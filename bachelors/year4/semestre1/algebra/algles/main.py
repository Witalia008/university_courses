from sympy import *
from copy import deepcopy


def id_matr(n):
    res = []
    for i in range(n):
        res.append([0] * n)
    for i in range(n):
        res[i][i] = 1
    return res


def is_zero(A):
    return all(all(j == 0 for j in i) for i in A)


def is_zero_part(A, rbound, cbound):
    for i in range(rbound[0], rbound[1]):
        for j in range(cbound[0], cbound[1]):
            if A[i][j] != 0:
                return False
    return True


def is_zero_v(v):
    return all(i == 0 for i in v)


def swap_row(A, i, j):
    for k in range(len(A[0])):
        A[i][k], A[j][k] = A[j][k], A[i][k]


def add_row(A, i, j, c):
    for k in range(len(A[0])):
        A[i][k] += A[j][k] * c


def multiply_row(A, i, c):
    for k in range(len(A[0])):
        A[i][k] *= c


def swap_column(A, i, j):
    for k in range(len(A)):
        A[k][i], A[k][j] = A[k][j], A[k][i]


def add_column(A, i, j, c):
    for k in range(len(A)):
        A[k][i] += A[k][j] * c


def multiply_column(A, i, c):
    for k in range(len(A)):
        A[k][i] *= c


def Smiths_form(A):
    print("Smith")
    m, n = len(A), len(A[0])
    B = deepcopy(A)
    U = id_matr(m)
    V = id_matr(n)

    if is_zero(B):
        return B, U, V, 0

    s = 0
    while s < n or s < m:
        print("----------------")
        print("B")
        for xx in B:
            print(xx)
        print("U")
        for xx in U:
            print(xx)
        print("V")
        for xx in V:
            print(xx)
        pos = (s, s)
        num = abs(B[s][s])
        print("Move smallest element by "
              "absolute value B[%d..%d,%d..%d] to [%d,%d]" % (s, m,s,n,s,s))
        for i in range(s, m):
            for j in range(s, n):
                if B[i][j] != 0 and (num == 0 or abs(B[i][j]) < num):
                    pos = (i, j)
                    num = abs(B[i][j])

        print("pos = (%d,%d)" % (pos[0], pos[1]))
        if pos[0] != s:
            print("swap row %d and %d" % (s, pos[0]))
            swap_row(B, s, pos[0])
            swap_row(U, s, pos[0])
            print("B")
            for xx in B:
                print(xx)
            print("U")
            for xx in U:
                print(xx)
        if pos[1] != s:
            print("swap column %d and %d" % (s, pos[1]))
            swap_column(B, s, pos[1])
            swap_column(V, s, pos[1])
            print("B")
            for xx in B:
                print(xx)
            print("V")
            for xx in V:
                print(xx)
        if B[s][s] < 0:
            print("multiply row %d by %d" % (s, -1))
            multiply_row(B, s, -1)
            multiply_row(U, s, -1)
            print("B")
            for xx in B:
                print(xx)
            print("U")
            for xx in U:
                print(xx)

        # LB_modedg
        modedg_proceed = True
        print("Приведення по модулю ключового елемента (%d,%d)"
              " edging вниз і вправа від ключового елемента" % (s, s))
        while modedg_proceed:
            for i in range(s + 1, m):
                if B[i][s] != 0:
                    q = B[i][s] // B[s][s]
                    print("Add row %d and %d * %d" % (i, s, -q))
                    add_row(B, i, s, -q)
                    add_row(U, i, s, -q)
                    print("B")
                    for xx in B:
                        print(xx)
                    print("U")
                    for xx in U:
                        print(xx)

            for j in range(s + 1, n):
                if B[s][j] != 0:
                    q = B[s][j] // B[s][s]
                    print("Add column %d and %d * %d" % (j, s, -q))
                    add_column(B, j, s, -q)
                    add_column(V, j, s, -q)
                    print("B")
                    for xx in B:
                        print(xx)
                    print("V")
                    for xx in V:
                        print(xx)

            # LB_nulledg
            print("Zerify edging")
            while True:
                pos = (s, s)
                num = abs(B[s][s])
                goto_modedg = False
                print("Move zero element of edging into (%d, %d)" % (s, s))
                if not (is_zero_part(B, [s + 1, m], [s, s + 1]) and
                               is_zero_part(B, [s, s + 1], [s + 1, n])):

                    for i in range(s + 1, m):
                        if B[i][s] != 0 and abs(B[i][s]) < num:
                            pos = (i, s)
                            num = abs(B[i][s])

                    for j in range(s + 1, n):
                        if B[s][j] != 0 and abs(B[s][j]) < num:
                            pos = (s, j)
                            num = B[s][j]

                    if pos[1] == s and pos[0] > s:
                        print("Swap row %d and %d" % (s, pos[0]))
                        swap_row(B, s, pos[0])
                        swap_row(U, s, pos[0])
                        print("B")
                        for xx in B:
                            print(xx)
                        print("U")
                        for xx in U:
                            print(xx)
                    elif pos[0] == s and pos[1] > s:
                        print("Swap column %d and %d" % (s, pos[1]))
                        swap_column(B, s, pos[1])
                        swap_column(V, s, pos[1])
                        print("B")
                        for xx in B:
                            print(xx)
                        print("V")
                        for xx in V:
                            print(xx)

                    # goto LB_modedg
                    goto_modedg = True

                if goto_modedg:
                    break

                if B[s][s] < 0:
                    print("Multiply row %d by %d" % (s, -1))
                    multiply_row(B, s, -1)
                    multiply_row(U, s, -1)

                print("Check south-east block - everyone "
                      "should divide by the key one")
                pos = [s, s]
                num = B[s][s]
                for i in range(s + 1, m):
                    for j in range(s + 1, n):
                        if B[i][j] % B[s][s] != 0 and \
                                                B[i][j] % B[s][s] < num:
                            pos = [i, j]
                            num = B[i][j] % B[s][s]

                if pos[0] != s or pos[1] != s:
                    print("Do not divide. Spoil edging")
                    print("Add row %d and %d * %d" %(s, pos[0], 1))
                    add_row(B, s, pos[0], 1)
                    add_row(U, s, pos[0], 1)
                    print("B")
                    for xx in B:
                        print(xx)
                    print("U")
                    for xx in U:
                        print(xx)

                    q = B[s][pos[1]] // B[s][s]
                    print("Add column %d and %d * %d" % (pos[1], s, -q))
                    add_column(B, pos[1], s, -q)
                    add_column(V, pos[1], s, -q)
                    print("B")
                    for xx in B:
                        print(xx)
                    print("V")
                    for xx in V:
                        print(xx)
                    print("Swap column %d and %d" % (pos[1], s))
                    swap_column(B, pos[1], s)
                    swap_column(V, pos[1], s)
                    print("B")
                    for xx in B:
                        print(xx)
                    print("V")
                    for xx in V:
                        print(xx)

                    # goto LB_nulledg
                else:
                    modedg_proceed = False
                    break

        if is_zero_part(B, [s + 1, m], [s + 1, n]):
            return B, U, V, s + 1

        s += 1
    # end Smiths_form

