s(s(NP,VP)) --> np(NP, subject), vp(VP).

np(np(DET, NAP), _) --> det(DET), nap(NAP).
np(np(PRO), X) --> pro(PRO, X).

nap(nap(N)) --> npp(N).
nap(nap(ADJ, NAP)) --> adj(ADJ), nap(NAP).

npp(npp(N)) --> n(N).
npp(npp(N, PP)) --> n(N), pp(PP).

pp(pp(PREP, NP)) --> prep(PREP), np(NP, object).

vp(vp(V, NP)) --> v(V), np(NP, object).
vp(vp(V)) --> v(V).

adj(adj(Word)) --> [Word], {lex(Word, adj)}.
n(n(Word)) --> [Word], {lex(Word, n)}.
det(det(Word)) --> [Word],{lex(Word, det)}.
v(v(Word)) --> [Word],{lex(Word, v)}.

prep(prep(Word)) --> [Word], {lex(Word, prep)}.
pro(pro(Word), object) --> [Word], {lex(Word, proO)}.
pro(pro(Word), subject) --> [Word], {lex(Word, proS)}.

lex(man, n).
lex(woman, n).
lex(showe, n).
lex(table, n).

lex(the, det).
lex(a, det).

lex(shoots, v).

lex(him, proO).
lex(her, proO).
lex(he, proS).
lex(she, proS).

lex(small, adj).
lex(frightened, adj).
lex(big, adj).
lex(fat, adj).

lex(on, prep).
lex(under, prep).


