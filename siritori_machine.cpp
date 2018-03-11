#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <random>
#include "siritori_machine.h"


using namespace std;

int Siritori::siritori_for_you(string word,int turn){

  //入力された文字列の大きさ
  word_size = word.size();

  int word_judge_count = 0;

  //入力された文字を一文字ずつ取り出すためのループ
  for(i = 0; i < word_size; i += 3){

    //取り出した文字が、ひらがなリストと一致するかチェックするためのループ
    for(j = 0; j < hiragana_size; j++){

      //ひらがなリストと一致しない時の処理
      if(word.substr(i,3) == hiragana[j]){
        word_judge_count = 1;
        break;
      }

      else{
        word_judge_count = 0;
      }

    }

    //ひらがなリストと一致しない時の処理
    if(word_judge_count == 0 && turn != 0){
      cout << "\n先頭、行末は、ルールに沿った、ひらがなでなければいけません。\n" << endl;
      cout << "次の文字は「" << before_word_end << "」です。\n" << endl;
      return -1;
    }

    else if(word_judge_count == 0){
      cout << "\n先頭、行末は、ルールに沿った、ひらがなでなければいけません。\n" << endl;
      return -1;
    }

  }

  //行頭の文字だけを取得
  word_start = word.substr(0,3);

  //行末の文字だけを取得
  word_end = word.substr(word.size()-3,3);

  //一番最初のターン以外の処理
  if(turn != 0){

    //相手が言った行末文字と、自分が言う行頭文字が違う時
    if(word_start != before_word_end){
      cout << "\n次の文字は「" << before_word_end << "」です。\n" << endl;

      //処理を入力受付に戻す
      return -1;
    }
  }

  //しりとりがはじまっているときの処理
  if(turn > 0){

    //いままで出た単語を走査するためのループ
    for(i = 0; i < turn; i++){

      //いままで出た単語と言おうとした単語が重複している時の処理
      if(word == said_words[i]){
        cout << "\nすでに出た単語は使えません。\n" << endl;
        cout << "次の文字は「" << before_word_end << "」です。\n" << endl;

        //単語を走査するためのループを抜ける
        break;
      }
    }

    //単語が重複している時の処理
    if(i != turn){

      //処理を入力受付に戻す
      return -1;
    }

  }

  //「ん」が行末文字の時の処理
  //hiragana[45] = "ん"
  if(word_end == "ん"){
    cout << "\n「ん」がついたのであなたの負けです。\n" << endl;

    //whileループを抜け、プログラム終了
    return 0;
  }

  //行末文字が「ー」のときは、次の人は行末から2文字目から始めるための処理
  //ex. みきさー → さくら
  //hiragana[80] = "ー"
  if(word_end == "ー"){
    before_word_end = word.substr(word.size()-6,3);
  }

  //行末が小文字の場合それを大文字として続けさせる
  else if(word_end == "ぁ"){
    before_word_end = "あ";
  }

  else if(word_end == "ぃ"){
    before_word_end = "い";
  }

  else if(word_end == "ぅ"){
    before_word_end = "う";
  }

  else if(word_end == "ぇ"){
    before_word_end = "え";
  }

  else if(word_end == "ぉ"){
    before_word_end = "お";
  }

  else if(word_end == "っ"){
    before_word_end = "つ";
  }

  else if(word_end == "ゃ"){
    before_word_end = "や";
  }

  else if(word_end == "ゅ"){
    before_word_end = "ゆ";
  }

  else if(word_end == "よ"){
    before_word_end = "ょ";
  }

  //通常処理
  else{

    //次のプレイヤーが続ける文字を保存
    before_word_end = word.substr(word.size()-3,3);
  }

  for(i = 0; i < hiragana_size; i++){
    if(before_word_end == hiragana[i]){
      before_word_end_index = i;
      break;
    }
  }

  //標準入力を保存

  cout << "\n次の文字は「" << before_word_end << "」です。\n" << endl;

  //動的配列に言った単語を追加していく
  // add_to_said_words(word);

  return 1;


}

