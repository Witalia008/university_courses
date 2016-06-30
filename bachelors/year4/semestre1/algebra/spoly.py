from copy import deepcopy

from sympy import *


def s_polynomial(f, g):
    return expand(lcm(LM(f), LM(g))*(1/LT(f)*f - 1/LT(g)*g))

x = Symbol('x')
y = Symbol('y')
z = Symbol('z')

F = [f1, f2, f3] = [x*y + z - 1, x - y - z**2, x**2 - 2*y + 1]

print("System F=", F)

s = s_polynomial(f1, f2)
print("s_polynomial=", s)

print("Generalized division of s-polynomial by systems of polynomials F is")

pprint(reduced(s, F)[1])

print()

print("Buchberger algorithm:")

print()

print("Input system", F)


def buchberger(F, isreduced=True):
    """Реалізація алгоритму Бухбергера. """
    G, pairs = list(F), set([])

    for i, f1 in enumerate(F):
        for f2 in F[i+1:]:
            pairs.add((f1, f2))

    while pairs:
        f1, f2 = pairs.pop()
        print("For polynomials")
        print("f1=",f1)
        print("f2=",f2)

        s = s_polynomial(f1, f2)
        print("s-polynomial is: ", s)
        h = reduced(s, G)[1]
        print("Generalized division s-polynomial by systems of polynomials G is", h)

        if h != 0:
            for g in G:
                pairs.add((g, h))

            G.append(h)
        print("New system is: ", G)
        print()

    if isreduced:
        N = []

        for i, g in enumerate(G):
            print("i=", i)
            print("g=", g)
            red = reduced(g, G[:i] + G[i+1:]) [1]

            if red != 0:
                N.append(red)

        G = deepcopy(N)
        G = list(map(monic, G))

    return G

# Number 6:
F = [x*y + z - 1, x - y - z**2, x**2 - 2*y + 1]
# Number 7:
# F = [x*z - y - x + x*y, y*z - z + x**2 + y*x**2, x - x**2 + y]
G = buchberger(F, True)
print("Groebner basis is:", G)
