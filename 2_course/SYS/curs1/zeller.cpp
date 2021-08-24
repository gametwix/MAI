/*  MPA   */
#include "mlisp.h"
bool NOT_Q/*3*/ (bool x_Q);
double day__of__week/*9*/ ();
double zeller/*16*/ (double d, double m
	 , double y, double c);
double neg__to__pos/*26*/ (double d);
double birthday/*30*/ (double dw);
extern double dd/*44*/;
extern double mm/*45*/;
extern double yyyy/*46*/;
//________________ 
bool NOT_Q/*3*/ (bool x_Q){
 return
( 0. == (x_Q
	? (1.)
	: (0.)) );
	 }
double day__of__week/*9*/ (){
 return
zeller(
	dd , (NOT_Q(
	( mm >= 3. ))
	? (( mm + 10. ))
	: (( mm - 2. ))) , 
	remainder(
	(NOT_Q(
	( mm >= 3. ))
	? (( yyyy - 1. ))
	: (yyyy)) , 100.)
	 , quotient(
	(NOT_Q(
	( mm >= 3. ))
	? (( yyyy - 1. ))
	: (yyyy)) , 100.)
	)
	;
	 }
double zeller/*16*/ (double d, double m
	 , double y, double c){
 return
neg__to__pos(
	remainder(
	( d + y + quotient(
	( ( 26. * m ) - 2. ) , 10.)
	 + quotient(
	y , 4.)
	 + quotient(
	c , 4.)
	 + ( 2. * ( - c ) ) ) , 7.)
	);
	 }
double neg__to__pos/*26*/ (double d){
 return
(NOT_Q(
	( d >= 0. ))
	? (( d + 7. ))
	: (d));
	 }
double birthday/*30*/ (double dw){
 display("Your were born on ");
	display((( dw == 1. )
	? "Monday "
	: ""));
	display((( dw == 2. )
	? "Tuesday "
	: ""));
	display((( dw == 3. )
	? "Wednesday "
	: ""));
	display((( dw == 4. )
	? "Thursday "
	: ""));
	display((( dw == 5. )
	? "Friday "
	: ""));
	display((( dw == 6. )
	? "Saturday "
	: ""));
	display((( dw == 7. )
	? "Sunday "
	: ""));
	display(dd);
	display(".");
	display(mm);
	display(".");
	return
yyyy;
	 }
double dd/*44*/ = 11.;
double mm/*45*/ = 07.;
double yyyy/*46*/ = 2001.;
int main(){
display(birthday(
	day__of__week()));
	newline();
	std::cin.get();
	return 0;
}

