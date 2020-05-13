from numpy import arange
from matplotlib import pyplot
from math import sqrt, fabs


def function(x, p):
    k = p(1.1)
    a = 1.05
    b = 1.35
    return k*(a*x + b)*p(x)


def f_x(x):
    if x == 1.05:
        return 2.3
    elif x == 1.15:
        return 2.74
    elif x == 1.25:
        return 3.46
    elif x == 1.35:
        return 4.6


def newton(point, x):
    def coeffs(x):
        n = len(x)
        y = list(map(f_x, x))
        k = [0] * n
        k[0] = y[0]
        for j in range(1, n):
            for i in range(0, n - j):
                y[i] = (y[i + 1] - y[i]) / (x[i + j] - x[i])
                k[j] = y[0]
        return k

    n = len(x)
    k = coeffs(x)
    # print(k)
    ans = k[0]
    p = 1
    for i in range(1, n):
        p = p * (point - x[i - 1])
        ans += k[i] * p
    # print(ans)
    return ans


def main():
    eps = 0.001
    a = 1.05
    b = 1.35
    args = [1.05, 1.15, 1.25, 1.35]
    P = lambda x: newton(x, args)
    x = [i for i in arange(args[0], args[-1], 0.01)]
    y = [function(i, P) for i in x]
    print(x)
    print(y)
    pyplot.grid(True)
    pyplot.plot(x, y, color="#00AA00", label='F_x')
    # pyplot.plot(args, [f_x(i) for i in args], color="#0000AA", label='f_x')
    # pyplot.plot(x, [P(i) for i in x], color="#AA0000", label='newton')
    pyplot.legend()
    # pyplot.show()
    print([P(i)for i in args])
    print(P(1.1))

    F = (sqrt(5) - 1) / 2
    while fabs(b - a) > eps:
        x1, x2 = a + (1 - F) * (b - a), a + F*(b - a)
        if function(x1, P) >= function(x2, P):
            a = x1
        else:
            b = x2
    print("Минимум функции: ", (a + b) / 2)
    print("Значение функции: ", function((a+b) / 2, P))
    print("Точное значение: ", function(1.05, P))


if __name__ == "__main__":
    main()