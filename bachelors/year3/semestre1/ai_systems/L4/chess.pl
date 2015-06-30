lost(Board, _, Color):-
    not(member(Board, [_,_,Color,_])) ;
    checkmate(Board, Color).

move(user, Color, OldBoard, NewBoard, _):-
    write('From X: '),read(X),
    write('From Y: '), read(Y),
    validPos(X, Y),
    write('To X: '), read(PtX),
    write('To Y: '), read(PtY),
    validPos(PtX, PtY),
    rivalColor(Color, Col),
    makeMove(OldBoard, [X, Y, Color, _], [PtX, PtY, Col|_], NewB),
    replacePawns(user, Color, NewB, NewBoard).
move(user, Color, OldBoard, NewBoard, Depth):-
    write('Not a valid move'), nl,
    move(user, Color, OldBoard, NewBoard, Depth).

move(comp, Color, OldBoard, NewBoard, Depth):-
    worstCase(true, A),
    worstCase(false, B),
    getBestMove(OldBoard, Color, [X, Y, X1, Y1, _], A, B, Depth, true),
    rivalColor(Color, RCol),
    makeMove(OldBoard, [X, Y, Color, _], [X1, Y1, RCol, _], NewB),
    replacePawns(comp, Color, NewB, NewBoard).

% chess(Pl, chess(Player1, Player2, Color1, Color2, Board, Depth))
chess(P1, _, C1, _, B, _):-
    (lost(B, P1, C1) ->
       (write_player(P1, C1),
        write(checkmate), nl)).
chess(Player1, Player2, Color1, Color2, Board, Depth):-
    writeBoard(Board, 0),
    write_player(Player1, Color1),
    (check(Board, Color1) -> (write(check), nl); !),
    move(Player1, Color1, Board, NewBoard, Depth),
    chess(Player2, Player1, Color2, Color1, NewBoard, Depth).

chess(Player1, Player2, Color1, Color2, Board, Depth):-
    write('Not a valid move'), nl,
    chess(Player1, Player2, Color1, Color2, Board, Depth).














