% Place your solution here


%Герман. 
%Дима единственный из нас, кто любит историю. 
%Олег и я увлекаемся одними и теми же предметами. 
%Мы все считаем биологию интереснейшей наукой. 
%Двое из нас любят и химию, и биологию. 
%Олег. 
%Нам всем очень нравится математика. 
%Герман завзятый историк. 
%В одном из увлечений мы расходимся с Димой. 
%Герман и Дима любят химию. 
%Дима. 
%Есть только один предмет, который любим мы все.
%Математикой увлекаюсь я один. 
%Каждый из нас любит разное сочетание дисциплин.
%Олег ошибается, говоря, что Герман и я увлекаемся химией. 
%Известно, что только два из утверждений каждого студента соответствуют действительности. Попробуйте сказать, какими науками увлекается каждый из них?

twoiz([Ger,Oleg,_]):- member("биология",Ger),member("химия",Ger),member("биология",Oleg),member("химия",Oleg).
twoiz([Ger,_,Dima]):- member("биология",Ger),member("химия",Ger),member("биология",Dima),member("химия",Dima).
twoiz([_,Oleg,Dima]):- member("биология",Dima),member("химия",Dima),member("биология",Oleg),member("химия",Oleg).

say(g,1,[G,O,D]):-member("история",D),not(member("история",G)),not(member("история",O)).
say(g,2,[G,O,_]):-intersect(G,O,L),length(L,3).
say(g,3,[G,O,D]):-member("биология",G),member("биология",O),member("биология",D).
say(g,4,[G,O,D]):-twoiz([G,O,D]).

say(o,1,[G,O,D]):-member("математика",G),member("математика",O),member("математика",D).
say(o,2,[G,_,_]):-member("история",G).
say(o,3,[_,O,D]):-subtract(O,D,L),length(L, 1).
say(o,4,[G,_,D]):-member("химия",G),member("химия",D).

say(d,1,[G,O,D]):-intersect(G,O,L1),intersect(D,L1,L2),length(L2, 1).
say(d,2,[G,O,D]):-not(member("математика",G)),not(member("математика",O)),member("математика",D).
say(d,3,[G,O,D]):-intersect(G,O,L1),intersect(G,D,L2),intersect(D,O,L3),
        length(L1, I1),length(L2, I2),length(L3, I3), I1 < 3,I2 < 3,I3 < 3.
say(d,4,[G,_,D]):-not(say(o,4,[G,_,D])).

check(N,S):-
        permutation([1,2,3,4],P),elems(P,T1,T2,L1,L2),
        say(N,T1,S), say(N,T2,S), not(say(N,L1,S)), not(say(N,L2,S)).
        

solve(Ger,Oleg,Dima):-
        permutation(["биология","химия","математика","история"],G),
        permutation(["биология","химия","математика","история"],O),
        permutation(["биология","химия","математика","история"],D),
        threeelem(G,Ger),threeelem(O,Oleg),threeelem(D,Dima),
        check(g,[Ger,Oleg,Dima]),check(o,[Ger,Oleg,Dima]),check(d,[Ger,Oleg,Dima]),!.


subtract([], _, []) :- !.
subtract([A|C], B, D) :-
        member(A, B), !,
        subtract(C, B, D).
subtract([A|B], C, [A|D]) :-
        subtract(B, C, D).

memb(_,[]) :- fail.
memb(X,[X|_]) :- !.
memb(X,[_|T]) :- memb(X,T).
 
intersect([],_,[]).
intersect([H|T],Y,[H|R]) :- memb(H,Y),intersect(T,Y,R), !.
intersect([_|T],Y,R) :- intersect(T,Y,R), !.

threeelem([_|Tail],Tail):-length(Tail,3).

elems([T1,T2,L1,L2],T1,T2,L1,L2).
