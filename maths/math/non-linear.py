from math import sin, fabs, sqrt, exp
from numpy import arange, arcsin


interval = (-10, 10)


def function(x):
    return x*exp(-x) - 1/(2*exp(1))
    # return sin(x) + x**2 - 1


def half_dev_method(func, interval, eps=0.0001, h=0.1):
    iters = []
    ans = []
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    pribl = []
    for (left, right) in intervals:
        if func(left) * func(right) < 0:
            a, b, middle = left, right, (left + right) / 2
            pribl.append(middle)
            iter = 0
            while b - a > eps:
                iter += 1
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
                iters.append(iter)
                # print("\n")
    print("Начальные приближения: ", pribl)
    print("Итераций: для x1 - {} ; для x2 - {}".format(iters[0], iters[1]))
    return ans


def simple_iteration_method(func, interval, eps=0.001, h=0.1):
    iters = []
    ans = []
    N = 25
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    # new_func = lambda x: arcsin(x**2 - 1)
    new_func1 = lambda x: sqrt(sin(x) + 1)
    new_func2 = lambda x: -sqrt(sin(x) + 1)
    pribl = []
    for (left, right) in intervals:
        if func(left) * func(right) < 0:
            tmp = (right + left) / 2
            if (left > 0):
                new_func = new_func1
            else:
                new_func = new_func2
            prev = right
            iter = 0
            pribl.append(tmp)
            while fabs(func(tmp) - func(prev)) > eps:
                iter += 1
                prev = tmp
                tmp = new_func(tmp)
                # print(tmp)
            if func(tmp) < eps:
                ans.append(tmp)
                iters.append(iter)
                # print("\n")
    print("Начальные приближения: ", pribl)
    print("Итераций: для x1 - {} ; для x2 - {}".format(iters[0], iters[1]))
    return ans


def first_center(y2, y0, h):
    return (y2 - y0) / (2 * h)


def newton_method(func, interval, eps=0.001, h=0.1):
    iters = []
    pribl = []
    ans = []
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    for (left, right) in intervals:
        # if first_center
        if func(left) * func(right) < 0:
            prev = right
            tmp = (left+right) / 2
            pribl.append(tmp)
            # print(tmp)
            iter = 0
            while fabs(func(tmp) - func(prev)) > eps:
                iter += 1
                prev = tmp
                tmp = tmp - (func(tmp) / first_center(func(tmp+0.1), func(tmp-0.1), 0.1))
                # print(tmp)
            if func(tmp) < eps:
                ans.append(tmp)
                iters.append(iter)
                # print("\n")
    print("Начальные приближения: ", pribl)
    print("Итераций: для x1 - {} ; для x2 - {}".format(iters[0], iters[1]))
    return ans


def secant_method(func, interval, eps=0.001, h=0.1):
    iters = []
    ans = []
    intervals = [(i, i+h) for i in arange(interval[0], interval[1], h)]
    pribl = []
    for (left, right) in intervals:
        if func(left) * func(right) < 0:
            prev = right
            tmp = (left + right) / 2
            pribl.append(tmp)
            iter = 0
            while fabs(func(tmp) - func(prev)) > eps:
                iter += 1
                kek = tmp
                tmp = tmp - ((func(tmp) / (func(tmp) - func(prev))) * (tmp - prev))
                prev = kek
                # print(tmp)
            if func(tmp) < eps:
                ans.append(tmp)
                iters.append(iter)
    print("Начальные приближения: ", pribl)
    print("Итераций: для x1 - {} ; для x2 - {}".format(iters[0], iters[1]))
    return ans

print("Вариант - ", 4)
eps = 0.00001
anss = [-0.636733, 1.40962]
# print("\nПогрешность: 0.00001\n")
# print("\nМетод половинного деления:\n")
# ans = half_dev_method(function, interval, eps)
# print("\nКорни: x1={} ; x2={}".format(ans[0], ans[1]))
# print("Подстановка: ")
# print("sin({}) - {}**2 + 1 = {}".format(ans[0], fabs(ans[0]), function(ans[0])))
# print("sin({}) - {}**2 + 1 = {}".format(ans[1], fabs(ans[1]), function(ans[1])))
# print("\nПогрешности: для x1 - {} ; для x2 - {}".format(fabs(ans[0] - anss[0]), fabs(ans[1] - anss[1])))

# print("\n\nМетод простой итерации:\n")
# ans = simple_iteration_method(function, interval, eps)
# print("\nКорни: x1={} ; x2={}".format(ans[0], ans[1]))
# print("Подстановка: ")
# print("sin({}) - {}**2 + 1 = {}".format(ans[0], fabs(ans[0]), function(ans[0])))
# print("sin({}) - {}**2 + 1 = {}".format(ans[1], fabs(ans[1]), function(ans[1])))
# print("\nПогрешности: для x1 - {} ; для x2 - {}".format(fabs(ans[0] - anss[0]), fabs(ans[1] - anss[1])))

print("\n\nМетод Ньютона:\n")
ans = newton_method(function, interval, eps)
print("\nКорни: x1={} ; x2={}".format(ans[0], ans[1]))
print("Подстановка: ")
print("sin({}) - {}**2 + 1 = {}".format(ans[0], fabs(ans[0]), function(ans[0])))
print("sin({}) - {}**2 + 1 = {}".format(ans[1], fabs(ans[1]), function(ans[1])))
print("\nПогрешности: для x1 - {} ; для x2 - {}".format(fabs(ans[0] - anss[0]), fabs(ans[1] - anss[1])))

# print("\n\nМетод секущих:\n",)
# ans = secant_method(function, interval, eps)
# print("\nКорни: x1={} ; x2={}".format(ans[0], ans[1]))
# print("Подстановка: ")
# print("sin({}) - {}**2 + 1 = {}".format(ans[0], fabs(ans[0]), function(ans[0])))
# print("sin({}) - {}**2 + 1 = {}".format(ans[1], fabs(ans[1]), function(ans[1])))
# print("\nПогрешности: для x1 - {} ; для x2 - {}".format(fabs(ans[0] - anss[0]), fabs(ans[1] - anss[1])))