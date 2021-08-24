//my.cpp
#include <iostream>
#include <iomanip>
#include "fsm.h"
using namespace std;

int main()
{
  tFSM fsm;

///////////////////////
//  Конечный автомат
  addstr(fsm,0,"+",1);
  addstr(fsm,0,"-",1);
  addstr(fsm,0,".",2);
  addrange(fsm,0,'0','9',1);
  addstr(fsm,1,".",2);
  addrange(fsm,1,'0','9',1);
  addrange(fsm,2,'0','9',3);
  addrange(fsm,3,'0','9',3);
  addstr(fsm,3,"e",4);
  addstr(fsm,3,"E",4);
  addstr(fsm,4,"-",5);
  addstr(fsm,4,"+",5);
  addrange(fsm,5,'0','9',6);
  addrange(fsm,6,'0','9',6);
  fsm.final(3);
  fsm.final(6);
///////////////////////

  cout << "Number of states = " << fsm.size()
       << "\n";

  while(true)
 {
  char input[81];
  cout << ">";
  cin.getline(input,81);
  if(!*input) break;
  int res = fsm.apply(input);
  cout << setw(res?res+1:0) << "^"
       << endl;
 }
 return 0;
}

