def poww(a, b, c):
    res = 1
    while b:
        if b and 1 == 1:
            res = (res * a) % c
        b = b >> 1
        a = (a * a) % c
    return res

a = int(raw_input())
b = int(raw_input())
c = int(raw_input())
print poww(a, b, c)