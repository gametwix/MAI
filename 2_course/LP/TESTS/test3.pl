text-->append([]).
p([_]).
p([_,_|X]):-p(X).

last(L,Last):-append(_,[Last],L).

fib(1,1).
fib(2,1).
fib(N,R):-fib(N,R,3,1,1).
fib(N,N3,H,N1,N2):-N = H,N3 is N1 + N2,!.
fib(N,R,H,N1,N2):-N>H,N3 is N1 + N2,H1 is H + 1,fib(N,R,H1,N2,N3).

fact(0,1).
fact(X,R):-fact(X,1,1,R).
fact(X,N,H,R):-X>N,H1 is H*N,N1 is N + 1,fact(X,N1,H1,R).
fact(X,N,H,H1):-X=N,H1 is H*N,!.

v([_|T],N):-v(T,N1),N1 = N -1.

maxeven([_],0).
maxeven([X|T],R):-maxeven([X|T],0,R).
maxeven([_],M,M).
maxeven([_,H2],_,H2).
maxeven([_,H2|T],M,R):-M2 is max(H2, M),maxeven(T,M2,R).

max_my([H],R):- max_member(R, H).
max_my([H|T],R):-max_my([H|T],0,R).
max_my([],M,M).
max_my([H|T],M,R):-max_member(R2, H),write(R2),M2 is max(R2, M),max_my(T,M2,R).