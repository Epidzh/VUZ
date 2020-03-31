from math import sqrt, fabs
import matplotlib.pyplot as plot
from numpy import arange


def func(x):
    return sqrt(x)


def lagrange(x, args, values, n):
    ans = 0
    for i in range(0, n):
        P = 1.0
        E = 1.0
        for j in range(0, n):
            if (j != i):
                P *= x - args[j]
                E *= args[i] - args[j]
        ans += P * values[i] / E
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


def newton(point, x):
    n = len(x)
    k = coeffs(x)
    ans = k[0]
    p = 1
    for i in range(1, n):
        p = p * (point - x[i - 1])
        ans += k[i] * p
    return ans


def display_lagrange(args, values, x_range):
    y = [lagrange(i, args, values, len(args)) for i in x_range]
    plot.plot(x_range, y, color="#0000FF", label='lagrange')


def display_newton(args, values, x_range):
    y = [newton(i, args) for i in x_range]
    plot.plot(x_range, y, color="#00BB00", label='newton')


def display_func(x_range):
    y = [func(i) for i in x_range]
    plot.plot(x_range, y, color="#FF0000", label='f(x)')


def main():
    args = [0, 1.7, 3.4, 5.1]
    values = list(map(func, args))
    x_left = args[0]
    x_right = args[-1]
    step = 0.1
    
    x_range = arange(x_left, x_right, step)
    x = 3.0
    print("Функция в точке x = {}; значение = {}".format(x, func(x)))
    print("Лагранж в точке x = {}; значение = {}".format(x, lagrange(x, args, values, len(args))))
    print("Ньютон в точке x = {}; значение = {}".format(x, newton(x, args)))

    # for i in x_range:
    #     print("x={}: f - {}, lagrange - {}, newton = {} ".format(i, func(i), lagrange(i, args, values, len(args)), newton(i, args)))
    
    fig = plot.figure()
    plot.grid(True)
    display_func(x_range)
    display_lagrange(args, values, x_range)
    display_newton(args, values, x_range)

    mx_value_diff = False
    mx_value_diff_point = False
    for i in arange(x_left, x_right, 0.01):
        a = func(i)
        b = lagrange(i, args, values, len(args))
        c = newton(i, args)
        if (mx_value_diff is False or mx_value_diff < fabs(a - b)):
            mx_value_diff = abs(a - b)
            mx_value_diff_point = i

    # print("MAX VALUE DIFFERENCE = {} at x = {}".format(mx_value_diff, mx_value_diff_point))
    # print("В точке x={}: f - {}, lagrange ={}, newton = {} ".format(mx_value_diff_point, func(mx_value_diff_point), lagrange(mx_value_diff_point, args, values, len(args)), newton(mx_value_diff_point, args)))

    # y = [func(i) for i in x]
    # print(y)
    # plot.plot(x, y, color="#FF0000", label='f(x)')

    # y = [lagrange(i, args, values, len(args)) for i in x]
    # print(y)
    # plot.plot(x, y, color="#00FF00", label='lagrange')

    # y = [newton(i, args) for i in x]
    # print(y)
    # plot.plot(x, y, color="#0000FF", label='newton')

    plot.legend()
    plot.show()


if (__name__ == "__main__"):
    main()
