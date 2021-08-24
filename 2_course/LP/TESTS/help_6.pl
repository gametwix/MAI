
razb(X,List):-X=..[A,B,C],razb(B,List1),razb(C,List2),string_chars(A,Op),append(Op,List1,Listh),append(Listh,List2,List),!.
razb(X,[X]):-integer(X),!.


del_last([_],[]).
del_last([H|T1],[H|T2]):-del_last(T1,T2).


subst(Z1,Z2,X,Res):-X=..[A,B,C],subst(Z1,Z2,B,B1),subst(Z1,Z2,C,C1),Res=..[A,B1,C1],!.
subst(Z1,Z2,Z1,Z2):-!.
subst(Z1,_,X,X):-X\=Z1,!.