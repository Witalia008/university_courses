# http://people.cs.clemson.edu/~goddard/texts/cpsc8400/part1.pdf
import operator
import pp

class Point:
    def __init__(self, x, y):
        self.x, self.y = x, y

    def __repr__(self):
        return '(%d, %s)' % (self.x, self.y)


def get_side_point(pts, func=operator.gt):
    idx = 0
    for i in range(1, len(pts)):
        if func(pts[i].x, pts[idx].x):
            idx = i
    return idx


def cw(a, b, c):
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0


def ccw(a, b, c):
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0


def unite(left, right):
    ln, rn = len(left), len(right)
    a = get_side_point(left, func=operator.gt)
    b = get_side_point(right, func=operator.lt)
    lup, ldown = a, a
    rup, rdown = b, b

    # find upper tangent
    while True:
        if ccw(left[lup-1], left[lup], right[rup]):
            lup = (lup-1+ln) % ln
        elif cw(right[(rup+1) % rn], right[rup], left[lup]):
            rup = (rup + 1) % rn
        else:
            break

    # find lower tangent
    while True:
        if cw(left[(ldown+1) % ln], left[ldown], right[rdown]):
            ldown = (ldown + 1) % ln
        elif ccw(right[rdown-1], right[rdown], left[ldown]):
            rdown = (rdown-1+rn) % rn
        else:
            break

    res = []
    while True:
        res.append(left[ldown % ln])
        if lup == ldown:
            break
        ldown = (ldown+1) % ln
    while True:
        res.append(right[rup % rn])
        if rup == rdown:
            break
        rup = (rup+1) % rn
    return res


def convex_hull(pts):
    n = len(pts)
    if n < 2:
        return pts
    left = convex_hull(pts[:n//2])
    right = convex_hull(pts[n//2:])
    return unite(left, right)


def convex_hull_parallel(pts, threadn=4):
    len_segm = (len(pts)+threadn-1) / threadn
    threads = []
    parts = []
    job_server = pp.Server()
    for i in range(0, threadn):
        _from = i * len_segm
        _to = min(len(pts), (i+1)*len_segm)
        threads.append(
            job_server.submit(convex_hull,
                              (pts[_from:_to],),
                              (unite, cw, ccw, get_side_point, Point),
                              modules=('operator',)))
    for thread in threads:
        parts.append(thread())
    while len(parts) > 1:
        _parts = []
        for i in range(0, len(parts), 2):
            if i+1 == len(parts):
                _parts.append(parts[i])
            else:
                _parts.append(unite(parts[i], parts[i+1]))
        parts = _parts
    return parts[0]


import turtle


def draw_hull(pts, hull):
    turtle.color('black')
    turtle.begin_fill()
    for pt in pts:
        turtle.penup()
        turtle.goto(pt.x, pt.y)
        turtle.pendown()
        turtle.forward(1)
    turtle.penup()
    turtle.goto(hull[-1].x, hull[-1].y)
    turtle.pendown()
    for pt in hull:
        turtle.goto(pt.x, pt.y)
    turtle.done()


if __name__ == '__main__':
    pts = [(30, 60), (50, 40), (0, 30), (15, 25), (70, 30), (55, 20), (50, 10), (20, 0)]
    pts = [Point(pt[0], pt[1]) for pt in pts]
    pts = sorted(pts, key=lambda a: a.x)
    print(pts)
    hull = convex_hull_parallel(pts)
    print(hull)
    draw_hull(pts, hull)
