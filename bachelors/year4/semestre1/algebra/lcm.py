from numpy.core._internal import _gcd


def lcm(a, b):
    return a * b // _gcd(a, b)


def lcm_arr(arr):
    res = arr[0]
    for i in arr:
        res = lcm(res, i)
    return res

print(lcm_arr([5, 7, 3, 2, 4]))


from sympy import *


def lcm_poly(a, b):
    return simplify(expand(a * b / gcd(a, b)))

x = Symbol('x')
y = Symbol('y')
z = Symbol('z')
[f1, f2] = [x*y + z - 1, x - y - z**2]

print(simplify(expand(lcm_poly(f1, f2) / f1)))
