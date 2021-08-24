count([],0,0).
count([H|T],A,B):-H="(",count(T,A1,B),A is A1 + 1.
count([H|T],A,B):-H=")",count(T,A,B1),B is B1 + 1.
count([H|T],A,B):-H\=")",H\="(",count(T,A,B).


oposit("(",")").
oposit("{","}").
oposit("[","]").


withoutlast(List1,List2):-append(List2,X,List1),length(X, 1).
last([X],X).
last([_|T],X):-last(T,X).
check([]).
check([H|T]):-last(T,Last),oposit(H,Last),withoutlast(T,List),check(List).
