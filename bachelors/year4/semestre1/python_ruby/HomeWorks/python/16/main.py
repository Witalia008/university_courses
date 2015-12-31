from scipy.optimize import linprog
import numpy as np
from mayavi import mlab


# Solve
c = [-1, 4]
A = [[-3, 1], [1, 2]]
b = [6, 4]
x0_bounds = (None, None)
x1_bounds = (-3, None)
res = linprog(c, A_ub=A, b_ub=b, bounds=(x0_bounds, x1_bounds),
              options={"disp": True})
print(res)
x = res.x.tolist()
print(x)


X, Y = np.mgrid[
          0:15:64j,
          -3:-2:64j,
          ]


def func(x, y):
    return c[0]*x + c[1]*y

mlab.surf(X, Y, func)

mlab.points3d(x[0], x[1], func(x[0], x[1]), color=(1, 0, 0))

mlab.show()