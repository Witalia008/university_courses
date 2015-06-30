firstCol([], []).
firstCol([[Rh|_]|At], [Rh|Rt]):-
    firstCol(At, Rt).

lastCols([], []).
lastCols([[_]|_], []).
lastCols([[_|Rh]|At], [Rh|Rt]):-
    lastCols(At, Rt).

transp([], []).
transp(A, [H|T]):-
    firstCol(A, H),
    lastCols(A, Tx),
    transp(Tx, T).

cont(_, 0, _, [], []).
cont(_, 0, X, [Y|L], [Y|L]):-
    Y is 1-X.
cont(gen, N, Wh, [Wh|T], Rest):-
    cont(gen, NewN, Wh, T, Rest),
    N is NewN + 1.
cont(chk, N, Wh, [Wh|T], Rest):- N > 0,
    NewN is N - 1,
    cont(chk, NewN, Wh, T, Rest).


goodRow([], F):-
    cont(gen, _, 0, F, []).

goodRow([Ph|Pt], [0|F]):-
    cont(gen, _, 0, F, Fx),
    cont(chk, Ph, 1, Fx, Fy),
    goodRow(Pt, Fy).

goodRows([], []).
goodRows([Ph|Pt], [Fh|Ft]):-
    goodRow(Ph, [0|Fh]),
    goodRows(Pt, Ft).

rect(0, _, []).
rect(A, B, [Rh|Rt]):-
    length(Rh, B),
    NewA is A - 1,
    rect(NewA, B, Rt).


solution(Left, Up, Field):-
    length(Left, R),
    length(Up, C),
    rect(R, C, Field),
    transp(Field, FieldR),
    goodRows(Left, Field),
    goodRows(Up, FieldR).

writeList([]):- writeln('').
writeList([0|T]):-
    write(' '),
    writeList(T).
writeList([1|T]):-
    write('*'),
    writeList(T).

writeMatr([]).
writeMatr([H|T]):-
    writeList(H),
    writeMatr(T).





