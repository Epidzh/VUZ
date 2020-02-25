from math import sqrt
def get_random_binomial(n, p, size=1):
    from numpy.random import binomial
    return binomial(n, p, size)


def get_random_geometric(p, size=1):
    from numpy.random import geometric
    return geometric(p, size)


def get_random_poisson(l, size=1):
    from numpy.random import poisson
    return poisson(l, size)


def get_sr(w, N):
    ans = 0
    for i in range(len(w)):
        ans += i*w[i]
    return ans


def get_disp(w, x):
    ans = 0
    for i in range(len(w)):
        ans += (i - x)*(i - x)*w[i]
    return ans


def get_ni_w(arr, N):
    mx = max(arr)
    ni = [0 for i in range(mx + 1)]
    w = [0 for i in range(len(ni))]
    for i in range(mx + 1):
        for j in arr:
            ni[i] = ni[i] + 1 if i == j else ni[i]
        w[i] = ni[i] / N
    return [ni, w]


def get_func(w, x):
    if (x < w[0]):
        return 0
    elif x > w[-1]:
        return 1
    else:
        ans = 0
        i = 0
        while w[i] < x:
            ans += w[i]
            i += 1
        return ans


def get_med(w):
    ans = 0
    for i in range(1, len(w) - 1):
        if get_func(w, i - 1) < 0.5 and get_func(w, i) > 0.5:
            ans = i
            break
        elif get_func(w, x) == 0.5:
            ans = 0.5*(i + i + 1)
            break
    return ans


N = 200
v = 54
n = 5 + (v % 16)
p = 0.3 + 0.005 * v
mo = n*p
D = n*p*(1 - p)
G = sqrt(D)
moda = [(n + 1)*p]
ass = ((1 - p) - p ) / G
eks = (1 - n*p ) / D
print("n={} ; p={}".format(n , p))

print("Binom")
binom = get_random_binomial(n, p, N)
print(binom)
print(sorted(binom))
ni, w = get_ni_w(binom, N)
x = get_sr(w, N)
disp = get_disp(w, x)
print("Выборочное среднее: ", x)
print("Выборочная дисперсия: ", disp)
print("Выборочное среднее квадратическое отклонение: ", sqrt(disp))
print("Выборочная мода:", ni.index(max(ni)))
print("Выборочная медиана:", get_med(w))

print("Geom")
geom = get_random_geometric(p, N)
print(geom)
print(sorted(geom))
ni, w = get_ni_w(geom, N)
x = get_sr(w, N)
disp = get_disp(w, x)
print("Выборочное среднее: ", x)
print("Выборочная дисперсия: ", disp)
print("Выборочное среднее квадратическое отклонение: ", sqrt(disp))
print("Выборочная мода:", ni.index(max(ni)))
print("Выборочная медиана:", get_med(w))

print("Poisson")
poisson = get_random_poisson(n*p, N)
print(poisson)
print(sorted(poisson))
ni, w = get_ni_w(poisson, N)
x = get_sr(w, N)
disp = get_disp(w, x)
print("Выборочное среднее: ", x)
print("Выборочная дисперсия: ", disp)
print("Выборочное среднее квадратическое отклонение: ", sqrt(disp))
print("Выборочная мода:", ni.index(max(ni)))
print("Выборочная медиана:", get_med(w))