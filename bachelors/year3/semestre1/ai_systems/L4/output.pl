writeSeq(9):- nl, !.
writeSeq(0):-
    write('   '), writeSeq(1).
writeSeq(X):-
    write('    '), write(X), write('|'),
    NewX is X + 1, writeSeq(NewX).

writeSep(10):- nl, !.
writeSep(X):-
    write('_____'),
    NewX is X + 1,
    writeSep(NewX).

% write    a single pieces
writeColor(white):- write('W').
writeColor(black):- write('B').

write_piece(pawn):- write('PA').
write_piece(king):- write('KI').
write_piece(queen):- write('QE').
write_piece(rook):- write('RO').
write_piece(knight):- write('KN').
write_piece(bishop):- write('BI').

writePiece(Color, Piece):-
    writeColor(Color),
    write('_'), write_piece(Piece).


% write at board
writePieceAt([], _, _):- write(' ... |'), !.
writePieceAt([[X, Y, C, P]|_], X, Y):-
    writePiece(C, P), write(' |').
writePieceAt([_|T], X, Y):-
    writePieceAt(T, X, Y).

writeBoardRow(_, _, 9):- !.
writeBoardRow(Board, X, Y):-
    writePieceAt(Board, Y, X),
    NewY is    Y + 1,
    writeBoardRow(Board, X, NewY).


writeBoard(_, 9):- !.
writeBoard(Board, 0):-
    writeSeq(0),
    writeBoard(Board, 1),
    writeSep(0).
writeBoard(Board, RowN):-
    writeSep(0),
    write(RowN), write(' |'),
    writeBoardRow(Board, RowN, 1), nl,
    NewRowN is RowN + 1,
    writeBoard(Board, NewRowN).

write_player(Player, Color):-
    write(Player), write('_'), write(Color), nl.









