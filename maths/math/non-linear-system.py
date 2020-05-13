from math import tan, fabs, cos


def first(x1, x2):
    return 3 * x1**2 - x1 + x2**2 - 1
    # return 2*x1**2 - x1*x2 - 5*x1 + 1


def second(x1, x2):
    return x2 - tan(x1)
    # return x1 + 3*log10(x1) - x2**2


def is_continue(x1, old_x1, x2, old_x2, eps):
    return fabs(x1 - old_x1) > eps or (fabs(x2 - old_x2)) > eps


def simple(system, eps=0.01):
    new_system = [lambda x1, x2: (1 - x2**2) / (3*x1 - 1), lambda x: tan(x)]
    x1 = -0.5
    old_x1 = 0
    x2 = -0.5
    old_x2 = 0
    pribl = [x1, x2]

    iters = 0
    while is_continue(x1, old_x1, x2, old_x2, eps):
        old_x1 = x1
        old_x2 = x2
        x1 = new_system[0](old_x1, old_x2)
        x2 = new_system[1](old_x1)
        # print(x1, x2)
        iters += 1
    print("Начальные приближения: ", pribl)
    print("\nИтераций: ", iters)
    return [x1, x2]


def first_center(y2, y0, h):
    return (y2 - y0) / (2 * h)

def newton(system, eps=0.01):
    x1 = 0.5
    old_x1 = 0
    x2 = 0.5
    old_x2 = 0
    pribl = [x1, x2]

    iters = 0
    while is_continue(x1, old_x1, x2, old_x2, eps):
        old_x1 = x1
        old_x2 = x2
        delta_x1 = (-system[1](old_x1, old_x2) + system[0](old_x1, old_x2)) / ((-1/(cos(old_x1)**2)) - 6*old_x2 - 1)
        delta_x2 = -system[0](old_x1, old_x2) - (6*old_x2 - 1) * delta_x1
        x1 = old_x1 + delta_x1
        x2 = old_x2 + delta_x2
        # print(x1, x2)
        iters += 1
    print("Начальные приближения: ", pribl)
    print("\nИтераций: ", iters)
    return [x1, x2]

system = [first, second]
eps = 0.0001
print("Вариант - 4\n")
print("Точность: ", eps)

print("\nМетод простой итерации: ")
ans = simple(system, eps)
print("Ответ: ", ans)
print("Проверка:")
print("3 * x1**2 - x1 + x2**2 - 1 = {}\nx2 - tg(x1) = {}".format(system[0](ans[0], ans[1]), system[1](ans[0], ans[1])))

print("\nМетод Ньютона: ")
ans = newton(system, eps)
print("Ответ: ", ans)
print("Проверка:")
print("3 * x1**2 - x1 + x2**2 - 1 = {}\nx2 - tg(x1) = {}".format(system[0](ans[0], ans[1]), system[1](ans[0], ans[1])))