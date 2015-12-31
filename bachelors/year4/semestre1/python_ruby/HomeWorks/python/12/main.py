from chaco.shell import *


def sierpinski(depth=0):
    if depth == 0:
        return [-1., 0., 1., -1.], [-1., 1., -1., -1.]
    px, py = sierpinski(depth-1)
    pts = zip(px, py)
    resx = []
    resy = []
    for (x, y) in pts:
        resy.append((y+1)/2-1)
        resx.append((x+1)/2-1)
    for (x, y) in pts:
        resy.append((y+1)/2)
        resx.append((x+1)/2-0.5)
    for (x, y) in pts:
        resy.append((y+1)/2-1)
        resx.append((x+1)/2)
    resx.append(-1.)
    resy.append(-1.)
    return resx, resy


x, y = sierpinski(6)

plot(x, y, "r-")
title("Sierpinski triangle")
show()
