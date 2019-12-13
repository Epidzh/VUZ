
import matplotlib.pyplot as plt
from numpy import arange

class SplineTuple:
    def __init__(self, a, b, c, d, x):
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.x = x


def BuildSpline(x, y, n):
    splines = [SplineTuple(0, 0, 0, 0, 0) for _ in range(0, n)]
    for i in range(0, n):
        splines[i].x = x[i]
        splines[i].a = y[i]

    alpha = [0.0 for _ in range(0, n - 1)]
    beta  = [0.0 for _ in range(0, n - 1)]

    for i in range(1, n - 1):
        hi = x[i] - x[i - 1]
        hi_plus_1 = x[i + 1] - x[i]
        li = y[i] - y[i - 1]
        li_plus_1 = y[i + 1] - y[i]
        if i == 1:
            alpha[i] = -hi_plus_1 / (2 * (hi + hi_plus_1))
            beta[i] = 3 * (li_plus_1 - li) / (2 * (hi + hi_plus_1))
        else:
            alpha[i] = -hi_plus_1 / (2 * hi + 2 * hi_plus_1 + hi * alpha[i - 1])
            beta[i] = (3 * li_plus_1 - 3 * li - hi * beta[i - 1]) / (2 * hi + 2 * hi_plus_1 + hi * alpha[i - 1])

    for i in range(n - 2, 0, -1):
        splines[i].c = alpha[i] * splines[i + 1].c + beta[i]

    for i in range(n - 1, 0, -1):
        hi = x[i] - x[i - 1]
        li = y[i] - y[i - 1]
        splines[i].b = hi * (2.0 * splines[i].c + splines[i - 1].c) / 3.0 + (splines[i].a - splines[i-1].a) / hi
        splines[i].d = (splines[i].c - splines[i - 1].c) / 3*hi
    return splines


def Interpolate(splines, x, t=0):

    n = len(splines)
    s = SplineTuple(0, 0, 0, 0, 0)
    if x <= splines[0].x:
        s = splines[0]
    elif x >= splines[n - 1].x:
        s = splines[n - 1]
    else:
        i = 0
        j = n - 1
        while i + 1 < j:
            k = i + (j - i) // 2
            if x <= splines[k].x:
                j = k
            else:
                i = k
        s = splines[j]
    dx = x - s.x
    if t != 0:
        print("a={} ; b={} ; c={} ; d={}; x={}".format(s.a, s.b, s.c, s.d, s.x))
    return s.a + (s.b + (s.c / 2.0 + s.d * dx / 6.0) * dx) * dx


x = [1.0, 1.9, 2.8, 3.7, 4.6]
y = [2.4142, 1.0818, 0.50953, 0.11836, -0.24008]
x0 = 2.66666
spline = BuildSpline(x, y, len(x))
xx = [i for i in arange(x[0], x[-1], 0.01)]
yy = [Interpolate(spline, i) for i in xx]
plt.grid(True)
plt.scatter(x, y)
plt.plot(xx, yy)
y0 = Interpolate(spline, x0)
plt.scatter(x0, y0)
print("x={} -> y={}".format(x0, y0))
print()
for j in range(0, len(spline)):
    i = spline[j]
    print("a={} ; b={} ; c={} ; d={}; x={}".format(i.a, i.b, i.c, i.d, i.x))
y1 = Interpolate(spline, 1.5)
print()
print("В точке x={} -> y={}".format(1.5, y1))
y1 = Interpolate(spline, 1.5, 1)
plt.show()
