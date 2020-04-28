from math import sin, fabs, sqrt
from numpy import arange, arcsin


interval = (-10, 10)


def function(x):
    return sin(x) - x*x + 1


def half_dev_method(func, interval, eps=0.0001, h=0.1):
    ans = []
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    for (left, right) in intervals:
        if func(left) * func(right) < 0:
            a, b, middle = left, right, (left + right) / 2
            while b - a > eps:
                middle = (a + b) / 2
                if func(middle) * func(a) < 0:
                    b = middle
                elif func(middle) * func(b):
                    a = middle
                else:
                    break
                # print(middle)
            if func(middle) < eps:
                ans.append(middle)
                # print("\n")
    return ans


def simple_iteration_method(func, interval, eps=0.001, h=0.1):
    ans = []
    N = 25
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    # new_func = lambda x: arcsin(x**2 - 1)
    new_func1 = lambda x: sqrt(sin(x) + 1)
    new_func2 = lambda x: -sqrt(sin(x) + 1)
    for (left, right) in intervals:
        if func(left) * func(right) < 0:
            tmp = (right + left) / 2
            if (left > 0):
                new_func = new_func1
            else:
                new_func = new_func2
            prev = right
            while fabs(func(tmp) - func(prev)) > eps:
                prev = tmp
                tmp = new_func(tmp)
                # print(tmp)
            if func(tmp) < eps:
                ans.append(tmp)
                # print("\n")
    return ans


def first_center(y2, y0, h):
    return (y2 - y0) / (2 * h)


def newton_method(func, interval, eps=0.001, h=0.1):
    ans = []
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    for (left, right) in intervals:
        if func(left) * func(right) < 0:
            prev = right
            tmp = (left + right) / 2
            # print(tmp)
            while fabs(func(tmp) - func(prev)) > eps:
                prev = tmp
                tmp = tmp - (func(tmp) / first_center(func(tmp+0.1), func(tmp-0.1), 0.1))
                # print(tmp)
            if func(tmp) < eps:
                ans.append(tmp)
                # print("\n")
    return ans


def secant_method(func, interval, eps=0.001, h=0.1):
    ans = []
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    for (left, right) in intervals:
        if func(left) * func(right) < 0:
            prev = right
            tmp = (left + right) / 2
            while fabs(func(tmp) - func(prev)) > eps:
                kek = tmp
                tmp = tmp - ((func(tmp) / (func(tmp) - func(prev))) * (tmp - prev))
                prev = kek
                # print(tmp)
            if func(tmp) < eps:
                ans.append(tmp)
    return ans


print("Метод половинного деления: ")
ans = half_dev_method(function, interval)
print("Корни: ", ans)
print("Подстановка: ")
print("sin({}) - {}**2 + 1 = {}".format(ans[0], ans[0], function(ans[0])))
print("sin({}) - {}**2 + 1 = {}".format(ans[1], ans[1], function(ans[1])))

print("\nМетод простой итерации: ")
ans = simple_iteration_method(function, interval)
print("Корни: ", ans)
print("Подстановка: ")
print("sin({}) - {}**2 + 1 = {}".format(ans[0], ans[0], function(ans[0])))
print("sin({}) - {}**2 + 1 = {}".format(ans[1], ans[1], function(ans[1])))

print("\nМетод Ньютона: ")
ans = newton_method(function, interval)
print("Корни: ", ans)
print("Подстановка: ")
print("sin({}) - {}**2 + 1 = {}".format(ans[0], ans[0], function(ans[0])))
print("sin({}) - {}**2 + 1 = {}".format(ans[1], ans[1], function(ans[1])))

print("\nМетод секущих: ",)
ans = secant_method(function, interval)
print("Корни: ", ans)
print("Подстановка: ")
print("sin({}) - {}**2 + 1 = {}".format(ans[0], ans[0], function(ans[0])))
print("sin({}) - {}**2 + 1 = {}".format(ans[1], ans[1], function(ans[1])))