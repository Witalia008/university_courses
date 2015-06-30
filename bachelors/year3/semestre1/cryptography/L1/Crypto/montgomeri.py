from gcd_ex import gcd_ex
import sys

b = 2 ** 32

def getR(N):
    res = b
    while res <= N:
        res *= b
    return res

def getRev(N, R):
    g, x, y = gcd_ex(N, R)
    if g != 1:
        print "R & N are not co-prime"
        return -1
    else:
        return (x % R + R) % R

N = int(raw_input("Enter N:"))
if N % 2 == 0:
    sys.exit(0)
    
R = getR(N)
print "R:", R
Q = getRev(R, N)

class Mnum:
    def __init__(self, x):
        self.num = (x * R) % N
    
    def __add__(self, b):
        res = Mnum(0)
        res.num = (self.num + b.num) % N
        return res
    
    def __mul__(self, b):
        res = Mnum(0)
        y = (self.num * b.num) % N
        res.num = (y * Q) % N
        return res

a = Mnum(int(raw_input("Enter A:")))
b = Mnum(int(raw_input("Enter B:")))
print "A & B MG:", a.num, b.num
print "A + B:", (a + b).num
print "A * B:", (a * b).num