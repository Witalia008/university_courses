getEl([], X, _):-
    X = wolf; X = cabbage; X = goat.
getEl([H|T], H, T).
getEl([H|T], X, [H|P]):-
    getEl(T, X, P).

good([]).
good([goat]).
good([wolf]).
good([cabbage]).
good([wolf, cabbage]).
good([cabbage, wolf]).

trav(right, [], _, [], _, _).
trav(left, Left, Right, R, MD, Depth):- Depth =< MD,
    getEl(Left, X, L),
    good(L),
    good(Right),
    NewD is Depth + 1,
    trav(right, L, [X|Right], P, MD, NewD),
    R = [[left, X]|P].
trav(left, Left, Right, [[left]|R], MD, Depth):- Depth =< MD,
    good(Left), good(Right),
    NewD is Depth + 1,
    trav(right, Left, Right, R, MD, NewD).

trav(right, Left, Right, [[right]|R], MD, Depth):- Depth =< MD,
    good(Left), good(Right),
    NewD is Depth + 1,
    trav(left, Left, Right, R, MD, NewD).

trav(right, Left, Right, Res, MD, Depth):- Depth =< MD,
    getEl(Right, X, R),
    good(Left),
    good(R),
    NewD is Depth + 1,
    trav(left, [X|Left], R, P, MD, NewD),
    Res = [[right,X]|P].




