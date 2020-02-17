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


def vib_sr(arr, N):
    mx = max(arr)
    digits = [0 for i in range(mx + 1)]
    w = [0 for i in range(mx + 1)]
    ans = 0
    for i in range(mx + 1):
        for j in arr:
            digits[i] = digits[i] + 1 if i == j else digits[i]
        w[i] = digits[i] / N
        ans += w[i] * i
    return ans

N=200
v = 54
n = 5 + (v % 16)
p = 0.3 + 0.005 * v
mo = n*p
D = n*p*(1 - p)
G = sqrt(D)
moda = [(n + 1)*p]
medi = round(n*p)
ass = ((1 - p) - p ) / G
eks = (1 - n*p ) / D

binom = get_random_binomial(n, p, N)
print("Binom")
print(binom)
print(sorted(binom))
print("Выборочное среднее: ", vib_sr(binom, N))

geom = get_random_geometric(p, N)
print("Geom")
print(geom)
print(sorted(geom))
print("Выборочное среднее: ", vib_sr(geom, N))

poisson = get_random_poisson(n*p, N)
print("Poisson")
print(poisson)
print(sorted(poisson))
print("Выборочное среднее: ", vib_sr(poisson, N))
