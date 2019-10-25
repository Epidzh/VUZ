from math import sqrt
import matplotlib.pyplot as plot
from numpy import arange


def func(x):
    return sqrt(x)


def lagrange(x, args, values, n):
    ans = 0
    for i in range(0, n):
        P = 1.0
        for j in range(0, n):
            if (j != i):
                P *= (x - args[j]) / (args[i] - args[j])
        ans += P * values[i]
    return ans


def diff(args, values):
    if len(args) > 2:
        return (diff(args[:-1], values[:-1]) -
                diff(args[1:], values[1:])) / (args[0] - args[-1])
    return (values[0] - values[-1]) / (args[0] - args[-1])


def newton(x, args, values, n):
    ans = func(args[0]) + (x - args[1]) * diff(args[:2], values[:2])
    for i in range(2, len(args)):
        t = 1.0
        print(list(range(0, i)))
        for j in range(0, i):
            t *= (x - args[j])
        ans += t * diff(args[:i], values[:i])
    return ans


def display_lagrange(points, values, x_left, x_right, step):
    x = arange(x_left, x_right, step)
    y = [lagrange(i, points, values, len(points)) for i in x]
    plot.plot(x, y, color="#0000FF", label='lagrange')


def display_newton(points, values, x_left, x_right, step):
    x = arange(x_left, x_right, step)
    y = [newton(i, points, values, len(points)) for i in x]
    plot.plot(x, y, color="#00BB00", label='newton')


def display_func(x_left, x_right, step):
    x = arange(x_left, x_right, step)
    y = [func(i) for i in x]
    plot.plot(x, y, color="#FF0000", label='f(x)')


def main():
    args = [0, 1.7, 3.4, 5.1]
    values = list(map(func, args))
    x = 3.0
    print("(sqrt(x)) x = {}; value = {}".format(x, func(x)))
    print("(lagrange) x = {}; value = {}".format(x, lagrange(x, args, values, len(args))))
    print("(newton) x = {}; value = {}".format(x, newton(x, args, values, len(args))))

    x_left = args[0]
    x_right = args[-1]
    step = 0.01

    fig = plot.figure()
    plot.grid(True)
    display_func(x_left, x_right, step)
    display_lagrange(args, values, x_left, x_right, step)
    display_newton(args, values, x_left, x_right, step)
    plot.legend()
    plot.show()


if (__name__ == "__main__"):
    main()
