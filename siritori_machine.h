#ifndef _SIRITORI_MACHINE_H_
#define _SIRITORI_MACHINE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Siritori{

public:

  int siritori_for_you(string word,int turn);
  int siritori_for_cpu(string word,int turn);
  void init_evaluation_value();
  void init_each_words_lines();
  string choiece_max_evaluation_word(int turn);
  string choiece_random_word(int turn);
  int com_create_word();
  void update_evaluation_values(int turn,double q_value);
  bool greedy_algorithm();
  int random_0_80();
  void erase_said_words();
  void erase_temp_each_word_index();
  void add_to_said_words(string word);
  void show_said_words(int turn,string arg1);

private:

  //使用できるひらがなと記号
  char hiragana[81][4] = {
                      "あ","い","う","え","お", "か","き","く","け","こ",
                      "さ","し","す","せ","そ", "た","ち","つ","て","と",
                      "な","に","ぬ","ね","の", "は","ひ","ふ","へ","ほ",
                      "ま","み","む","め","も", "や","ゆ","よ",
                      "ら","り","る","れ","ろ", "わ","を","ん",
                      "ぁ","ぃ","ぅ","ぇ","ぉ", "ゃ","ゅ","ょ","っ",
                      "が","ぎ","ぐ","げ","ご", "ざ","じ","ず","ぜ","ぞ",
                      "だ","ぢ","づ","で","ど", "ば","び","ぶ","べ","ぼ",
                      "ぱ","ぴ","ぷ","ぺ","ぽ", "ー"
                    };

  //ひらがな個別ファイルの行数配列を0で初期化
  double evaluation_values[81][81] = {};

  int each_words_lines[81][81] = {};

  //ひらがなのリストサイズ
  const int hiragana_size = sizeof(hiragana) / sizeof(hiragana[0]);

  //forカウンタ
  int i;
  int j;
  int k;

  //入力文字列保存
  string word;

  // //入力文字列の長さ
  int word_size;

  //入力した単語の先頭文字
  string word_start;

  //入力した単語の行末文字
  string word_end;

  //出てきた単語を重複確認のために保存する動的配列
  vector<string> said_words;

  vector<int> temp_each_word_index;

  //fileポインタ
  FILE *fp1;

  FILE *fp2;

  //ひらがな個別ファイルから読み込むファイル名
  string file_pass1;

  string file_pass2;

  string arg1;

  //単語ごとの評価値
  double q_value;

  int max_q_value;

  //前に言った人の行末の文字
  string before_word_end;

  int word_start_index;

  int word_end_index;

  int before_word_end_index;

  //経過ターン数(自分言った、相手言ったで2ターン)を保存
  int turn;



};

#endif
