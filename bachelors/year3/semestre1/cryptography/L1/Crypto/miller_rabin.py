import random

def separate(n):
    s = 0
    while n % 2 == 0:
        s += 1
        n = n // 2
    return [s, n]

def miller(n, k):
    s, d = separate(n - 1)
    for i in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, d, n)
        if (x == 1) or (x == n - 1):
            continue
        good = False
        for j in range(s - 1):
            x = pow(x, 2, n)
            if x == 1:
                return False
            if x == n - 1:
                good = True
                break
        if good == False:
            return False
    return True

n = int(raw_input())
k = int(raw_input())
print miller(n, k)