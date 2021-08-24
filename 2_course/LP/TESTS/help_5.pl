female('Maria Kruglova').
female('Anna Fadeeva').
female('Galina Nikolina').
female('Natalia Smeyan').
female('Hatalia Kruglova').
female('Alexandra Nignikova').
female('Antonina Nikolina').
female('Nina Nikolina').
female('Elizabeth Nikolina').
female('Olga Ryzhikova').
female('Galina Smeyan').
female('Victoria Simkina').
female('Olga Armyitseva').
female('Alina Armyitseva').
female('Vasilisa Ostrovskaya').
female('Irina Sokolova').
male('Sergey Kruglov').
male('Boris Kruglov').
male('Vladimir Fadeev').
male('Sergey Lebedev').
male('German Black').
male('Alex Kruglov').
male('Sergey Nikolin').
male('Nick Smeyan').
male('Evgeniy Maslennicov').
male('Dmitriy Maslennicov').
male('Dmitriy Epifanov').
male('Ivan Epifanov').
male('Eremey Epifanov').
male('Efim Simkin').
male('Anton Armyitsev').
male('Nick Kruglov').
male('Vasiliy Fadeev').
male('Karl Kruglov').

child('Sergey Kruglov', 'Maria Kruglova').
child('Anna Fadeeva', 'Maria Kruglova').
child('Sergey Kruglov', 'Alex Kruglov').
child('Anna Fadeeva', 'Alex Kruglov').
child('Boris Kruglov', 'Hatalia Kruglova').
child('Galina Nikolina', 'Hatalia Kruglova').
child('Boris Kruglov', 'Karl Kruglov').
child('Galina Nikolina', 'Karl Kruglov').
child('Boris Kruglov', 'Sergey Kruglov').
child('Galina Nikolina', 'Sergey Kruglov').
child('Vladimir Fadeev', 'Anna Fadeeva').
child('Natalia Smeyan', 'Anna Fadeeva').
child('German Black', 'Sergey Lebedev').
child('Hatalia Kruglova', 'Sergey Lebedev').
child('Sergey Nikolin', 'Galina Nikolina').
child('Alexandra Nignikova', 'Galina Nikolina').
child('Sergey Nikolin', 'Antonina Nikolina').
child('Alexandra Nignikova', 'Antonina Nikolina').
child('Sergey Nikolin', 'Nina Nikolina').
child('Alexandra Nignikova', 'Nina Nikolina').
child('Sergey Nikolin', 'Elizabeth Nikolina').
child('Alexandra Nignikova', 'Elizabeth Nikolina').
child('Nick Smeyan', 'Natalia Smeyan').
child('Olga Ryzhikova', 'Natalia Smeyan').
child('Nick Smeyan', 'Galina Smeyan').
child('Olga Ryzhikova', 'Galina Smeyan').
child('Dmitriy Maslennicov', 'Evgeniy Maslennicov').
child('Galina Smeyan', 'Evgeniy Maslennicov').
child('Ivan Epifanov', 'Eremey Epifanov').
child('Antonina Nikolina', 'Eremey Epifanov').
child('Ivan Epifanov', 'Dmitriy Epifanov').
child('Antonina Nikolina', 'Dmitriy Epifanov').
child('Efim Simkin', 'Victoria Simkina').
child('Nina Nikolina', 'Victoria Simkina').
child('Anton Armyitsev', 'Olga Armyitseva').
child('Victoria Simkina', 'Olga Armyitseva').
child('Anton Armyitsev', 'Alina Armyitseva').
child('Victoria Simkina', 'Alina Armyitseva').
child('Nick Kruglov', 'Boris Kruglov').
child('Irina Sokolova', 'Boris Kruglov').
child('Vasiliy Fadeev', 'Vladimir Fadeev').
child('Vasilisa Ostrovskaya', 'Vladimir Fadeev').

dever(X,Y,Z) :- child(X, L), child(Z, L), male(X), male(Y), female(Z), child(R, X), child(R, Y), X\=Y.


father(X,Y):-child(X,Y), male(X).
mother(X,Y):-child(X,Y), female(X).

nameis(mother(_,_),mother).
nameis(father(_,_),father).
nameis(child(_,_),child).

move(X,Y):-mother(Y,X).
move(X,Y):-father(Y,X).
move(X,Y):-child(X,Y).

move_pred(X,Y,Pred):-mother(Y,X),nameis(mother(Y,X),Pred).
move_pred(X,Y,Pred):-father(Y,X),nameis(father(Y,X),Pred).
move_pred(X,Y,Pred):-child(X,Y),nameis(child(Y,X),Pred).

prolong([H|T],[X,H|T]):-move(H,X),not(member(X,[H|T])).
path_min(X,Y,R):-bdth([[X]],Y,P),reverse(P,R).
bdth([[X|T]|_],X,[X|T]).
bdth([P|QI],X,R):-findall(Z,prolong(P,Z),T),append(QI,T,QO),!,bdth(QO,X,R).

path_to_rel([_],Rez,Rez).
path_to_rel([X,Y|Tail],Rel,Rez):-move_pred(X,Y,Pred),path_to_rel([Y|Tail],[Pred|Rel],Rez).
path_to_rel(Path,Rez):-path_to_rel(Path,[],Rez).

%relative(Rez,X,Y):-move_pred(X,Y,Rez).
relative(Rez,X,Y):-path_min(X,Y,Path),path_to_rel(Path,R),rez_to_format(R,Rez).

rez_to_format([Rez],Rez).
rez_to_format([Head|Tail],Rez):-minus(Head,Tail,Rez).

minus(H,[H1],Rez):-Rez = H - H1.
minus(H,[Head|Tail],Rez):-T = H - Head, minus(T, Tail,Rez).