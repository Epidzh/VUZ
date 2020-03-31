def f(x):
    eps = 0.00001
    if x < eps:
        return 0.0
    elif x - 1.0 < eps:
        return 1.0
    elif x - 2.0 < eps:
        return 1.4142
    elif x - 3.0 < eps:
        return 1.7321
    elif x - 4.0 < eps:
        return 2.0


def second(y2, y1, y0, h):
    return (y2 - 2*y1 + y0) / (h*h)


def first_left(y1, y0, h):
    return (y1 - y0) / h


def first_right(y2, y1, h):
    return (y2 - y1) / h


def first_center(y2, y0, h):
    return (y2 - y0) / (2 * h)


def second_right(y2, y1, y0, h):
    return first_right(y2, y1, h) - first_right(y1, y0, h) / h


args = [0, 1.0, 2.0, 3.0, 4.0]
x = 2.0
h = 1.0
print("x={}\nh={}".format(x, h))
print("Первая левая производная: {}".format(first_left(f(x), f(x - h), h)))
print("Первая правая производная: {}".format(first_right(f(x + h), f(x), h)))
print("Первая центральная производная: {}".format(first_center(f(x + h), f(x - h), h)))
# print("second derive: {}".format(second(f(x + h), f(x), f(x - h), h)))
# print("second right: {}".format(second_right(f(x + h + h), f(x + h), f(x), h)))
print("Вторая производная: {}".format(second(f(x + h), f(x), f(x - h), h)))
