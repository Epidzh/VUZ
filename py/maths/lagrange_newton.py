from math import sqrt
import matplotlib.pyplot as plot
from numpy import arange


def func(x):
    return sqrt(x)


def lagrange(x, f, n):
    ans = 0
    for i in range(0, n):
        P = 1.0
        E = 1.0
        for j in range(0, n):
            if (j != i):
                P *= x - list(f.keys())[j]
                E *= list(f.keys())[i] - list(f.keys())[j]
        ans += P * list(f.values())[i] / E
    return ans


def coeffs(x):
    n = len(x)
    y = list(map(func, x))
    k = [0] * n
    k[0] = y[0]
    for j in range(1, n):
        for i in range(0, n - j):
            y[i] = (y[i + 1] - y[i]) / (x[i + j] - x[i])
            k[j] = y[0]
    return k


def Newtone(point, x):
    n = len(x)
    k = coeffs(x)
    ans = k[0]
    p = 1
    for i in range(1, n):
        p = p * (point - x[i - 1])
        ans += k[i] * p
    return ans


def display_lagrange(f, x_left, x_right, step):
    x = arange(x_left, x_right, step)
    y = [lagrange(i, f, len(f)) for i in x]
    plot.plot(x, y, color="#0000FF", label='lagrange')


def display_newton(f, x_left, x_right, step):
    x = arange(x_left, x_right, step)
    y = [Newtone(i, x) for i in x]
    plot.plot(x, y, color="#00BB00", label='newton')


def display_func(x_left, x_right, step):
    x = arange(x_left, x_right, step)
    y = [func(i) for i in x]
    plot.plot(x, y, color="#FF0000", label='f(x)')


def main():
    args = [0, 1.7, 3.4, 5.1]
    x_left = args[0]
    x_right = args[-1]
    step = 0.1
    f = dict(zip(args, list(map(func, args))))
    x = 3.0
    print("(sqrt(x)) x = {}; value = {}".format(x, func(x)))
    print("(lagrange) x = {}; value = {}".format(x, lagrange(x, f, len(f))))
    print("(newton) x = {}; value = {}".format(x, Newtone(x, args)))

    fig = plot.figure()
    plot.grid(True)
    display_func(x_left, x_right, step)
    display_lagrange(f, x_left, x_right, step)
    display_newton(f, x_left, x_right, step)
    plot.legend()
    plot.show()


if (__name__ == "__main__"):
    main()
