kr_tri(X):- M is X mod 3, M = 0.

f_min([H|_],H):-kr_tri(H),!.
f_min([_|T],X):-f_min(T,X).

min_tri(List,X):-f_min(List,H),min_tri(List,H,X).
min_tri([H|T],Hv,X):-kr_tri(H),H<Hv,min_tri(T,H,X).
min_tri([H|T],Hv,X):-kr_tri(H),H>=Hv,min_tri(T,Hv,X).
min_tri([H|T],Hv,X):-not(kr_tri(H)),min_tri(T,Hv,X).
min_tri([],Hv,Hv):-!.
