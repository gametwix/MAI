/* $ms */
#include "semantics.h"
using namespace std;
void tSM::init(){
  globals.clear();
  locals.clear();
  params.clear();
  scope =0; // вне процедуры

//константы:
  globals["e"] = 
    tgName(VAR|DEFINED|BUILT);
// ...
// элементарные процедуры:
  globals["abs"] =
    tgName(PROC|DEFINED|BUILT,"", 1);
// ...
  globals["remainder"] =
    tgName(PROC|DEFINED|BUILT,"", 2);
// ...
	return;}
int tSM::p01(){ //       S -> PROG
 bool error=false;
 for(tGlobal::iterator it=globals.begin();
     it!=globals.end();
     ++it){
// Просмотреть таблицу глобальных имен
// и в сообщении об ошибках указать имена
// ВСЕХ вызванных, но не определенных процедур,
// а также использованных, но не определенных
// глобальных переменных.
//   it->first   имя
//   it->second  учетная запись
// ...
 }//for...
 if(error) return 1;
	return 0;}
int tSM::p02(){ //  PROG -> CALCS
	return 0;}
int tSM::p03(){ //  PROG -> DEFS
	return 0;}
int tSM::p04(){ //  PROG -> DEFS CALCS
	return 0;}
int tSM::p05(){ // CALCS -> CALC
	return 0;}
int tSM::p06(){ // CALCS -> CALCS CALC
	return 0;}
int tSM::p07(){ //  CALC -> E
	return 0;}
int tSM::p08(){ //     E -> $int
	return 0;}
int tSM::p09(){ //     E -> $id
 string name = S1->name;
 switch(scope){
    case 2:if(locals.count(name))break;
    case 1:if(params.count(name))break;
    default:tgName& ref = globals[name];
       if(ref.empty()){
            ref = tgName(VAR|USED, S1->line);
            break;
       }//if(ref.empty())...
       if(ref.test(VAR)){
             ref.set(USED);
            break;
       }
       if(ref.test(BUILT)){
           ferror_message+=
             "Error[09-1] in line "+ S1->line +": the built-in '"
              +name+
             "' procedure \n\t\t\t cannot be used as a variable!\n";
//встроенную процедуру 'abs' нельзя использовать в качестве переменной
//the built-in 'abs' procedure cannot be used as a variable
        return 1;
        }

        ferror_message+=
             "Error[09-2] in line "+ S1->line +": the name '"
              +name+
             "' cannot be used to refer to a variable;\n"+
             "\t\t\tit was previously declared as a procedure in line "+ ref.line +" !\n";
//имя 'f' нельзя использовать для ссылки на переменную, в строке 1 оно ранее объявлено как процедура
//the name 'f' cannot be used to refer to a variable; it was previously declared as a procedure in line 1
        return 1;

  }//switch...

	return 0;}
int tSM::p10(){ //   DEF -> PROC
	return 0;}
int tSM::p11(){ //  DEFS -> DEF
	return 0;}
int tSM::p12(){ //  DEFS -> DEFS DEF
	return 0;}
int tSM::p13(){ //  PROC -> HPROC E )
// точка анализа выходит из тела
// процедуры
 params.clear();
 scope = 0;
	return 0;}
int tSM::p14(){ // HPROC -> PCPAR )
// ???
// точка анализа входит в тело
// процедуры
 scope = 1;
	return 0;}
int tSM::p15(){ // PCPAR -> ( define ( $id
 S1->name = S4->name;
 S1->count = 0;
	return 0;}
int tSM::p16(){ // PCPAR -> PCPAR $id
    if(params.count(S2->name)){
      ferror_message+=
        "Error[16-1] in line "+ S2->line +": the procedure '"
        +S1->name+
        "' duplicates \n\t\t\tthe '"
        +S2->name+"' parameter!\n";
//в процедуре 'f' дублируется параметр 'x'
//the 'f' procedure duplicates the 'x' parameter
      return 1;
    }

    if(S2->name==S1->name){
      ferror_message+=
        "Warning[16-2] in line "+ S2->line +": procedure '"
        +S1->name+
        "'has the same name \n"
        "\t\t\tas its parameter!\n";
//у процедуры 'f' такое же имя, как у ее параметра
//procedure 'f' has the same name as its parameter
    }
    params.insert(S2->name);
 ++S1->count;
	return 0;}
