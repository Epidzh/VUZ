from matplotlib import pyplot


def get_normal(a, sigma, N):
    from numpy.random import normal
    return list(normal(a, sigma, 200))


def get_info_normal(R, N):
    from numpy import arange
    from math import log2
    m = 1 + round(log2(N))
    a0 = min(R)
    am = max(R)
    d = (am - a0) / m
    interval_raw = []
    for i, j in [[i, i + d] for i in arange(a0, am, d)]:
        count = 0
        for k in R:
            if i <= k <= j:
                count += 1
        interval_raw.append([(i, j), count, count / N])
    return [interval_raw, [[(i + j) / 2, k, l] for (i, j), k, l in interval_raw]]


N = 200
v = 54
a = (-1)**v * 0.1 * v
sigma = 0.01 * v + 1
# a = 2.6
# sigma = 1.26
L = 3 + (-1)**v * 0.01 * v

print("Normal: a = {}, sigma = {}".format(a, sigma))
R1 = get_normal(a, sigma, N)
print(sorted(R1))
t1, t2 = get_info_normal(R1, N)
