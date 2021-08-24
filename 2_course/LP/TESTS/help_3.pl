swap([b,w|T],[w,b|T]).
swap([w,b|T],[b,w|T]).
swap([X|T],[X|R]):- swap(T,R).

move(S,F):-swap(S,F).

path(Start,Finish):-path(Start,Finish,[Start],Path),reverse(Path,R),write_path(R).
path(Start,Start,Path,Path).
path(Start,Finish,List,Path):-move(Start,Z),not(member(Z, List)),path(Z,Finish,[Z|List],Path).

write_path([]):-write("-------------\n").
write_path([X|L]):-write(X),write("\n"),write_path(L).
prolong([H|T],[X,H|T]):-move(H,X),not(member(X,[H|T])).
path_min(X,Y):-bdth([[X]],Y,P),reverse(P,R),write_path(R),!.
bdth([[X|T]|_],X,[X|T]).
bdth([P|QI],X,R):-findall(Z,prolong(P,Z),T),append(QI,T,QO),!,bdth(QO,X,R).


iter(1).
iter(M):-iter(N),M is N + 1.

iter_2(X):-iter_2(X,1).
iter_2(X,Y):-Y<30,X is Y.
iter_2(X,Y):-Y<30,Y1 is Y+1,iter_2(X,Y1).

search_id(Start,Finish):-iter_2(Level),search_id([Start],Finish,Path,Level),reverse(Path,P),write_path(P).
search_id([Finish|T],Finish,[Finish|T],0).
search_id(Path,Finish,R,N):-N>0, N < 30,prolong(Path,NewPath),N1 is N - 1,search_id(NewPath,Finish,R,N1).

