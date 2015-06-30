def gcd_ex(a, b):
    if b == 0:
        return [a, 1, 0]
    g, x, y = gcd_ex(b, a % b)
    return [g, y, x - (a // b) * y]
