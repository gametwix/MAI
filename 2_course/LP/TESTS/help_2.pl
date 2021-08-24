true(true).

check("~",X,true):-not(true(X)).
check("~",X,false):-true(X).

check("V", X, Y,true):- true(X), true(Y).
check("V", X, Y,true):- not(true(X)), true(Y).
check("V", X, Y,true):- true(X), not(true(Y)).
check("V", X, Y,false):- not(true(X)), not(true(Y)).

check("^", X, Y,true):-  true(X), true(Y).
check("^", X, Y,false):-  not(true(X)), true(Y).
check("^", X, Y,false):-  not(true(Y)), true(X).
check("^", X, Y,false):-  not(true(X)), not(true(Y)).

check("=>",X,Y,true):-true(X),true(Y).
check("=>",X,Y,true):-not(true(X)),true(Y).
check("=>",X,Y,true):-not(true(X)),not(true(Y)).
check("=>",X,Y,false):-true(X),not(true(Y)).


cal(Expr,Val):-reverse(Expr,Expr1),a_term(Expr1,Val).
a_term([X],X).
a_term(T,V):-append([X],["V"|Y],T),a_term(Y,Vy),check("V",X,Vy,V).
a_term(T,V):-append([X],["~"|_],T),check("~",X,V).
a_term(T,V):-append([X],["^"|Y],T),a_term(Y,Vy),check("^",X,Vy,V).
a_term(T,V):-append([X],["=>"|Y],T),a_term(Y,Vy),check("=>",Vy,X,V).


my_sublist(List,Sub):-append(_,X1,List),append(X2,_,X1),X2 = Sub.
naim(List,X):-my_sublist(List,SK),my_sublist(SK,X),
    not(member("(",X)),not(member(")",X)),append(["("],X,X1),append(X1,[")"],SK),!.

replace(List,U,V,List_ex):-append(St,X1,List),append(X2,Fi,X1),X2 = U,
    append(St,V,List_ned),append(List_ned,Fi,List_ex),!.


all_rep(List,X):-naim(List,X1),cal(X1,Val),
    append(["("],X1,X2), append(X2,[")"],X3),
    replace(List,X3,[Val],L),all_rep(L,X).
all_rep(List,List):-not(member("(",List)),not(member(")",List)).


calculate(Expr,Val):-all_rep(Expr,X),cal(X,Val).


