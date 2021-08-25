% Task 2: Relational Data

% The line below imports the data
:- ['two.pl'].



ball_list_for_less(Less,List):-findall(X,grade(_,_,Less,X),List).

all_less(List):-
    findall(X,grade(_,_,X,_),Listf),
    setof(L,member(L,Listf),List).

sum_list([],Sum):- Sum is 0.
sum_list([Head|Tail],Sum):-sum_list(Tail,S2),Sum is S2+Head.


singl_elem([Head|_],X):- X = Head.
singl_elem([_|Tail],X):-singl_elem(Tail,X).

mid_ball(Less,X):-
    ball_list_for_less(Less,Balllist),
    sum_list(Balllist,Sum),
    length(Balllist, Leng),
    X is Sum / Leng.

mid_ball:-
    all_less(Less_list),
    singl_elem(Less_list,Less),
    mid_ball(Less,X),
    write(Less),write("-"),write(X),nl.




ne_sdal(Group,Fam,Less):-grade(Group,Fam,Less,2).
ne_sdal_group(Group,Count):-
    findall(Fam,ne_sdal(Group,Fam,_),List1),
    setof(L,member(L,List1),List2),
    length(List2,Count).

ne_sdal_all_group:-
    findall(Groups,grade(Groups,_,_,_),List1),
    setof(L,member(L,List1),List),
    singl_elem(List,Group),
    ne_sdal_group(Group,Count),
    write(Group),write("-"),write(Count),nl.


ne_sdal_less(Less,Count):-
    findall(Fam,ne_sdal(_,Fam,Less),List1),
    setof(L,member(L,List1),List2),
    length(List2,Count).

ne_sdal_all_less:-
    findall(Less,grade(_,_,Less,_),List1),
    setof(L,member(L,List1),List),
    singl_elem(List,Lesson),
    ne_sdal_less(Lesson,Count),
    write(Lesson),write("-"),write(Count),nl.

