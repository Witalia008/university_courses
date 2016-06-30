def legandre(a, m):
    a %= m
    t = 1
    while a != 0:
        while a % 2 == 0:
            a /= 2
            if (m % 8) in [3, 5]:
                t = -t
        a, m = m, a
        if a % 4 == m % 4 == 3:
            t = -t
        a %= m
    if m == 1:
        return t
    return 0

print(legandre(2562357894096485, 1000003))
print(legandre(80, 2))