int Siritori::siritori_for_cpu(string word,int turn){

  //行頭の文字だけを取得
  word_start = word.substr(0,3);

  //行末の文字だけを取得
  word_end = word.substr(word.size()-3,3);

  for(i = 0; i < hiragana_size; i++){
    if(word_start == hiragana[i]){
      word_start_index = i;
      break;
    }
  }

  for(i = 0; i < hiragana_size; i++){
    if(word_end == hiragana[i]){
      word_end_index = i;
      break;
    }
  }

  //一番最初のターン以外の処理
  if(turn != 0){

    //相手が言った行末文字と、自分が言う行頭文字が違う時
    if(word_start != before_word_end){
      return 0;
    }
  }

  //「ん」が行末文字の時の処理
  //hiragana[45] = "ん"
  if(word_end == "ん"){
    return 0;
  }

  if(Siritori::com_create_word() < 0){
    return 0;
  }

  //行末文字が「ー」のときは、次の人は行末から2文字目から始めるための処理
  //ex. みきさー → さくら
  //hiragana[80] = "ー"
  if(word_end == "ー"){
    before_word_end = word.substr(word.size()-6,3);
  }

  //行末が小文字の場合それを大文字として続けさせる
  else if(word_end == "ぁ"){
    before_word_end = "あ";
  }

  else if(word_end == "ぃ"){
    before_word_end = "い";
  }

  else if(word_end == "ぅ"){
    before_word_end = "う";
  }

  else if(word_end == "ぇ"){
    before_word_end = "え";
  }

  else if(word_end == "ぉ"){
    before_word_end = "お";
  }

  else if(word_end == "っ"){
    before_word_end = "つ";
  }

  else if(word_end == "ゃ"){
    before_word_end = "や";
  }

  else if(word_end == "ゅ"){
    before_word_end = "ゆ";
  }

  else if(word_end == "よ"){
    before_word_end = "ょ";
  }

  //通常処理
  else{

    //次のプレイヤーが続ける文字を保存
    before_word_end = word.substr(word.size()-3,3);

  }

  for(i = 0; i < hiragana_size; i++){
    if(before_word_end == hiragana[i]){
      before_word_end_index = i;
      break;
    }
  }

  return 1;


}

int Siritori::com_create_word(){

  temp_each_word_index.push_back(each_words_lines[word_start_index][word_end_index]);

  each_words_lines[word_start_index][word_end_index]--;

  int word_lines = each_words_lines[word_start_index][word_end_index];


  return word_lines;

}




string Siritori::choiece_max_evaluation_word(int turn){

  max_q_value = 0;

  if(turn == 0){

    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){

        if(evaluation_values[i][j] > max_q_value){
          max_q_value = evaluation_values[i][j];

          word_start = hiragana[i];
          word_end = hiragana[j];
        }

      }

    }

  }

  else{

    for(i = 0; i < hiragana_size; i++){

      if(evaluation_values[before_word_end_index][i] > max_q_value){
        max_q_value = evaluation_values[before_word_end_index][i];

        word_start = before_word_end;
        word_end = hiragana[i];

      }
    }
  }

  word = word_start + word_end;

  return word;

}

string Siritori::choiece_random_word(int turn){

  if(turn == 0){
    word_start = hiragana[Siritori::random_0_80()];
    word_end = hiragana[Siritori::random_0_80()];
  }

  else{
    word_start = before_word_end;
    word_end = hiragana[Siritori::random_0_80()];
  }

  word = word_start + word_end;
  return word;

}

void Siritori::init_evaluation_value(){

  file_pass1 = "evaluation_values.txt";
  FILE *fp1;

  fp1 = fopen(file_pass1.c_str(),"r");

  if(fp1 != NULL){

    char temp[256];

    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){
        fscanf(fp1,"%s %lf",temp,&evaluation_values[i][j]);
      }

    }

    fclose(fp1);

  }

  else{



    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){
        evaluation_values[i][j] = 0;
      }
    }

    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){
        file_pass1 = "./training_data/" + string(hiragana[i]) + string(hiragana[j]) + ".txt";
        fp1 = fopen(file_pass1.c_str(),"r");

        if(fp1 == NULL){
          evaluation_values[i][j] = 0;
        }

        else{

          char temp[256];

          while(fgets(temp,256,fp1)){
            evaluation_values[i][j]++;
          }

        }

        fclose(fp1);

      }

    }

  }

}

