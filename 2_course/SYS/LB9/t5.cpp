/*  KPG   */
#include "mlisp.h"
double __KPG__try/*2*/ (double x);
//________________ 
double __KPG__try/*2*/ (double x){
 x = sin(x);	
return
 x;
	 }
int main(){
 display(__KPG__try(2));
	 newline();
	  std::cin.get();
	 return 0;
	 }

