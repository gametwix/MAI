/*  MPA   */
#include "mlisp.h"
extern double VARIANT/*3*/;
extern double LAST__DIGIT__OF__GROUP__NUMBER/*4*/;
extern double KINDS__OF__COINS/*5*/;
double first__denomination/*7*/ (double kinds__of__coins);
bool NOT_Q/*18*/ (bool x_Q);
bool AND_Q/*22*/ (bool x_Q, bool y_Q);
bool MORE_Q/*26*/ (double x, double y);
bool LESS_Q/*30*/ (double x, double y);
double count__change/*35*/ (double amount);
bool pier_Q/*61*/ (bool x_Q, bool y_Q);
double cc/*65*/ (double amount, double kinds__of__coins);
double denomination__list/*75*/ (double kinds__of__coins);
double GR__AMOUNT/*88*/ ();
//________________ 
double VARIANT/*3*/ = 22.;
double LAST__DIGIT__OF__GROUP__NUMBER/*4*/ = 5.;
double KINDS__OF__COINS/*5*/ = 4.;
double first__denomination/*7*/ (double kinds__of__coins){
 return
(( kinds__of__coins == 1. )
	? (1.)
	: ( kinds__of__coins == 2. )
	? (2.)
	: ( kinds__of__coins == 3. )
	? (5.)
	: ( kinds__of__coins == 4. )
	? (10.)
	: (0.));
	 }
bool NOT_Q/*18*/ (bool x_Q){
 return
( 0. == (x_Q
	? (1.)
	: (0.)) );
	 }
bool AND_Q/*22*/ (bool x_Q, bool y_Q){
 return
NOT_Q(
	( NOT_Q(
	x_Q) || NOT_Q(
	y_Q) ));
	 }
bool MORE_Q/*26*/ (double x, double y){
 return
AND_Q(
	( x >= y ) , NOT_Q(
	( x == y )));
	 }
bool LESS_Q/*30*/ (double x, double y){
 return
NOT_Q(
	( x >= y ));
	 }
double count__change/*35*/ (double amount){
 display("______\n amount: ");
	display(amount);
	newline();
	display("KINDS-OF-COINS: ");
	display(KINDS__OF__COINS);
	newline();
	{
double largest__coin(first__denomination(
	KINDS__OF__COINS));
	display("largest-coin: ");
	display(largest__coin);
	newline();
	return
(AND_Q(
	AND_Q(
	MORE_Q(
	amount , 0.) , MORE_Q(
	KINDS__OF__COINS , 0.)) , MORE_Q(
	largest__coin , 0.))
	? (display("List of coin denominations: "),
	denomination__list(
	KINDS__OF__COINS),
	display("count-change= "),
	cc(
	amount , KINDS__OF__COINS)
	)
	: (display("Improper parameter value!\ncount-change= "),
	-1.));
	}
}
bool pier_Q/*61*/ (bool x_Q, bool y_Q){
 return
NOT_Q(
	( x_Q || y_Q ));
	 }
double cc/*65*/ (double amount, double kinds__of__coins){
 return
(( amount == 0. )
	? (1.)
	: pier_Q(
	LESS_Q(
	amount , 0.) , ( kinds__of__coins == 0. ))
	? (( cc(
	amount , ( kinds__of__coins - 1. ))
	 + cc(
	( amount - first__denomination(
	kinds__of__coins) ) , kinds__of__coins)
	 ))
	: (0.));
	 }
double denomination__list/*75*/ (double kinds__of__coins){
 return
(( kinds__of__coins == 0. )
	? (newline(),
	0.)
	: (display(first__denomination(
	kinds__of__coins)),
	display(" "),
	denomination__list(
	( kinds__of__coins - 1. ))));
	 }
double GR__AMOUNT/*88*/ (){
 return
remainder(
	( ( 100. * LAST__DIGIT__OF__GROUP__NUMBER ) + VARIANT ) , 231.)
	;
	 }
int main(){
display("Variant ");
	display(VARIANT);
	newline();
	newline();
	display(count__change(
	100.));
	newline();
	display(count__change(
	GR__AMOUNT()));
	newline();
	KINDS__OF__COINS = 13.;
	display(count__change(
	100.));
	newline();
	display("(c) Mohliakov P.A. 2021\n");
	std::cin.get();
	return 0;
}

