from math import exp
import matplotlib.pyplot as plot
from numpy import arange


def func(x):
    return x * x * exp(x)


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
        return (diff(args[0:len(args) - 1], values[0:len(args) - 1]) -
                diff(args[1:len(args)], values[1:len(args)])) / (args[0] - args[-1])
    return (values[0] - values[1]) / (args[0] - args[1])


def newton(x, args, values, n):
    ans = func(x)
    for i in range(2, len(args)):
        t = 1.0
        for j in range(0, len(args)):
            t *= (x - args[j])
        ans += t * diff(args[0:i], values[0:i])
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
    args = [-1.2, -0.7, -0.2, 0.3]
    values = list(map(func, args))
    x = -0.5
    print("(x^2*e^x) x = -0.5; value = {}".format(func(-0.5)))
    print("(lagrange) x = -0.5; value = {}".format(lagrange(x, args, values, len(args))))
    print("(newton) x = -0.5; value = {}".format(newton(x, args, values, len(args))))

    x_left = args[0]
    x_right = args[len(args) - 1]
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
