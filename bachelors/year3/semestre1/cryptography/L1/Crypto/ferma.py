import random

def ferma(n, k):
    for i in range(k):
        a = random.randint(1, n - 1)
        if pow(a, n - 1, n) != 1:
            return False
    return True

n = int(raw_input())
k = int(raw_input())
print ferma(n, k)
        