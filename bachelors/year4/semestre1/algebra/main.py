# http://alex-black.ru/article.php?content=117
# array (coef, pow_x, pow_y, pow_z)

import copy


def compare(mon_a, mon_b):
    for i in range(len(mon_a) - 1):
        if mon_a[i] != mon_b[i]:
            return 1 if mon_a[i] > mon_b[i] else -1
    return 0


def sort(poly):
    poly = sorted(poly, reverse=True)
    return poly


def add_monom(poly, mon):
    poly = copy.deepcopy(poly)
    for i, el in enumerate(poly):
        if el[0:-1] == mon[0:-1]:
            el[-1] += mon[-1]
            if el[-1] == 0 and len(poly) > 1:
                del poly[i]
            return poly
    poly.append(mon)
    return sort(poly)


def mul_monom(poly, mon):
    poly = copy.deepcopy(poly)
    for el in poly:
        el[-1] *= mon[-1]
        for i in range(0, len(mon) - 1):
            el[i] += mon[i]
    return sort(poly)


def subtract(poly_a, poly_b):
    poly_a = copy.deepcopy(poly_a)
    poly_b = copy.deepcopy(poly_b)
    for el in poly_b:
        el[-1] *= -1
    ai = 0
    bi = 0
    res = []
    while ai < len(poly_a) or bi < len(poly_b):
        if ai == len(poly_a):
            res.append(poly_b[bi])
            bi += 1
        elif bi == len(poly_b):
            res.append(poly_a[ai])
            ai += 1
        else:
            cmp = compare(poly_a[ai], poly_b[bi])
            if cmp == 1:
                res.append(poly_a[ai])
                ai += 1
            elif cmp == -1:
                res.append(poly_b[bi])
                bi += 1
            else:
                res_ = poly_a[ai]
                res_[-1] += poly_b[bi][-1]
                if res_[-1] != 0:
                    res.append(res_)
                ai += 1
                bi += 1
    return res


def s_poly(poly_a, poly_b):
    poly_a = copy.deepcopy(poly_a)
    poly_b = copy.deepcopy(poly_b)
    a = poly_a[0]
    b = poly_b[0]

    mul_a = [y-x if y > x else 0 for (x, y) in zip(a, b)]
    mul_a[-1] = b[-1]
    mul_b = [x - y if x > y + 1e-5 else 0 for (x, y) in zip(a, b)]
    mul_b[-1] = a[-1]

    poly_a = mul_monom(poly_a, mul_a)
    poly_b = mul_monom(poly_b, mul_b)

    return subtract(poly_a, poly_b)


def divide(mon_a, mon_b):
    res = list(mon_a)
    for i in range(len(mon_a)-1):
        if mon_a[i] < mon_b[i]:
            return None
        res[i] -= mon_b[i]
    res[-1] /= mon_b[-1]
    return res


def is_zero(poly):
    for el in poly:
        if abs(el[-1]) > 1e-5:
            return False
    return True


def reduce(basis, poly):
    res = []

    while not is_zero(poly):
        divided = False
        i = 0
        while i < len(basis) and not divided:
            f = copy.deepcopy(basis[i])
            m = poly[0]
            d = divide(m, f[0])
            if d is None:
                i += 1
                continue
            f = mul_monom(f, d)
            poly = subtract(poly, f)
            divided = True

        if not divided:
            res.append(poly[0])
            poly = poly[1:]

    return res


letters = ['x', 'y', 'z']


def print_poly(poly):
    print("# ", end='')
    for el in poly:
        if el[-1] > 0: print('+', end='')
        print('%.2f' % el[-1], end='')
        for i in range(0, len(el)-1):
            if el[i] > 0:
                print(letters[i], end='')
                if el[i] > 1:
                    print('^%.0f' % el[i], end='')
    print('')


def print_poly_s(poly_s):
    for poly in poly_s:
        print_poly(poly)


maxLen = 20


def buchberger(poly_s, is_reduced=True):
    k = 1
    print("Basis:")
    print_poly_s(poly_s)
    while k < len(poly_s) < maxLen:
        f1 = poly_s[k]
        i = 0
        while i < len(poly_s):
            if i != k:
                f2 = poly_s[i]
                s_p = s_poly(f1, f2)
                print("\n--------------------Step")
                print("S-polynome:")
                print_poly(s_p)
                s = reduce(poly_s, s_p)
                if not is_zero(s):
                    poly_s.append(s)
                    if len(poly_s) >= maxLen:
                        print("Basis:")
                        print_poly_s(poly_s)
                        break
                print("Basis:")
                print_poly_s(poly_s)
                print()
            i += 1
        k += 1
    print('')

    if is_reduced:
        N = []
        for i, g in enumerate(poly_s):
            red = reduce(poly_s[:i] + poly_s[i+1:], g)
            if not is_zero(red):
                N.append(red)
        poly_s = copy.deepcopy(N)

    return poly_s


# print(poly_s)
# print(add_monom(poly_s[1], [0, 1, 2, 3]))
# print(mul_monom(poly_s[1], [0, 2, 3, 5]))

# print(subtract(poly_s[0], poly_s[1]))
# print(s_poly(poly_s[0], poly_s[1]))
# print(divide(poly_s[0][0], poly_s[1][0]))

# print(reduce([
#     [[0, 2, 1], [0, 0, -1]],
#     [[1, 1, 1], [0, 0, -1]]
# ], [[2, 1, 1], [1, 2, 1], [0, 2, 1]]))

# print_poly_s(buchberger([
#     [[2, 0, -6], [1, 0, 6], [0, 2, -6], [0, 1, 6], [0, 0, -2]],
#     [[3, 0, 4], [2, 0, -6], [0, 3, -4], [0, 2, 6]]
# ]))


# Number 6:
poly_s = [
    sort([[1, 1, 0, 1], [0, 0, 1, 1], [0, 0, 0, -1]]),  # xy + z - 1
    sort([[1, 0, 0, 1], [0, 1, 0, -1], [0, 0, 2, -1]]),  # x - y - z^2
    sort([[2, 0, 0, 1], [0, 1, 0, -2], [0, 0, 0, 1]]),  # x^2 - 2y + 1
]
print_poly_s(buchberger(poly_s, True))


# Number 2:
# print_poly_s(buchberger([
#     [[1, 0, 1, 1], [0, 1, 0, -2], [0, 0, 0, 1]],
#     [[0, 1, 1, 1], [0, 0, 0, -1], [0, 0, 1, 1]],
#     [[0, 1, 1, 1], [1, 1, 1, 1], [0, 0, 1, 1]]
# ], True))


# Number 7:
# print_poly_s(buchberger([
#     [[1, 0, 1, 1], [0, 1, 0, -1], [1, 0, 0, -1], [1, 1, 0, 1]],
#     [[0, 1, 1, 1], [0, 0, 1, -1], [2, 0, 0, 1], [2, 1, 0, 1]],
#     [[1, 0, 0, 1], [2, 0, 0, -1], [0, 1, 0, 1]]
# ], True))
