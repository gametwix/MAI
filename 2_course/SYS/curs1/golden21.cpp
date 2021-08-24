/*  MPA   */
#include "mlisp.h"
extern double a/*2*/;
extern double b/*2*/;
double fun/*3*/ (double x);
bool NOT_Q/*8*/ (bool x_Q);
double golden__section__search/*13*/ (double a, double b);
double golden__start/*21*/ (double a, double b);
extern double mphi/*30*/;
double __MPA__try/*31*/ (double a, double b
	 , double xa, double ya
	 , double xb, double yb);
bool close__enough_Q/*51*/ (double x, double y);
extern double tolerance/*53*/;
extern double total__iterations/*54*/;
extern double xmin/*55*/;
//________________ 
double a/*2*/ = -1.;
double b/*2*/ = 0.;
double fun/*3*/ (double x){
 x = ( x - ( 22. / 23. ) );
	return
( expt(
	( exp(
	( - x )) - 5. ) , 4.)
	 - 11. );
	 }
bool NOT_Q/*8*/ (bool x_Q){
 return
( 0. == (x_Q
	? (1.)
	: (0.)) );
	 }
double golden__section__search/*13*/ (double a, double b){
 {
double xmin((NOT_Q(
	( a >= b ))
	? (golden__start(
	a , b)
	)
	: (golden__start(
	b , a)
	)));
	newline();
	return
xmin;
	}
}
double golden__start/*21*/ (double a, double b){
 total__iterations = 0.;
	{
double xa(( a + ( mphi * ( b - a ) ) )),
	xb(( b + ( - ( mphi * ( b - a ) ) ) ));
	return
__MPA__try(
	a , b , 
	xa , fun(
	xa) , 
	xb , fun(
	xb))
	;
	}
}
double mphi/*30*/ = ( ( 3. - sqrt(
	5.) ) * ( 1 / 2.0 ) );
double __MPA__try/*31*/ (double a, double b
	 , double xa, double ya
	 , double xb, double yb){
 return
(close__enough_Q(
	a , b)
	? (( ( a + b ) * 0.5 ))
	: (total__iterations = ( total__iterations + 1. ),
	(NOT_Q(
	( ya >= yb ))
	? (b = xb,
	xb = xa,
	yb = ya,
	xa = ( a + ( mphi * ( b - a ) ) ),
	__MPA__try(
	a , b , 
	xa , fun(
	xa) , 
	xb , yb)
	)
	: (a = xa,
	xa = xb,
	ya = yb,
	xb = ( b - ( mphi * ( b - a ) ) ),
	__MPA__try(
	a , b , 
	xa , ya , 
	xb , fun(
	xb))
	))));
	 }
bool close__enough_Q/*51*/ (double x, double y){
 return
NOT_Q(
	( abs(
	( x - y )) >= tolerance ));
	 }
double tolerance/*53*/ = 0.001;
double total__iterations/*54*/ = 0.;
double xmin/*55*/ = 0.;
int main(){
xmin = golden__section__search(
	a , b)
	;
	display("Interval=\t[");
	display(a);
	display(" , ");
	display(b);
	display("]\n");
	display("Total number of iteranions=");
	display(total__iterations);
	newline();
	display("xmin=\t\t");
	display(xmin);
	newline();
	display("f(xmin)=\t");
	display(fun(
	xmin));
	newline();
	std::cin.get();
	return 0;
}

