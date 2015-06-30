rivalColor(white, black).
rivalColor(black, white).

m_alot(true, -3).
m_alot(false, 3).
m_infinite(true, -1000000).
m_infinite(false, 1000000).

cost(pawn, 1).
cost(rook, 5).
cost(knight, 3).
cost(bishop, 3).
cost(queen, 9).
cost(king, 100000).

addCost(Piece, OldCost, NewCost):-
    cost(Piece, Delta),
    NewCost is OldCost + Delta.
addCostSmall(Piece, OldCost, NewCost):-
    cost(Piece, Delta),
    NewCost is OldCost + max(Delta / 3, 1).
