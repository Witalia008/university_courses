s(s(NP,VP)) --> np(NP, subject), vp(VP).

np(np(DET, N), _) --> det(DET), n(N).
np(np(PRO), X) --> pro(PRO, X).

vp(vp(V, NP)) --> v(V), np(NP, object).
vp(vp(V)) --> v(V).

n(n(Word)) --> [Word], {lex(Word, n)}.
det(det(Word)) --> [Word],{lex(Word, det)}.
v(v(Word)) --> [Word],{lex(Word, v)}.

pro(pro(Word), object) --> [Word], {lex(Word, proO)}.
pro(pro(Word), subject) --> [Word], {lex(Word, proS)}.

lex(man, n).
lex(woman, n).
lex(the, det).
lex(a, det).
lex(shoots, v).
lex(him, proO).
lex(her, proO).
lex(he, proS).
lex(she, proS).
