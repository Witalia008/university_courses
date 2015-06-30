% [PosX, PosY, Color, Piece]
% validMove([X, Y, Color, Piece], NewX, NewY)

validPos(X, Y):-
    X >= 1, X =< 8, Y >= 1, Y =< 8.

isRealMove(X, Y, Px, Py):-
    Px =\= X ; Py =\= Y.

% Check pawns
validMove([X, Y, white, pawn], X, PtY):- isRealMove(X, Y, X, PtY),
    (Y == 2 ->
    (PtY =< 4, PtY >= 3) ;
    PtY is Y + 1).
validMove([X, Y, black, pawn], X, PtY):- isRealMove(X, Y, X, PtY),
    (Y == 7 ->
    (PtY =< 6, PtY >= 5) ;
    PtY is Y - 1).

% Check King
validMove([X, Y, _, king], PtX, PtY):- isRealMove(X, Y, PtX, PtY),
    Xdiff is abs(PtX - X),
    Ydiff is abs(PtY - Y),
    Xdiff =< 1, Ydiff =< 1,
    Xdiff + Ydiff >= 0.

% Check Queen
validMove([X, Y, _, queen], PtX, PtY):- isRealMove(X, Y, PtX, PtY),
    Xdiff is abs(PtX - X),
    Ydiff is abs(PtY - Y),
    Xdiff + Ydiff >= 0,
        (Xdiff == Ydiff ; Ydiff == 0 ; Xdiff == 0).


% Check Rook
validMove([X, Y, _, rook], PtX, PtY):- isRealMove(X, Y, PtX, PtY),
    (PtX is X , abs(PtY - Y) > 0);
    (PtY is Y , abs(PtX - X) > 0).

% Check Bishop
validMove([X, Y, _, bishop], PtX, PtY):- isRealMove(X, Y, PtX, PtY),
    Xdiff is abs(PtX - X),
    Ydiff is abs(PtY - Y),
    Xdiff == Ydiff,
    Xdiff + Ydiff > 0.

% Check Knight
validMove([X, Y, _, knight], PtX, PtY):- isRealMove(X, Y, PtX, PtY),
    Xdiff is abs(PtX - X),
    Ydiff is abs(PtY - Y),
    Xdiff + Ydiff is 3,
    Xdiff > 0, Ydiff > 0.


% Kill moves
killMove([X, Y, Color, pawn], PtX, PtY):- isRealMove(X, Y, PtX, PtY),
    1 is abs(PtX - X),
    (Color = white -> Y is PtY - 1 ; Y is PtY + 1).

killMove([X, Y, Color, Piece], PtX, PtY):- isRealMove(X, Y, PtX, PtY),
    Piece \= pawn,
    validMove([X, Y, Color, Piece], PtX, PtY).


underAttack(Board, [H|T], [X1, Y1, C1, _]):-
    (H = [X, Y, C, P],
    rivalColor(C, C1),
    (countInBetween([H|T], X, Y, X1, Y1, 0, 2);
    countInBetween([H|T], X, Y, X1, Y1, 0, 1)),
    killMove([X,Y,C,P], X1, Y1))
    ; underAttack(Board, T, [X1, Y1, C1, _]).

underAttackL(_, _, _, _, []).
underAttackL(Board, X, Y, Color, [[Dx,Dy]|T]):-
    Nx is X + Dx, Ny is Y + Dy,
    (not(validPos(Nx, Ny)) ;
    underAttack(Board, Board, [Nx,Ny,Color,_])
    ),
    underAttackL(Board, X, Y, Color, T).


dist(X1, Y1, X2, Y2, R):-
    R is sqrt((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1)).

eq(A, B):-
    Del is abs(A - B),
    Del =< 0.000000001.
inBetween(X, Y, X1, Y1, X2, Y2):-
    dist(X1, Y1, X2, Y2, Left),
    dist(X, Y, X1, Y1, A),
    dist(X, Y, X2, Y2, B),
    Right is A + B,
    eq(Left, Right).


%  countInBetween(Board, X1, Y1, X2, Y2, Acc, Count)
countInBetween([],_,_,_,_,A,A).
countInBetween([[X,Y|_]|T], X1, Y1, X2, Y2, Acc, C):-
    (inBetween(X,Y,X1,Y1,X2,Y2) ->
    NewC is Acc + 1
    ; NewC is Acc),
    countInBetween(T, X1, Y1, X2, Y2, NewC, C).

member([H|_], H).
member([H|T], X):-
    X \= H,
    member(T, X).

% removePiece(Board, X, Y, NewBoard).
removePiece([], _, _, _).
removePiece([[X, Y|_]|R], X, Y, R).
removePiece([H|T], X, Y, [H|R]):-
    H \= [X, Y|_],
    removePiece(T, X, Y, R).

% movePiece(Board, X1, Y1, X2, Y2, R).X1, Y1, C1, P1]
movePiece([],_,_,_,_,_).
movePiece([[X1,Y1|CP1]|T], X1, Y1, X2, Y2, [[X2,Y2|CP1]|T]).
movePiece([H|T], X1, Y1, X2, Y2, [H|R]):-
    H \= [X1, Y1|_],
    movePiece(T, X1, Y1, X2, Y2, R).

% Kill other player's piece
makeMove(Old, [X1, Y1, C1, P1], [X2, Y2|CP2], New):-
    member(Old, [X2,Y2|CP2]),
    member(Old, [X1,Y1,C1,P1]),
    (P1 \= king ;
    not(underAttack(Old, Old, [X2,Y2,C1,_]))),
    countInBetween(Old, X1, Y1, X2, Y2, 0, 2),
    killMove([X1,Y1,C1,P1], X2, Y2),
    removePiece(Old, X2, Y2, New1),
    movePiece(New1, X1, Y1, X2, Y2, New).

% just move
makeMove(Old, [X1, Y1,C1,P1], [X2, Y2|_], New):-
    member(Old, [X1,Y1,C1,P1]),
    not(member(Old, [X2,Y2,_,_])),
    (P1 \= king ;
    not(underAttack(Old, Old, [X2,Y2,C1,_]))),
    countInBetween(Old, X1, Y1, X2, Y2, 0, 1),
    validMove([X1,Y1,C1,P1], X2, Y2),
    movePiece(Old, X1, Y1, X2, Y2, New).

check(Board, Color):-
    member(Board, [X,Y,Color,king]),
    underAttack(Board, Board, [X,Y,Color,king]).

getSurrList([[-1, -1], [-1, 0], [-1, 1],
         [0, -1], [0, 1],
         [1, -1], [1, 0], [1, 1]]).

checkmate(Board, Color):-
    not(member(Board, [_,_,Color,king])) ;
    (check(Board, Color),
    member(Board, [X,Y,Color,king]),
    getSurrList(L),
    underAttackL(Board, X, Y, Color, L)).

getPawnRepl(user, NewP):-
    write('Desired Piece: '), read(NewP).
getPawnRepl(comp, queen).

replacePawns(_, _,[],[]).
replacePawns(Player, Color, [H|T], [H|R]):-
    H \= [_,_,Color,pawn],
    replacePawns(Player, Color, T, R).
replacePawns(Player, Color, [H|T], [Rh|Rt]):-
    H = [X,Y,Color,pawn],
    (Color = white -> Lim is 8 ; Lim is 1),
    (Y is Lim -> getPawnRepl(Player, NewP) ; NewP = pawn),
    Rh = [X,Y,Color,NewP],
    replacePawns(Player, Color, T, Rt).











