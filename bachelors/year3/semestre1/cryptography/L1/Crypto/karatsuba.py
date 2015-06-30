def split_at(num, m):
    str_m = str(num)[::-1]
    endd, begg = (str_m[:m])[::-1], (str_m[m:])[::-1]
    if begg == "": begg = "0"
    if endd == "": endd = "0"
    return (int(begg), int(endd))
    
def strl(a, m):
    while len(a) < m:
        a = "0" + a
    return a
    
def mul_tpow(a, m):
    res = str(a)
    for i in range(m):
        res += "0"
    return int(res)

def karatsuba(num1, num2):
    if (num1 < 10) or (num2 < 10):
        return num1 * num2
    m = max(len(str(num1)), len(str(num2))) // 2
    high1, low1 = split_at(num1, m)
    high2, low2 = split_at(num2, m)
    z0 = karatsuba(low1, low2)
    z1 = karatsuba((low1 + high1), (low2 + high2))
    z2 = karatsuba(high1, high2)
    return mul_tpow(z2, m * 2) + mul_tpow((z1 - z2 - z0), m) + z0

a = int(raw_input())
b = int(raw_input())
print a * b
print karatsuba(a, b)
