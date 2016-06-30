

def Pid(n):
    return range(n)


def Pdeg(alpha):
    return len(alpha)


def Pequal(alpha, beta):
    for (a, b) in zip(alpha, beta):
        if a != b:
            return False
    return True


def Pmul(alpha, beta):
    n = Pdeg(alpha)
    res = []
    for i in range(n):
        res.append(alpha[beta[i]])
    return res


def Ppow(alpha, k):
    n = Pdeg(alpha)
    k = (k % n + n) % n
    res = Pid(n)
    for i in range(k):
        res = Pmul(res, alpha)
    return res


def Pord(alpha):
    n = Pdeg(alpha)
    nid = Pid(n)
    k = 1
    beta = alpha
    while not Pequal(beta, nid):
        k += 1
        beta = Pmul(beta, alpha)
    return k

alpha = [2, 7, 4, 3, 1, 0, 5, 6]
beta = [6, 1, 3, 4, 7, 0, 5, 2]
xi = [5, 0, 4, 3, 2, 6, 1, 7]
eta = [3, 2, 7, 4, 1, 6, 0, 5]
phi = [1, 6, 4, 3, 2, 0, 5, 7]

lst = map(Pord, [alpha, beta, xi, eta, phi])
print(list(lst))
