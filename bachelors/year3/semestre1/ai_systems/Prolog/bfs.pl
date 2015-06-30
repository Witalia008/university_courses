notMember([], _).
notMember([H|T], X):-
    X =\= H,
    notMember(T, X).

member([H|_], 0, H).
member([_|T], X, R):-
    NewX is X - 1,
    member(T, NewX, R).

range(0, []).
range(X, [Nx|R]):-
    Nx is X - 1,
    range(Nx, R).

bfs(Adj, Used, _, _):-
    length(Adj, L),
    length(Used, L).
bfs(Adj, Used, [], R):-
    length(Adj, L),
    range(L, Q),
    bfs(Adj, Used, Q, R).
bfs(Adj, Used, [Qh|Qt], [Qh|R]):-
    notMember(Used, Qh),
    member(Adj, Qh, X),
    append(X, Qt, NQ),
    bfs(Adj, [Qh|Used], NQ, R).
bfs(Adj, Used, [_|Qt], R):-
    bfs(Adj, Used, Qt, R).
