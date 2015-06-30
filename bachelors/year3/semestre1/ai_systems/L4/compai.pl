countCol([], _, 0):- !.
countCol([[_,_,Col,P]|T], Col, R):-
    countCol(T, Col, NR),
    addCost(P, NR, R).
countCol([_|T], Col, R):-
    countCol(T, Col, R).

countAtt(_, [], _, 0).
countAtt(Board, [H|T], Color, Cnt):-
    H = [_,_,_,P],
    countAtt(Board, T, Color, NewCnt),
    ((H = [_,_,Color,P], underAttack(Board, Board, H)) ->
       addCostSmall(P, NewCnt, Cnt)
       ;  Cnt is NewCnt).

dangerCount(Board, Color, Cnt, Max):-
    (checkmate(Board, Color) ->
       m_infinite(Max, Cnt)
       ;  (check(Board, Color) ->
              m_alot(Max, Cnt)
              ;  Cnt is 0)).

func(Board, Color, F, Max):-
    rivalColor(Color, RCol),
    dangerCount(Board, Color, CntX, Max),
    dangerCount(Board, RCol, CntY, Max),
    countCol(Board, Color, Cnt1),
    countCol(Board, RCol, Cnt2),
    countAtt(Board, Board, Color, Cnt3),
    countAtt(Board, Board, RCol, Cnt4),
    %write(Cnt1),nl,write(Cnt2),nl,
    %write(Cnt3),nl,write(Cnt4),nl,
    %write(CntX),nl,write(CntY),nl,
    F is Cnt1 - Cnt2 + Cnt4 - Cnt3 + CntX * 2 - CntY.

% this is not my piece
generateChildren(_, H, _, _, C, []):-
    H \= [_,_,C,_],!.
% all cells considered
generateChildren(_, _, 9, 1, _, []):-!.
% next row needs to be considered
generateChildren(Board, H, X, 9, C, R):-
    Nx is X + 1,
    generateChildren(Board, H, Nx, 1, C, R).
% consider current cell
generateChildren(Board, [X,Y,Color,_], X1, Y1, Color, R):-
    rivalColor(Color, RCol),
    (makeMove(Board, [X,Y,Color,_], [X1,Y1,RCol,_], NewB) ->
        Cur = [[[X,Y,X1,Y1,_],NewB]]
        ; Cur = []),
    Ny is Y1 + 1,
    generateChildren(Board, [X,Y,Color,_], X1, Ny, Color, Rx),
    append(Cur, Rx, R).

generateChildrenL(_, [], _, []):-!.
generateChildrenL(Board, [H|T], Color, R):-
    generateChildrenL(Board, T, Color, L),
    generateChildren(Board, H, 1, 1, Color, X),
    append(X, L, R).

% getBestMove(Board, Color, Result, Alpha, Beta, Depth, Maximize)
% Result = [Xfrom, Yfrom, Xto, Yto, Func]
getBestMove(Board, Color, [X,Y,X1,Y1,F], A, B, Depth, Max):-
    rivalColor(Color, RCol),
    ((Depth is 0
       ; checkmate(Board, Color)
       ; checkmate(Board, RCol)) ->
          func(Board, Color, F, Max);
    (generateChildrenL(Board, Board, Color, Kids),
    % write(Kids),nl,
    % get just first variant
    % getMaximum(Color, Kids, [X,Y,X1,Y1,_]),nl
     (Max = true -> WCVal is A ; WCVal is B),
     iterateChildren(Kids, Board, Color, [_,_,_,_,WCVal],
            [X,Y,X1,Y1,F],A,B,Depth,Max)
    )).

opposite(true, false).
opposite(false, true).
worstCase(true, -100000000).
worstCase(false, 100000000).
changeCoef(true, A, B, NA, B, F):-
    NA is max(A, F).
changeCoef(false, _, B, F, NB, F):-
    NB is min(B, F).

chooseBest(true, Move1, Move2, Res):-
    Move1 = [_,_,_,_,F1],
    Move2 = [_,_,_,_,F2],
    (F1 >= F2 -> Res = Move1 ; Res = Move2).
chooseBest(false, Move1, Move2, Res):-
    Move1 = [_,_,_,_,F1],
    Move2 = [_,_,_,_,F2],
    (F1 =< F2 -> Res = Move1 ; Res = Move2).

% iterateChildren(Kids, Board, Color, Acc, Move, A, B, Depth, Max)
iterateChildren(Kids, _, _, Acc, Acc, A, B,_,_):-
    (Kids = [] ; B =< A),!.
iterateChildren([H|T], Board, Color, Acc, Res, A, B, Depth, Max):-
    opposite(Max, NM),
    rivalColor(Color, RCol),
    NewD is Depth - 1,
    H = [Move, BD],
    % get result for current child
    getBestMove(BD, RCol, Temp1, A, B, NewD, NM),
    Temp1 = [_,_,_,_,F1],
    Move = [_,_,_,_,F1],
    % update alpha or beta
    changeCoef(Max, A, B, NA, NB, F1),
    % iterate the rest children
    chooseBest(Max, Move, Acc, Temp2),
    iterateChildren(T, Board, Color, Temp2, Res, NA, NB, Depth, Max).

%getMaximum(_, [], [_,_,_,_,-1000000]):-!.
%getMaximum(Color, [[H,B]|T], El):-
%    getMaximum(Color, T, X),
%    X = [_,_,_,_,F1],
%    func(B, Color, F2),
%    H = [_,_,_,_,F2],
%    write(H),nl,
%    (F1 > F2 ->
%       El = X
%       ; El = H).








