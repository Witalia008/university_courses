import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from numpy import *


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

f = open("output.txt", "r")
n = int(f.readline())
X, Y, Z = [], [], []
for i in range(n):
    x, y, z = map(int, f.readline().split())
    X.append(x)
    Y.append(y)
    Z.append(z)

ax.plot(X, Y, Z)
plt.show()
Axes3D.plot()