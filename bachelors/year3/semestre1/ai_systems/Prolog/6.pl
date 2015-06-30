append([], L, L).
append([H | T], L2, [H | Rt]):-
    append(T, L2, Rt).

prefix(A, X):- append(A, _, X).
suffix(A, X):- append(_, A, X).

sublist(SubL,X):-
    suffix(S, X),
    prefix(SubL, S).

revAcc([],A,A).
revAcc([H|T], A, R):- revAcc(T, [H|A], R).
rev(A, R):- revAcc(A, [], R).

doubled(A):- append(X, X, A).
palindrome(A):- rev(A, A).

toptail([_|At], R):-
    append(R, [_], At).

last([X], X).
last([_|T], X):-
    last(T, X).

swapfl([Ah|At],[Bh|Bt]):-
    append(X, [Bh], At),
    append(X, [Ah], Bt).
