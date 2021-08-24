length_list([], 0) :- !.
length_list([_Head | Tail], Int) :-
    length_list(Tail, TailInt),
    Int = TailInt + 1.

%быстрые работает, но использует вспомогательную функцию Buffer
%length_list_2(List, Int):-
%   length_list_2(List, 0, Int).
%length_list_2([], Int, Int):-!.
%length_list_2([_Head|Tail], Buffer, Int):-
%   NewBuffer is Buffer + 1,
%   length_list_2(Tail, NewBuffer, Int). */

member(X, [X | _Tail]) :-!.
member(X, [_Head | Tail]) :-
    member(X, Tail). 

%когда нужно вернуть элемент, если есть вхождение
%member(X, X, [X | _Tail]) :-!.
%member(X, X, [_Head | Tail]) :-
%    member(X, X, Tail). */

append([], List2, List2).
append([Head | Tail], List2, [Head | TailResult]) :-
    append(Tail, List2, TailResult).


%моя реализация удаления ВСЕХ вхождений заданого элемента,
%не подходит для permute(((, там требуется удаление один раз!
remove_all([], _Element, []) :- !.
remove_all([Element | Tail], Element, ResultTail) :-
    remove_all(Tail, Element, ResultTail), !.
remove_all([Head | Tail], Element, [Head | ResultTail]) :-
    remove_all(Tail, Element, ResultTail).

%реализация из лекции, использовал в permute
remove([Element | Tail], Element, Tail).
remove([Head | Tail], Element, [Head | ResultTail]):-
    remove(Tail, Element, ResultTail).

%взял из лекции
permute([], []).
permute(List, [X | Tail]) :-
    remove(List, X, ResultTail),
    permute(ResultTail, Tail).

%sub_start - вспомогательная функция
sub_start([], _List).
sub_start([Head|TailSub], [Head|TailList]):-
   sub_start(TailSub, TailList).

sublist(Sub, List):-
   sub_start(Sub, List).
sublist(Sub, [_Head|Tail]):-
   sublist(Sub, Tail).

%нашел красивый поиск в учебнике
sublist_append(List, Sub, Left, Right):-
    append(Left, CenterRight, List),
    append(Sub, Right, CenterRight),
    \+ (Sub = []).

%удаление по индексу без использования других предикатов
remove_index([_Head | Tail], 0, Tail) :- !.
remove_index(_List, Index, _Result) :-
    Index < 0, !, fail.
remove_index([Head | Tail], Index, [Head | ResultTail]) :-
    NextIndex is Index - 1,
    remove_index(Tail, NextIndex, ResultTail). 



%удаление по индексу с использование вспомогательной функции и стандартного придеката
remove_index_ap(Start,Ind,Finish):-length(Start, L), L > Ind, append(Head,[_|Tail],Start),length(Head, L1),L1 = Ind,append(Head,Tail,Finish) .



 
sum_list([], [], []):-!.
sum_list([Head_1|Tail_1], [Head_2|Tail_2], [Head|Tail]):-
   sum_list(Tail_1, Tail_2, Tail),
   Head is Head_1 + Head_2.


sum_list_ap([],[],[]).
sum_list_ap(List1, List2, Res):-append([H1],T1,List1),append([H2],T2,List2),
Sum is H1 + H2, sum_list_ap(T1,T2,TRes), append([Sum],TRes,Res).
    