//_____________________
int tSM::p17(){return 0;} int tSM::p18(){return 0;} 
int tSM::p19(){return 0;} int tSM::p20(){return 0;} 
int tSM::p21(){return 0;} int tSM::p22(){return 0;} 
int tSM::p23(){return 0;} int tSM::p24(){return 0;} 
int tSM::p25(){return 0;} int tSM::p26(){return 0;} 
int tSM::p27(){return 0;} int tSM::p28(){return 0;} 
int tSM::p29(){return 0;} int tSM::p30(){return 0;} 
int tSM::p31(){return 0;} int tSM::p32(){return 0;} 
int tSM::p33(){return 0;} int tSM::p34(){return 0;} 
int tSM::p35(){return 0;} int tSM::p36(){return 0;} 
int tSM::p37(){return 0;} int tSM::p38(){return 0;} 
int tSM::p39(){return 0;} int tSM::p40(){return 0;} 
int tSM::p41(){return 0;} int tSM::p42(){return 0;} 
int tSM::p43(){return 0;} int tSM::p44(){return 0;} 
int tSM::p45(){return 0;} int tSM::p46(){return 0;} 
int tSM::p47(){return 0;} int tSM::p48(){return 0;} 
int tSM::p49(){return 0;} int tSM::p50(){return 0;} 
int tSM::p51(){return 0;} int tSM::p52(){return 0;} 
int tSM::p53(){return 0;} int tSM::p54(){return 0;} 
int tSM::p55(){return 0;} int tSM::p56(){return 0;} 
int tSM::p57(){return 0;} int tSM::p58(){return 0;} 
int tSM::p59(){return 0;} int tSM::p60(){return 0;} 
int tSM::p61(){return 0;} int tSM::p62(){return 0;} 
int tSM::p63(){return 0;} int tSM::p64(){return 0;} 
int tSM::p65(){return 0;} int tSM::p66(){return 0;} 
int tSM::p67(){return 0;} int tSM::p68(){return 0;} 
int tSM::p69(){return 0;} int tSM::p70(){return 0;} 
int tSM::p71(){return 0;} int tSM::p72(){return 0;} 
int tSM::p73(){return 0;} int tSM::p74(){return 0;} 
int tSM::p75(){return 0;} int tSM::p76(){return 0;} 
int tSM::p77(){return 0;} int tSM::p78(){return 0;} 
int tSM::p79(){return 0;} int tSM::p80(){return 0;} 
int tSM::p81(){return 0;} int tSM::p82(){return 0;} 
int tSM::p83(){return 0;} int tSM::p84(){return 0;} 
int tSM::p85(){return 0;} int tSM::p86(){return 0;} 
int tSM::p87(){return 0;} int tSM::p88(){return 0;} 
int tSM::p89(){return 0;} int tSM::p90(){return 0;} 
int tSM::p91(){return 0;} int tSM::p92(){return 0;} 
int tSM::p93(){return 0;} int tSM::p94(){return 0;} 
int tSM::p95(){return 0;} int tSM::p96(){return 0;} 
int tSM::p97(){return 0;} int tSM::p98(){return 0;} 
int tSM::p99(){return 0;} int tSM::p100(){return 0;} 
int tSM::p101(){return 0;} int tSM::p102(){return 0;} 
int tSM::p103(){return 0;} int tSM::p104(){return 0;} 
int tSM::p105(){return 0;} int tSM::p106(){return 0;} 
int tSM::p107(){return 0;} int tSM::p108(){return 0;} 
int tSM::p109(){return 0;} int tSM::p110(){return 0;} 


