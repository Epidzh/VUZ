from numpy import arange


def func(x):
    return (3 * x + 4) / (2 * x + 7)


def rectangle(fun, a, b, n):
    h = float(b - a) / n
    result = fun(a+0.5*h)
    for i in arange(1, n):
        result += fun(a + 0.5*h + i*h)
    result *= h
    return result


def trap(fun, a, b, n):
    h = float(b - a) / n
    sum = (fun(a) + fun(b)) / 2
    for i in arange(1, n):
        sum += fun(a + i*h)
    return sum * h


def simpson(fun, a, b, n):
    n = int(n) if n % 2 == 0 else int(n + 1)
    h = float(b - a) / n
    sum = func(a) + func(b) + 4 * fun(a + h)
    for i in arange(1, int(n / 2)):
        sum += 2 * fun(a + 2*i*h) + 4 * fun(a + (2*i + 1)*h)
    return sum * h / 3


a, b, h = -2, 2, 1.0
n = float(b - a) / h
print("Точное значение интеграла = ~1.777")
print("Метод прямоугольников (h)   = {}".format(rectangle(func, a, b, n)))
print("Метод прямоугольников (h/2) = {}".format(rectangle(func, a, b, n * 2)))
print("Метод трапеций (h)   = {}".format(trap(func, a, b, n)))
print("Метод трапеций (h/2) = {}".format(trap(func, a, b, n * 2)))
print("Метод симпсона (h)   = {}".format(simpson(func, a, b, n)))
print("Метод симпсона (h/2) = {}".format(simpson(func, a, b, n * 2)))
