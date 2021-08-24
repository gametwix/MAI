//                 Make-semantics.cpp 2020
#include <iostream>
#include <iomanip>
#include "kngramma.h"

#include "basegramma.cpp"
#include "kngramma.cpp"
using namespace std;

int main()
{
  const int MAXPROD=110;
  char buf[100];

  do{
   cout << "Input gramma name>";
   *buf = 0;
   cin.getline(buf,100);
  if (!*buf) break;

   char* name=buf;
   bool print=false;
   if(*name=='+'){ ++name; print=true;}
   string gramma_name = 
                  string( name )+".txt" ;
   cout << "Gramma:"<<
            gramma_name<<endl;
//____________________________________
  tGramma gr;
  gr.loadFromFile(gramma_name.c_str());
  if(!gr){ cout << gr.getError() << endl; continue;};
  if(print)outgr(cout,gr);
   {
    string cpp_name = 
                 "semantics.cpp" ;
    ofstream file(cpp_name.c_str());
    file << "/* " << gr.decode(2) << " */" << endl;
    file << "#include \"semantics.h\"\n"
            "using namespace std;\n";

    file << "void tSM::init(){\n";
    file << "\treturn;}\n";

    int count=0;
    size_t wmax=gr.smbWidth();
    for (size_t left=gr.getStart(); left<gr.ABCsize()
                               ; ++left){
      string sleft = gr.decode(left);
      size_t ac = gr.altCount(left);
      for(size_t ialt=0; ialt<ac; ++ialt){
       ++count;
       const tGramma::tSymbstr& rp = gr.rightPart(left,ialt);
       file << "int tSM::p" <<
         (count<10 ? "0" : "") <<
           count << "(){ //" ;
       file << setw(wmax)<<sleft <<" ->";
       out_chain(file,gr,rp);
       file << "\n\treturn 0;}\n";
      }
     }
    file << "//_____________________\n";
    ++count;
    for(size_t  lc=0; count<=MAXPROD; ++count){
       file << "int tSM::p" <<
         (count<10 ? "0" : "") <<
           count << "(){" 
        << "return 0;} ";
     if(++lc>1) { lc=0;file << endl;};
    } 
    file << "\n\n";
    cout << cpp_name;
    cout <<(file ? " is saved!" : " is not saved!")<<endl;
   }
//
 } while(false);
 cout<<"Press Enter to exit >";
 cin.get();
 return 0;
}
