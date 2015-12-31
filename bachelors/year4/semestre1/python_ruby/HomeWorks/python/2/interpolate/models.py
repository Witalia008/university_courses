import bisect
from collections import defaultdict

# Create your models here.
import math


class Interpolation:
    class Dot:
        def __init__(self, x, y):
            self.x, self.y = [x, y]

        def __str__(self):
            return "Dot(%f, %f)" % (self.x, self.y)

    class Tuple:
        def __init__(self):
            self.a, self.b, self.c, self.d, self.x = 0., 0., 0., 0., 0.

        def __str__(self):
            return "S(x) = %0.3f + %0.3f*x + %0.3f*x^2/2 + %0.3f*x^3/6 (x = %0.3f)" \
                   % (self.a, self.b, self.c, self.d, self.x)

    in_func = lambda x: math.sin(x)
    in_min_x = 0
    in_max_x = 25
    in_step = 2.5

    out_min_x = 0
    out_max_x = 25
    out_step = 0.1

    splines = defaultdict(lambda: Interpolation.Tuple())

    @classmethod
    def interpolate(cls, dots):
        n = len(dots)

        for i in range(n):
            cls.splines[i].x, cls.splines[i].a = dots[i].x, dots[i].y

        alpha, beta = [defaultdict(lambda: 0.), defaultdict(lambda: 0.)]

        for i in range(1, n-1):
            C = 4. * cls.in_step
            F = 6. * ((dots[i + 1].y - dots[i].y) / cls.in_step - (dots[i].y - dots[i - 1].y) / cls.in_step)
            z = (cls.in_step * alpha[i - 1] + C)
            alpha[i] = -cls.in_step / z
            beta[i] = (F - cls.in_step * beta[i - 1]) / z

        for i in reversed(range(1, n-1)):
            cls.splines[i].c = alpha[i] * cls.splines[i + 1].c + beta[i]

        for i in reversed(range(1, n)):
            hi = dots[i].x - dots[i - 1].x
            cls.splines[i].d = (cls.splines[i].c - cls.splines[i-1].c) / hi
            cls.splines[i].b = hi * (2.0 * cls.splines[i].c + cls.splines[i-1].c) / 6.0 + (dots[i].y - dots[i-1].y) / hi

    @classmethod
    def calc(cls, x):
        distribution = sorted([t[1].x for t in cls.splines.items()])
        indx = bisect.bisect_left(distribution, x)
        if indx == len(distribution):
            return 0
        dx = x - cls.splines[indx].x
        return cls.splines[indx].a + \
               cls.splines[indx].b * dx + \
               cls.splines[indx].c * dx**2 / 2.0 + \
               cls.splines[indx].d * dx**3 / 6.0
