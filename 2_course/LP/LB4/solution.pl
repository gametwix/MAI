:-op(200, xfy,:).



parent(alexei,tolia).
parent(alexei,volodia).
parent(tolia,tima).
parent(volodia,sasha).
parent(volodia,mitia).

brat(X,Y):-parent(X1,X),parent(X1,Y),X\=Y.
brat(X,Y,yes):-brat(X,Y),!.
brat(X,Y,no):-not(brat(X,Y)).

parent(X,Y,yes):-parent(X,Y),!.
parent(X,Y,no):-not(parent(X,Y)).

swi_ped(otez,X,Predic):-parent(X,Predic).
swi_ped(brat,X,Predic):-brat(X,Predic).

swi_ped(brat,X,Y,Predic):-brat(X,Y,Predic).
swi_ped(otez,X,Y,Predic):-parent(X,Y,Predic).

gen1(File1):-File1=[
    alexei:sost("именит"):[alexei],
    tolia:sost("именит"):[tolia],
    volodia:sost("именит"):[volodia],
    tima:sost("именит"):[tima],
    sasha:sost("именит"):[sasha],
    mitia:sost("именит"):[mitia],
    alexei:sost("родит"):[alexia],
    tolia:sost("родит"):[toli],
    volodia:sost("родит"):[volodi],
    tima:sost("родит"):[timi],
    sasha:sost("родит"):[sashi],
    mitia:sost("родит"):[miti],
    alexei:sost("прит"):[alexein],
    tolia:sost("прит"):[tolin],
    volodia:sost("прит"):[volodin],
    sasha:sost("прит"):[sashin],
    mitia:sost("прит"):[mitin],
    tima:sost("прит"):[timin]].

gen2(File2):-File2=[
    kto:sost("именит"):[kto],
    kto:sost("прит"):[chei],
    brat:sost("предикат"):[brat],
    otez:sost("предикат"):[otez]].






fid(X, XC, K, File):-member(M,File), condition(X, XC, K, M).
condition(X, XC, K, XC:K:L):-member(X, L).
an_phrase([X,Y,Z,"?"],Predic) :-an_obj(X1, sost("именит"), X), an_funct(X2, sost("предикат"),Y),an_obj(X3, sost("родит"),Z),swi_ped(X2,X1,X3,Predic).
an_phrase([X,Y,Z,"?"],Predic) :-an_funct(_, sost("именит"), X), an_obj(X2, sost("прит"),Y), an_funct(X3, sost("предикат"),Z),swi_ped(X3,Predic,X2).
an_phrase([X,Y,Z,"?"],Predic) :-an_funct(_, sost("прит"), X), an_funct(X2, sost("предикат"),Y),an_obj(X3, sost("именит"),Z), swi_ped(X2,X3,Predic).
an_obj(XC, K,X) :-gen1(File1),fid(X, XC, K, File1).
an_funct(XC, K, Y) :-gen2(File2),fid(Y, XC, K, File2).


