%gen([1,x,y],R). R=1+x+y, 1+x*y, (1+x)*y, 1*(x+y), 1*x+y.
zn(X,Y,X*Y).
zn(X,Y,X-Y).
zn(X,Y,X+Y).
zn(X,Y,X/Y).

gen_t(Y):-X = a+b,Y = X*c.

gen([H|T],R):-gen_zn(H,T,R).
gen_zn(X,[H|T],R):-length([H|T],I),I>1,gen_zn(H,T,R1),zn(X,R1,R).
gen_zn(X,[H|T],R):-length([H|T],I),I>1,zn(X,H,M),gen_zn(M,T,R).
gen_zn(X,[H],R):-zn(X,H,R).

my_append([],L2,L2).
my_append([H|T],L2,[H|Tail]):-
    my_append(T,L2,Tail).