# A = [
#     [50, -88, 50, -62],
#     [-156, 264, -150, 186],
#     [18, -42, 24, -30]
# ]
# B, U, V, r = Smiths_form(A)
#
# print(B)
# print(U)
# print(V)
# print(r)


def mul_Mv(A, b):
    res = []
    for i in A:
        cur = 0
        for x, y in zip(i, b):
            cur += x * y
        res.append(cur)
    return res


def vector(n, symbol='x'):
    return [Symbol('%s%d' % (symbol, i)) for i in range(n)]


def iLinSolve(A, b):
    m, n = len(A), len(A[0])

    if m != len(b):
        raise Exception("")

    S, U, V, r = Smiths_form(A)

    print("S")
    for xx in S:
        print(xx)
    print("U")
    for xx in U:
        print(xx)
    print("V")
    for xx in V:
        print(xx)
    print(r)
    print("LinSolve")

    if r == 0 and not is_zero_v(b):
        return None
    if r == 0 and is_zero(b):
        return vector(n)

    c = mul_Mv(U, b)
    print("C = ", c)
    y = vector(n, symbol='y')
    print("y = ", y)

    if not is_zero_v(c[r + 1:m]):
        return None

    for i in range(r):
        if c[i] % S[i][i] != 0:
            return None
        y[i] = c[i] // S[i][i]
        print("y = ", y)

    return mul_Mv(V, y)


# A = [
#     [0, -14, -2, 16],
#     [4, -34, -4, 40],
#     [4, 2, 0, 0]
# ]
# b = [8, 8, 64]
#
# print(iLinSolve(A, b))

# A = [
#     [-18, 32, 40, 10, 50],
#     [-6, 20, 10, 10, 20],
#     [-4, 10, 8, 4, 12],
#     [-28, 62, 58, 24, 62]
# ]
# b = [64, 34, 18, 116]
#
# print(iLinSolve(A, b))

# A = [
#     [3, 1, -1, -1, 0],
#     [9, 1, -2, -1, -2],
#     [1, -1, 0, -1, 2],
#     [1, 1, -1, -3, 4]
# ]
# b = [2, 5, 1, 2]
# y = iLinSolve(A, b)
# print(y)
# print(mul_Mv(A, y))

# A = [
#     [2, 1, -1, -1, 1],
#     [1, -1, 1, 1, -2],
#     [3, 3, -3, -3, 4],
#     [4, 5, -5, -5, 7]
# ]
# b = [1, 0, 2, 3]
# y = iLinSolve(A, b)
# print(y)
# print(mul_Mv(A, y))

A = [
    [0, -14, -2, 16],
    [4, -34, -4, 40],
    [4, 2, 0, 0],
]
b = [8, 8, 64]
y = iLinSolve(A, b)
print(y)
print(mul_Mv(A, y))