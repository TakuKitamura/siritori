#include "calculate_exp.h"
#include <iostream>

using namespace std;


int main(){

  Exp ins;

  //指数
  double exp_num = 0;

  cout << "eの何乗を求めますか？ :" ; cin >> exp_num;

  cout << ins.Calculate_exp(exp_num) << endl;

  return 0;

}
