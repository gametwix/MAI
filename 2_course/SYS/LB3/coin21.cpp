//coin21.cpp
#include "mlisp.h"

extern double VARIANT;
extern double LAST__DIGIT__OF__GROUP__NUMBER;
extern double KINDS__OF__COINS;
double first__denomination(double kinds__of__coins);
double count__change(double amount);
bool pier_Q(bool x_Q, bool y_Q);
double cc(double amount, double kinds__of__coins);
double denomination__list(double  kinds__of__coins);
double GR__AMOUNT();


double VARIANT=22.;

double LAST__DIGIT__OF__GROUP__NUMBER=5.;

double KINDS__OF__COINS=4.;

double first__denomination(double kinds__of__coins){
   return
	( kinds__of__coins == 1. ? 1.
	: kinds__of__coins == 2. ? 2.
 	: kinds__of__coins == 3. ? 5.
  : kinds__of__coins == 4. ? 10.
	: 0.
	);
}

double count__change(double amount){
	display( "______\n amount: ");
	display( amount);
        newline();
	display( "KINDS-OF-COINS: ");
	display( KINDS__OF__COINS);
        newline();
  {
   double largest__coin (first__denomination( KINDS__OF__COINS));
    display( "largest-coin: ");
    display( largest__coin);
    newline();
    return
	( amount > 0. &&
	  KINDS__OF__COINS > 0. &&
	  largest__coin > 0. ?
              ( display( "List of coin denominations: "),
                denomination__list( KINDS__OF__COINS),
	        display( "count-change= "),
      		cc(amount, KINDS__OF__COINS)
              )
	 : (display("Improper parameter value!\ncount-change= "), -1.)
	);
  }
}

bool pier_Q(bool x_Q, bool y_Q){

  return !(x_Q || y_Q);
}

double cc(double amount, double kinds__of__coins){
  return
	( amount == 0. ? 1.
	: pier_Q(amount < 0., kinds__of__coins == 0.) ?
	   cc(amount, kinds__of__coins - 1.) +
	   cc(amount - first__denomination(kinds__of__coins),
	     kinds__of__coins)
        : 0.
	);
}

double denomination__list(double  kinds__of__coins){
	return ( kinds__of__coins== 0 ? (newline() , 0.)
                : (display(first__denomination(kinds__of__coins)),
                   display(" "),
                   denomination__list(kinds__of__coins - 1.)
                  )
               );
}

double GR__AMOUNT(){
   return
    remainder(100. * LAST__DIGIT__OF__GROUP__NUMBER + VARIANT,
              231);
}

int main(){
 display ("Variant ");
 display (VARIANT);
 newline();
 newline();
 display (count__change(100.) ); newline();
 display (count__change(GR__AMOUNT()) ); newline();
 KINDS__OF__COINS=13.;
 display (count__change(100.) ); newline();
 display ("(c) Mohliakov P.A. 2021\n");

 std::cin.get();
 return 0;
}