void Siritori::init_each_words_lines(){



  FILE *fp1;

  file_pass1 = "each_words_lines.txt";

  fp1 = fopen(file_pass1.c_str(),"r");

  if(fp1 == NULL){


    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){
        each_words_lines[i][j] = 0;
      }
    }



    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){

        file_pass1 = "./training_data/" + string(hiragana[i]) + string(hiragana[j]) + ".txt";
        fp1 = fopen(file_pass1.c_str(),"r");

        if(fp1 == NULL){
          each_words_lines[i][j] = 0;
        }

        else{

          char temp[256];

          while(fgets(temp,256,fp1)){
            each_words_lines[i][j]++;
          }

        }

        fclose(fp1);

      }

    }

    file_pass1 = "each_words_lines.txt";

    fp1 = fopen(file_pass1.c_str(),"w");

    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){
        fprintf(fp1,"%s %d\n",(string(hiragana[i]) + string(hiragana[j])).c_str(),each_words_lines[i][j]);
      }
    }

    fclose(fp1);

  }

  else{

    char temp[256];

    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){
        fscanf(fp1,"%s %d",temp,&each_words_lines[i][j]);
      }
    }

    fclose(fp1);

  }


}

int Siritori::random_0_80(){

  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution<> rand80(0,80);

  return rand80(mt);

}

bool Siritori::greedy_algorithm(){

  double e = 0.3;

  random_device rnd;
  mt19937 mt(rnd());
  uniform_real_distribution<> rand1(0.0, 1.0);

  if (rand1(mt) > e){
    return true;
  }

  else{
    return false;
  }

}

void Siritori::update_evaluation_values(int turn, double q_value){

  double before_q_value = 0;

  FILE *fp1;

  file_pass1 = "evaluation_values.txt";

  fp1 = fopen(file_pass1.c_str(),"r");

  if(fp1 != NULL){

    char temp[256];

    for(i = 0; i < hiragana_size; i++){
      if(i == word_start_index){
        for(j = 0; j < hiragana_size; j++){
          if(j == word_end_index){
            fscanf(fp1,"%s %lf\n",temp,&before_q_value);
            fclose(fp1);
            break;
          }
        }
      }
    }
  }

  q_value = before_q_value + (0.1 * (turn + (0.9 * max_q_value) - q_value));
  evaluation_values[word_start_index][word_end_index] = q_value;


  fp1 = fopen(file_pass1.c_str(),"w");

  if(fp1 != NULL){

    for(i = 0; i < hiragana_size; i++){
      for(j = 0; j < hiragana_size; j++){
        fprintf(fp1,"%s %lf\n",(string(hiragana[i]) + string(hiragana[j])).c_str(),evaluation_values[i][j]);
      }
    }
  }

  fclose(fp1);

}

void Siritori::erase_said_words(){
  said_words.erase(said_words.begin(),said_words.end());
}

void Siritori::erase_temp_each_word_index(){
  temp_each_word_index.erase(temp_each_word_index.begin(),temp_each_word_index.end());
}

void Siritori::add_to_said_words(string word){

  said_words.push_back(word);


}

void Siritori::show_said_words(int turn,string arg1){

  // cout << said_words[0] << endl;
  FILE *fp1;
  string command;
  char temp[256];

  if(arg1 == "-learn"){

    for(i = 0; i < said_words.size(); i++){

      file_pass1 = "./training_data/" + said_words[i].substr(0,3) + said_words[i].substr(said_words[i].size()-3,3) + ".txt";

      command = "sed -n " + to_string(temp_each_word_index[i]) + "p " + file_pass1;
      fp1 = popen(command.c_str(),"r");

      if(fp1 != NULL){
        fscanf(fp1,"%s",temp);
        pclose(fp1);
        said_words[i] = temp;
      }

      cout << said_words[i] << endl;

    }

  }

  else{

    // cout << said_words[0] << "だよ" << endl;

    file_pass1 = "./training_data/" + said_words[turn - 1].substr(0,3) + said_words[turn - 1].substr(said_words[turn - 1].size()-3,3) + ".txt";
    // cout << said_words[0] << "かー" << endl;
    command = "sed -n " + to_string(temp_each_word_index[0]) + "p " + file_pass1;
    fp1 = popen(command.c_str(),"r");

    if(fp1 != NULL){
      fscanf(fp1,"%s",temp);
      pclose(fp1);
      said_words[turn - 1] = temp;
    }

    cout << said_words[turn - 1] << endl;

    cout << "\n次の文字は「" << said_words[turn - 1].substr(said_words[turn - 1].size()-3,3) << "」です。" << endl;


  }

}
