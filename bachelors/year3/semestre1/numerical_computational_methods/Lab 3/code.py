'''import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from math import *
from numpy import *

step = 0.01
Z = arange(-2, 2, step)
X, Y = [], []
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')


def F0(x, y, z):
    return (x**2) / 4 + (y**2) + (z**2) / 9 - 1
def F1(x, y, z):
    return (x**2) + (y**2) / 9 + (z**2) / 4 - 1
for p in [0, 1, 2, 3]:
    c1 = 1 if p % 2 == 0 else -1
    c2 = 1 if (p / 2) % 2 == 0 else -1
    X, Y = [], []
    for zi in Z:
        xi, yi = c1 * sqrt(288 - 77 * (zi**2)) / (3 * sqrt(35)), c2 * sqrt(108 - 7 * (zi**2)) / (2 * sqrt(35))
        X.append(xi)
        Y.append(yi)
        print xi, yi, zi, F0(xi, yi, zi), F1(xi, yi, zi)
    ax.plot(X, Y, Z)    


plt.show()
Axes3D.plot()'''
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from math import *
from numpy import *

def sqr(a):
    return a * a

def F0(x, y, z):
    return (x**2) / 4 + (y**2) + (z**2) / 9 - 1
def F1(x, y, z):
    return (x**2) + (y**2) / 9 + (z**2) / 4 - 1

def norm(x, y):
    return abs(x) + abs(y)

def f0(x, y, z):
    return (x**2) / 4 + (y**2) - (1 - z * z / 9) * (norm(x, y) ** 2)
def f1(x, y, z):
    return (x**2) + (y**2) / 9 - (1 - z * z / 4) * (norm(x, y) ** 2)

T = 0.2

def phi0(x, y, z):
    #return x - T * f0(x, y, z)
    return 2 * sqrt(fabs(1 - sqr(z) / 9 - sqr(y)))
def phi1(x, y, z):
    #return y - T * f1(x, y, z)
    return 3 * sqrt(fabs(1 - sqr(z) / 4 - sqr(x)))

eps = 0.001

def approx(x0, y0, z0):
    while True:
        x = phi0(x0, y0, z0)
        y = phi1(x0, y0, z0)
        if (norm(x - x0, y - y0) < eps):
            return [x, y]
        x0, y0 = x, y

step = 0.1
Z = arange(0, 1 + step, step)
X, Y = [], []
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

c = 0.3
def X0(z):
    return sqrt((1 - sqr(z) / 4) / (1 + 9 / sqr(c)))
def Y0(z):
    return sqrt((1 - sqr(z) / 9) / (1 + 4 / sqr(c)))

for zi in Z:
    xi, yi = approx(X0(zi), Y0(zi), zi)
    X.append(xi)
    Y.append(yi)
    print xi, yi, zi, F0(xi, yi, zi), F1(xi, yi, zi)

ax.plot(X, Y, Z)
plt.show()
Axes3D.plot()