from math import sqrt, floor
import numpy as np


def div_set(a):
    res = []
    for i in range(1, floor(sqrt(abs(a)))):
        if int(a) % i == 0:
            res.append(i)
            res.append(a // i)
    return sorted(res)


def cart(A, B):
    return [i + j for i in A for j in B]


def zerop(poly):
    for i in range(0, len(poly)):
        if abs(poly[i]) > 1e-6:
            return False
    return True


def kroneker(f):
    n = len(f) - 1
    for i in range(0, n // 2 + 1):
        if np.polyval(f, [i])[0] == 0:
            return np.array([1, -i])

    U = [[i] for i in div_set(np.polyval(f, 0))]
    for i in range(1, n // 2 + 1):
        M = [[i] for i in div_set(np.polyval(f, [i])[0])]
        U = cart(U, M)
        for ys in U:
            g = np.polyfit(range(0, i + 1), ys, i)
            while len(g) > 1 and abs(g[0]) < 1e-6:
                g = g[1:]
            x = np.polydiv(f, g)
            if len(g) > 1 and zerop(x[1]):
                return g
    return f


def factorize(f):
    res = []
    while len(f) > 1 or f[0] != 1:
        g = kroneker(f)
        res.append(g)
        x = np.polydiv(f, g)
        f = np.polydiv(f, g)[0]
    return res


import sys


def fancy_print_p(p):
    sys.stdout.write('(')
    for i in range(0, len(p)):
        if i and p[i] > 0:
            sys.stdout.write('+')
        j = len(p)-i-1
        if abs(p[i] - 1) > 1e-6 or j == 0:
            sys.stdout.write(str(p[i]))
        if j > 0:
            sys.stdout.write('x')
            if j > 1:
                sys.stdout.write('^' + str(len(p)-i-1))
    sys.stdout.write(')')


def fancy_print(pla):
    for i in range(0, len(pla)):
        if i: sys.stdout.write(' * ')
        fancy_print_p(pla[i])
    print()

f8 = np.array([16, 76, 68, -76, -84])
f28 = np.array([1, 2, -72, -416, -640])

fancy_print(factorize(f8))
fancy_print(factorize(f28))


print()

from sympy import *

x = Symbol('x')

f = 16*x**4+76*x**3+68*x**2-76*x-84
print(factor(f))
f = x**4+2*x**3-72*x**2-416*x-640
print(factor(f))
