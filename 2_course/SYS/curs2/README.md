# Compiler of a simplified dialect of the Lisp language to the C ++ language
Compiler-translator based on a finite automaton. To analyze the syntax and semantics of a Lisp program, error conclusions and warnings. In the absence of errors, translates the program into C++

Accepts grammar and Lisp source code and outputs C++ source code

## Example:

Lisp file:

```
;golden21
(define a -1)(define b 0)
(define (fun x)
 (set! x (- x (/ 22 23)))
 ( - (expt(- (exp(- x )) 5) 4) 11)
)

(define (NOT? x?) 
(= 0(cond (x? 1)(else 0)))
)


(define (golden-section-search a b)
    (let(
      (xmin (cond ((NOT?(>= a b))(golden-start a b))(else(golden-start b a ))))
    )
    (newline)
    xmin
    )
)
(define (golden-start a b)
 (set! total-iterations 0)
  (let(
      (xa (+ a (* mphi(- b a))))
      (xb (+ b (-(* mphi(- b a)))))
    )
    (try a b xa (fun xa) xb (fun xb))
  )
)
(define mphi (* (- 3(sqrt 5))(/ 2.0)))
(define (try a b xa ya xb yb)
 (cond((close-enough? a b)
      (* (+ a b)0.5))
             (else (set! total-iterations (+ total-iterations 1))
             (cond((NOT?(>= ya yb))(set! b xb)
                         (set! xb xa)
                         (set! yb ya)
                         (set! xa (+ a (* mphi(- b a))))
                         (try a b xa (fun xa) xb yb)
                  )
                  (else    (set! a xa)
                         (set! xa xb)
                         (set! ya yb)
                         (set! xb (- b (* mphi(- b a))))
                         (try a b xa ya xb (fun xb))
                   )
             );cond...
             )
 );if...
)
(define (close-enough? x y)
  (NOT?(>= (abs (- x y)) tolerance)))
(define tolerance 0.001)
(define total-iterations 0)
(define xmin 0)
(set! xmin(golden-section-search a b))
  (display"Interval=\t[")
  (display a)
  (display" , ")
  (display b)
  (display"]\n")
  (display"Total number of iteranions=")
total-iterations
  (display"xmin=\t\t")
xmin
  (display"f(xmin)=\t")
(fun xmin)
```

Compile to C++ source code:

```
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

```

## Semantic error detection example

```
Input gramma name>j22
Gramma:j22.txt
Source>er
Source:er.ss
   1|(display"a=\t\t")
   2|a
   3|
   4|
_________________
Error[01-2] in line 2: Variable 'a' used, but not defined
   4|
     ^
Rejected!
```