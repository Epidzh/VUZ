def f(x):
    eps = 0.00001
    if x + 0.2 < eps:
        return 1.7722
    elif x < eps:
        return 1.5708
    elif x - 0.2 < eps:
        return 1.3694
    elif x - 0.4 < eps:
        return 1.1593
    elif x - 0.6 < eps:
        return 0.9273


def first_left(y1, y0, h):
    return (y1 - y0) / h


def first_right(y2, y1, h):
    return (y2 - y1) / h


def first_center(y2, y0, h):
    return (y2 - y0) / (2*h)


def second(y2, y1, y0, h):
    return (y2 - 2*y1 + y0) / (h*h)


args = [-0.2, 0.0, 0.2, 0.4, 0.6]
x = 0.2
h = 0.2
print("x={}\nh={}".format(x, h))
print("first left derive: {}".format(first_left(f(x + h), f(x), h)))
print("first right derive: {}".format(first_right(f(x + h + h), f(x + h), h)))
print("first center derive: {}".format(first_center(f(x + h + h), f(x), h)))
print("second derive: {}".format(second(f(x + h + h), f(x + h), f(x), h)))
