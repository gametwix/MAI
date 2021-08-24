//                 lexer.h 2021
#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"
class tLexer:public tBaseLexer{
public:
//конструктор
 tLexer():tBaseLexer(){
//создать автоматы:

//________________________________________

//вещественное
  addstr(Adec,0,"+",1);
  addstr(Adec,0,"-",1);
  addstr(Adec,0,".",2);
  addrange(Adec,0,'0','9',1);
  addstr(Adec,1,".",2);
  addrange(Adec,1,'0','9',1);
  addrange(Adec,2,'0','9',3);
  addrange(Adec,3,'0','9',3);
  addstr(Adec,3,"e",4);
  addstr(Adec,3,"E",4);
  addstr(Adec,4,"-",5);
  addstr(Adec,4,"+",5);
  addrange(Adec,5,'0','9',6);
  addrange(Adec,6,'0','9',6);
  Adec.final(3);
  Adec.final(6);
//________________________________________

//-?!
//идентификатор
  //Начало (!,?,A-Z,a-z)
  addstr(Aid,0,"!",1);
  addstr(Aid,0,"?",2);
  addrange(Aid,0,'A','Z',1);
  addrange(Aid,0,'a','z',1);
  //Нормальное перемещение
  addrange(Aid,1,'0','9',1);
  addrange(Aid,1,'A','Z',1);
  addrange(Aid,1,'a','z',1);
  addstr(Aid,1,"!",1);
  //Обработка вопросительного знака
  addstr(Aid,1,"?",2);
  addrange(Aid,2,'0','9',1);
  addrange(Aid,2,'A','Z',1);
  addrange(Aid,2,'a','z',1);
  addstr(Aid,2,"?",2);
  addstr(Aid,2,"!",1);
  //Обработка исключения
  addstr(Aid,2,"-",3);
  addstr(Aid,1,"-",3);
  addstr(Aid,3,"?",4);
  //Отмена исключения для 3 состояния
  addrange(Aid,3,'0','9',1);
  addrange(Aid,3,'A','Z',1);
  addrange(Aid,3,'a','z',1);
  addstr(Aid,3,"!",1);
  addstr(Aid,3,"-",3);
  //Отмена исключения для 4 состояния
  addrange(Aid,4,'0','9',1);
  addrange(Aid,4,'A','Z',1);
  addrange(Aid,4,'a','z',1);
  addstr(Aid,4,"?",2);
  addstr(Aid,4,"-",3);
  Aid.final(1);
//________________________________________

//идентификатор предиката
  //Начало (!,?,-,A-Z,a-z)
  addstr(Aidq,0,"?",2);
  addstr(Aidq,0,"!",1);
  addstr(Aidq,0,"-",3);
  addrange(Aidq,0,'A','Z',1);
  addrange(Aidq,0,'a','z',1);
  //Нормальное перемещение
  addstr(Aidq,1,"?",2);
  addstr(Aidq,1,"!",1);
  addstr(Aidq,1,"-",3);
  addrange(Aidq,1,'A','Z',1);
  addrange(Aidq,1,'a','z',1);
  //Вопросительный знак
  addstr(Aidq,2,"?",2);
  addstr(Aidq,2,"!",1);
  addstr(Aidq,2,"-",3);
  addrange(Aidq,2,'A','Z',1);
  addrange(Aidq,2,'a','z',1);
  addrange(Aidq,2,'0','9',1);
  //Выход из третьего состояния
  addstr(Aidq,3,"?",2);
  addstr(Aidq,3,"!",1);
  addrange(Aidq,3,'A','Z',1);
  addrange(Aidq,3,'a','z',1);
  addrange(Aidq,3,'0','9',1);
  Aidq.final(2);
}
};
#endif

