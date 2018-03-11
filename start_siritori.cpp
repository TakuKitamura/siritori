#include "siritori_machine.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <vector>
#include <iomanip>

using namespace std;

//コマンドライン引数により、通常プレイか学習するかの処理を分岐させる
int main(int argc, char *argv[]){

  Siritori ins;

  string arg1;

  //コマンドライン引数が2つある時
  if(argc == 2){
    //第二コマンドライン引数を保存
    arg1 = argv[1];
  }

  //Player VS CPU の処理
  if(arg1 != "-learn"){

    //経過ターン数(自分、相手、自分で3ターン)を保存
    int turn = 0;

    //進行中のしりとりの状態を表す
    //judge_number == 1  :　通常どうり
    //judge_number == -1 :　入力値不正、すでに出た単語を入力した
    //judge_number == 0  :　「ん」がついてしりとり終了

    int judge_number = 0;

    string choice_num;

    //入力文字列
    string player_word;

    //入力文字列
    string cpu_word;

    double q_value = 0;
    turn = 0;
    ins.init_evaluation_value();
    ins.init_each_words_lines();

    cout << "\nPLAYER VS CPU\n" << endl;

    do{
      cout << "先行（1）、後行（2）どちらにしますか。 :";

      cin >> setw(1) >> choice_num;

      cout << "\n";

    }while(atoi(choice_num.c_str()) != 1 && atoi(choice_num.c_str()) != 2);



    //「ん」がついてしりとり終了するまでループ
    while(1){

      if(turn == 0 && atoi(choice_num.c_str()) == 1){
        cout << ":"; cin >> setw(60) >> player_word;
        judge_number = ins.siritori_for_you(player_word,turn);

        if(judge_number == 1){
          ins.add_to_said_words(player_word);
          turn++;
        }

        else if(judge_number == -1){
          continue;
        }

        else{
          break;
        }
      }

      if(turn % 2 == 0 && turn != 0){
        cout << ":"; cin >> setw(60) >> player_word;
        judge_number = ins.siritori_for_you(player_word,turn);

        if(judge_number == 1){
          ins.add_to_said_words(player_word);
          turn++;
        }

        else if(judge_number == -1){
          continue;
        }

        else{
          break;
        }
      }

      else{


        while(1){
          if(ins.greedy_algorithm()){

            cpu_word = ins.choiece_max_evaluation_word(turn);



            judge_number = ins.siritori_for_cpu(cpu_word,turn);

            if(judge_number == 1){

              ins.update_evaluation_values(turn,q_value);
              // cout << cpu_word << " です" << endl;
              ins.add_to_said_words(cpu_word);
              turn++;
              break;
            }

            else{
              q_value = 0;
              turn = 0;
              ins.init_each_words_lines();
              ins.erase_said_words();
              ins.erase_temp_each_word_index();
            }

          }

          else{
            cpu_word = ins.choiece_random_word(turn);

            judge_number = ins.siritori_for_cpu(cpu_word,turn);

            if(judge_number == 1){
              ins.update_evaluation_values(turn,q_value);
              // cout << cpu_word <<" です" << endl;
              ins.add_to_said_words(cpu_word);
              turn++;
              break;

            }

            else{
              q_value = 0;
              turn = 0;
              ins.init_each_words_lines();
              ins.erase_said_words();
              ins.erase_temp_each_word_index();
            }

          }

        }
        ins.show_said_words(turn,arg1);
        // cout << turn << endl;
        cout << "\n";

      }

    }


  }

  //CPU VS CPU の処理
  else{
    cout << "\nCPU VS CPU\n" << endl;

    int turn = 0;

    double q_value = 0;

    int judge_number = 0;

    //入力文字列
    string cpu_word;

    string choice_num;

    turn = 0;
    q_value = 0;
    ins.init_evaluation_value();
    ins.init_each_words_lines();

    int roop_count = 0;
    string roop_num;
    string word_limit;

    do{
      cout << "しりとりをする単語数はいくつにしますか。 :";

      cin >> setw(4) >> word_limit;

      cout << "しりとりの往復数はいくつにしますか。 :";

      cin >> setw(4) >> roop_num;

      cout << "\n";

    }while(atoi(word_limit.c_str()) < 1 || atoi(roop_num.c_str()) < 1);

    while(roop_count < atoi(roop_num.c_str())){
      turn = 0;
      q_value = 0;
      ins.init_each_words_lines();
      ins.erase_said_words();
      ins.erase_temp_each_word_index();


      while(turn < atoi(word_limit.c_str())){

        //Q値が最大の単語を選ぶ
        if(ins.greedy_algorithm()){

          cpu_word = ins.choiece_max_evaluation_word(turn);

          judge_number = ins.siritori_for_cpu(cpu_word,turn);

          if(judge_number == 1){
            ins.update_evaluation_values(turn,q_value);
            ins.add_to_said_words(cpu_word);
            turn++;
          }

          else{
            q_value = 0;
            turn = 0;
            ins.init_each_words_lines();
            ins.erase_said_words();
            ins.erase_temp_each_word_index();
          }

        }

        else{
          cpu_word = ins.choiece_random_word(turn);

          judge_number = ins.siritori_for_cpu(cpu_word,turn);

          if(judge_number == 1){
            ins.update_evaluation_values(turn,q_value);
            ins.add_to_said_words(cpu_word);
            turn++;

          }

          else{
            q_value = 0;
            turn = 0;
            ins.init_each_words_lines();
            ins.erase_said_words();
            ins.erase_temp_each_word_index();
          }

        }


      }

      ins.show_said_words(turn,arg1);
      cout << "\n";
      roop_count++;

    }

  }

}
