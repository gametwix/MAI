subst(X,Z1,Z2,Res):-X=..[A,B,C],subst(B,Z1,Z2,B1),subst(C,Z1,Z2,C1),Res=..[A,B1,C1],!.
subst(Z1,Z1,Z2,Z2):-!.
subst(X,Z1,_,X):-X\=Z1,!.


add_new(X,List,[X|List]):-not(member(X, List)).
cifra(X):-member(X,[0,1,2,3,4,5,6,7,8,9]).
to_int([H|T],R):-to_int([H|T],0,R).
to_int([H|T],Hv,R):-Hv1 is Hv*10 + H,to_int(T,Hv1,R).
to_int([],Hv,Hv).
comb(O,D,I,N,M,G):-cifra(O),add_new(O,[],L1),
    cifra(D),add_new(D,L1,L2),
    cifra(I),add_new(I,L2,L3),
    cifra(N),add_new(N,L3,L4),
    cifra(M),add_new(M,L4,L5),
    cifra(G),add_new(G,L5,_),
    to_int([O,D,I,N],Odin), to_int([M,N,O,G,O],Mnogo),
    Mnogo is Odin+Odin.

%?- comb(O,D,I,N,M,G).
%O = 6,
%D = 8,
%I = 2,
%N = 3,
%M = 1,
%G = 4 ;

merge([],Res,Res).
merge(Res,[],Res).
merge([H1|T1],[H2|T2],[H1|Res1]):-H1<H2,merge(T1,[H2|T2],Res1).
merge([H1|T1],[H2|T2],[H2|Res1]):-H1>=H2,merge([H1|T1],T2,Res1).



