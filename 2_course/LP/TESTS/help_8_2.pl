cmb(S1,S2,R):-
    R=S1 + S2.
    cmb(S1,S2,R):-
    R=S1 - S2.
    cmb(S1,S2,R):-
    R=S1 * S2.
    cmb(S1,S2,R):-
    R=S1 / S2.
    
    
    
    gen(ArgList,R):-
    append(Lis1,Lis2,ArgList),
    %member(_,Lis1),member(_,Lis2),
    not(length(Lis1,0)),not(length(Lis2,0)),
    gen(Lis1,R1),
    gen(Lis2,R2),
    cmb(R1,R2,R).
    gen([S],S).

