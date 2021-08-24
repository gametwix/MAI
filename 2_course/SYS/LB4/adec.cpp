
//               adec.cpp
#include <iostream>
#include <iomanip>
#include "fsm.h"
using namespace std;

int main()
{
  tFSM Adec;
///////////////////////
//удалить этот код и заменить своим
  addrange(Adec,0,'0','9',1);
  addrange(Adec,1,'0','9',1);
  addstr(Adec,1,".",2);
  addrange(Adec,2,'0','9',2);
 Adec.final(2);
///////////////////////
  cout << "Number of states = " << Adec.size()
       << "\n";

  while(true)
 {
  char input[81];
  cout << ">";
  cin.getline(input,81);
  if(!*input) break;
  int res = Adec.apply(input);
  cout << setw(res?res+1:0) << "^"
       << endl;
 }
 return 0;
}

