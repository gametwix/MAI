


move_w([0,w|L],[w,0|L]).
move_w([0,X,w|L],[w,X,0|L]).
move_w([X|L1],[X|L2]):-move_w(L1,L2).


move_b([b,0|L],[0,b|L]).
move_b([b,X,0|L],[0,X,b|L]).
move_b([X|L1],[X|L2]):-move_b(L1,L2).

move(S,N):-move_w(S,N).
move(S,N):-move_b(S,N).
move(S,S).

path(Start,Finish):-path(Start,Finish,[Start],Path),reverse(Path,R),write_path(R).
path(Start,Start,Path,Path).
path(Start,Finish,List,Path):-move(Start,Z),not(member(Z, List)),path(Z,Finish,[Z|List],Path).
 
write_path([]):-write("-------------\n").
write_path([X|L]):-write(X),write("\n"),write_path(L).
prolong([H|T],[X,H|T]):-move(H,X),not(member(X,[H|T])).
path_min(X,Y):-bdth([[X]],Y,P),reverse(P,R),write_path(R).
bdth([[X|T]|_],X,[X|T]).
bdth([P|QI],X,R):-findall(Z,prolong(P,Z),T),append(QI,T,QO),!,bdth(QO,X,R).


iter(1).
iter(M):-iter(N),M is N + 1.

iter_2(X,M):-iter_2(X,1,M).
iter_2(X,Y,M):-Y<M,X is Y.
iter_2(X,Y,M):-Y<M,Y1 is Y+1,iter_2(X,Y1,M).

search_id(Start,Finish):-iter_2(Level,30),search_id([Start],Finish,Path,Level),reverse(Path,P),write_path(P).
search_id([Finish|T],Finish,[Finish|T],0).
search_id(Path,Finish,R,N):-N>0, N < 30,prolong(Path,NewPath),N1 is N - 1,search_id(NewPath,Finish,R,N1).



call_time(G,T) :-
    statistics(runtime,[T0|_]),
    G,
    statistics(runtime,[T1|_]),
    T is T1 - T0.