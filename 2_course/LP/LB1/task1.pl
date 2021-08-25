
%длина списка
my_length([_|Tail],L):-
    my_length(Tail,L1),
    L is L1+1.
my_length([],L):-L is 0.

%есть ли элимент F в списке
my_member(F,[_|Tail]):-
    my_member(F,Tail).
my_member(F,[F|_]).

%список1, список2, результат
my_append([],List2,List2).
my_append([Head|Tail],List2,[Head|Tailres]):-
    my_append(Tail,List2,Tailres).

%Списток, элимент который удаляем, результат
my_remove([Item|Tail],Item,Tail).
my_remove([Head|Tail],Item,[Head|Tailres]):-
my_remove(Tail,Item,Tailres).

%Список, варианты перестановок
my_permute([],[]).
my_permute(List,[Head|Tail]):-my_remove(List,Head,Res),my_permute(Res,Tail).

%Подсписок, Список
my_sublist(Sub,List):-my_append(Sub,_,L),my_append(_,L,List).


delete_last_three_std(List,Ans):-append(Ans,Last,List),length(Last,3).
delete_last_three_std(List,[]):-length(List,L),L=<3.



delete_last_three([],[]):-!.
delete_last_three([_],[]):-!.
delete_last_three([_,_],[]):-!.
delete_last_three([_,_,_],[]):-!.
delete_last_three([Head|Tail],[Head|Tans]):-delete_last_three(Tail,Tans).


vozr([_]).
vozr([Head,H2|Tail]):-vozr([H2|Tail]),Head =< H2.


vozr_stl([_]).
vozr_stl([Head|Tail]):-vozr_stl(Tail),append([H],_,Tail),Head =< H.




%объядинение двух списков в кторых удалили по 3 послдних элимента
append_without_three(List1,List2,Ans):-delete_last_three(List1,Res1),delete_last_three(List2,Res2),my_append(Res1,Res2,Ans).
