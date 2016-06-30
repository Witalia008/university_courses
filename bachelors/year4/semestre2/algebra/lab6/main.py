import random
import time


def timing(f):
    def wrap(*args):
        time1 = time.time()
        ret = f(*args)
        time2 = time.time()
        print('%s function took %.3f ms' %
              (f.__name__, (time2 - time1) * 100.0))
        return ret
    return wrap

inf = 1e1


def rand_r(l, r):
    return int(random.random() * (r - l) + l)


def gen_poly(n):
    return [rand_r(-inf, inf) for _ in range(0, n + 1)]


def slow_mul(a, b):
    res = [0] * (len(a) + len(b))
    for (i, ai) in enumerate(a):
        for (j, bj) in enumerate(b):
            res[i + j] += ai * bj
    return res


def summ(a, b, koef=1):
    res = []
    n, m = len(a), len(b)
    for i in range(0, max(n, m)):
        res.append((a[i] if i < n else 0) + koef * (b[i] if i < m else 0))
    return res


def add_shift(res, a, k):
    for (i, ai) in enumerate(a):
        while i + k >= len(res):
            res.append(0)
        res[i + k] += ai


def karatsuba(a, b):
    if a == [] or b == []:
        return []
    if len(a) <= 10 or len(b) <= 10:
        return slow_mul(a, b)

    n, m = len(a), len(b)
    l = max(n, m) // 2
    a1, a2 = a[:l], a[l:]
    b1, b2 = b[:l], b[l:]

    fst = karatsuba(a1, b1)
    trd = karatsuba(a2, b2)
    snd = karatsuba(summ(a1, a2), summ(b1, b2))
    snd = summ(snd, fst, -1)
    snd = summ(snd, trd, -1)

    res = []
    add_shift(res, fst, 0)
    add_shift(res, snd, l)
    add_shift(res, trd, l*2)
    return res


@timing
def test_karatsuba(p, q):
    return karatsuba(p, q)


@timing
def test_slow(p, q):
    return slow_mul(p, q)


n = 24
p = gen_poly(n)
q = gen_poly(n)
print(p)
print(q)
r = test_karatsuba(p, q)
print(r)
r = test_slow(p, q)
print(r)
