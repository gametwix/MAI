//                 mlispsem.cpp 2019
#include <iostream>
#include <iomanip>
//#include "semantics.h"

#include "basegramma.cpp"
#include "kngramma.cpp"
#include "slr.cpp"
#include "baselexer.cpp"
#include "base-compiler.cpp"
#include "semantics.cpp"
#include "code-gen.cpp"
using namespace std;

int main()
{
  char buf[1000];
   cout << "Input gramma name>";
   *buf = 0;
   cin.getline(buf,1000);

   char* name=buf;
   bool print=false;
   if(*name=='+'){ ++name; print=true;}
   string gramma_name = 
                  string( name )+".txt" ;
   cout << "Gramma:"<<
            gramma_name<<endl;
//____________________________________
  tSM sm(gramma_name.c_str());
  tCG cg(gramma_name.c_str());
  tBC& bc=sm;
  tBC& bc2=cg;
   if(print){
     outgr(cout, bc.getGramma());
     }
  if(!bc || !bc2){
    cout<<
      "Good bye!\n";
    cin.get();
    return 1;
    }

  do{
   cout << "Source>";
   *buf = 0;
   cin.getline(buf,1000);
   if (!*buf) break;
   char* name=buf;
   bool file=false;
   bc.PARSER_DEBUG = true;
//****************************************
   do{ //16.04.2016
    if(*name=='\''){ ++name; file=true;
     break;
    }

    if(*name=='/'){ ++name; file=true;
     bc.PARSER_DEBUG = false;
     break;
    }

    string source_name = string(name) + ".ss";
    ifstream tmp(source_name.c_str());
    if(!tmp) break;
// ������ ����� ������ �� ��� �����
    file = true;
    bc.PARSER_DEBUG = false;
   }while(false);
//****************************************

   string source = (file ? name : "temp");
   string source_name = source + ".ss";
   if(!file){
     ofstream tmp(source_name.c_str());
     tmp << buf << endl;
    bc.PARSER_DEBUG = false;// 2020
     }

   cout << "Source:"<<
            source_name<<endl;
  {// ������ ����� ���������� �����
    ifstream fsource(source_name.c_str());
    int linecount=0;
    while(fsource){
     *buf=0;
     fsource.getline(buf,1000);
     cout<< setw(4)<< ++linecount<<"|"<<
                              buf<<endl;
     }//while(fsource)...
     cout<<"_________________\n";
   }// ����� �����

   int res = bc.rewrite(source_name.c_str());
   int res2 = bc2.rewrite(source_name.c_str());
       cout<< bc.getMessage();
//       cout<< bc.getMessage()<<endl;
   if(res==0 && res2 == 0){
      cout <<"Accepted!\n";
      cout <<"Code:\n"<<
                       bc2.getObject()<< endl;
     string obj_name = source + ".cpp";
     ofstream tmp(obj_name.c_str());
     tmp << bc2.getObject() << endl;
     if(tmp)
        cout << "Code is saved to file " << obj_name <<
                " ! "<<endl;
    }
    else 
      cout <<"Rejected!\n";
   cout<<"_________________________\n";
 } while(true);
 return 0;
}
