from math import pi
import matplotlib.pyplot as plt

x = pi / 4
X = [+0.00, 0.50, 1.00, 1.50, 2.00]
Y = [-1.00, 1.75, 4.00, 5.75, 7.00]
n = len(X)

P = [Y]
print(Y)
for k in range(1, n):
    m = n - k
    P.append([0] * m)
    for i in range(0, m):
        P[k][i] = (x - X[i + k]) * P[k - 1][i]
        P[k][i] += (X[i] - x) * P[k - 1][i + 1]
        P[k][i] /= X[i] - X[i + k]
    print(P[k])

print(P[n - 1][0])

plt.plot(X, Y)
plt.show()
