remove([], _, []):-!.
remove([H|T], X, Res):-
    remove(T, X, NR),
    (X = H ->
       Res = NR ;
       Res = [H|NR]).

validMove(X, Y, X1, Y1):-
    A is abs(X - X1),
    B is abs(Y - Y1),
    3 is A + B, A > 0, B > 0.

getMoves([], _, _, []):-!.
getMoves([H|T], X, Y, Res):-
    H = [X1, Y1],
    getMoves(T, X, Y, R1),
    (validMove(X, Y, X1, Y1) ->
        Res = [H | R1];
        Res = R1).

iterate(_, [], _, _, Acc, Acc):-fail.
iterate(Board, [H|T], X, Y, Acc, Res):-
    H = [X1, Y1],
    (trav(Board, X1, Y1, [[X,Y]|Acc], Res);
        iterate(Board, T, X, Y, Acc, Res)).


% trav(Board, X, Y, Res).
trav([[X, Y]], X, Y, Acc, [[X,Y]|Acc]).
trav(Board, X, Y, Acc, Res):-
    remove(Board, [X,Y], Brd),
    getMoves(Brd, X, Y, B),
    iterate(Brd, B, X, Y, Acc, Res).


doIt:-
    fillB(1, 1, B),
    trav(B, 1, 5, [], X),
    outputB(1, 1, X).




fillB(9, 1, []):- !.
fillB(X, 9, R):-
    NewX is X + 1,!,
    fillB(NewX, 1, R).
fillB(X, Y, R):-
    NewY is Y + 1,!,
    fillB(X, NewY, NR),
    R = [[X, Y]|NR].

find([], _, _, -1):-!.
find([H|_], H, Cnt, Cnt):-!.
find([_|T], El, Cnt, Res):-
    NewC is Cnt + 1,
    find(T, El, NewC, Res).





outputC(X):-
    write(X),
    (X < 10 ->
        write('   ');
        write('  ')).
outputB(9, 1, _):-!.
outputB(X, 9, B):-
    nl,
    NewX is X + 1,
    outputB(NewX, 1, B).
outputB(X, Y, B):-
    NewY is Y + 1,
    find(B, [X, Y], 0, Pos),
    outputC(Pos),
    outputB(X, NewY, B).















