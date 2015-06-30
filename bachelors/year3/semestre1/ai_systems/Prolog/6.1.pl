member(H, [H|_]).
member(X, [_|T]):-
    member(X, T).

next(A, B, [A,B|_]).
next(A, B, [_|T]):-
    next(A, B, T).

solve(Sol):-
    length(Sol, 3),
    member([english, red, _], Sol),
    member([spanish, _, jaguar], Sol),
    next([_, _, snail], [japanese, _, _], Sol),
    next([_, _, snail], [_, blue, _], Sol),
    member([_, _, zebra], Sol),
    member([_, green, _], Sol).

zebra(X):-
    solve(Y),
    member([X, _, zebra], Y).
