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


def get_sr(R, N):
    ans = 0
    for xi, ni, wi in R:
        ans += xi * wi
    return ans


def get_disp(R, sr):
    ans = 0
    for xi, ni, wi in R:
        ans += (xi - sr)*(xi - sr)*wi
    return ans


def get_xi_ni_wi(xi, N):
    xi.sort()
    mx = xi[-1]
    ni = [0 for i in range(mx + 1)]
    wi = [0 for i in range(len(ni))]
    for i in range(mx + 1):
        for j in xi:
            ni[i] = ni[i] + 1 if i == j else ni[i]
        wi[i] = ni[i] / N
    return list(zip(*[(list(range(mx + 1))), (ni), (wi)]))


def get_func(w, x):
    if (x < R[0][0]):
        return 0
    elif x >= R[-1][0]:
        return 1
    else:
        ans = 0
        i = 0
        while R[i][0] <= x:
            ans += R[i][2]
            i += 1
        return ans


def get_med(R):
    ans = 0
    for i in range(1, len(R) - 1):
        if get_func(R, R[i][0]) > 0.5:
            ans = R[i][0]
            break
        elif get_func(R, R[i][0]) == 0.5:
            ans = 0.5*(R[i][0] + R[i][0] + 1)
            break
    return ans


def get_moda(R):
    return max([(j, i) for i, j, _ in R])[1]


def get_moment(R, k):
    ans = 0
    for xi, ni, wi in R:
        ans += (xi**k)*wi
    return ans


def get_k_asim(R, disp):
    ans = get_moment(R, 3) - 3*get_moment(R, 2)*get_moment(R, 1)
    return ( ans + 2*(get_moment(R, 1)**3)) / (disp**3)


def get_k_eks(R, disp):
    ans = get_moment(R, 4) - 4*get_moment(R, 3)*get_moment(R, 1)
    ans += 6* get_moment(R, 2)*(get_moment(R, 1)**2)
    ans -= 3*(get_moment(R, 1)**4)
    return (ans / (disp**4)) - 3


N = 200
v = 54
n = 5 + (v % 16)
p = 0.3 + 0.005 * v
print("n={} ; p={}".format(n , p))

print("Binom")
#binom = get_random_binomial(n, p, N)
binom = [7, 7, 6, 7, 5, 7, 6, 7, 9, 9, 5, 7, 5, 5, 7, 5, 7, 8, 4, 7, 0, 3, 7, 5, 6, 9, 7, 7, 7, 2, 8, 4, 4, 5, 4, 8, 6, 7, 6, 7, 6, 8, 8, 8, 7, 5, 6, 4, 6, 4, 8, 5, 4,9, 5, 8, 9, 4, 5, 7, 6, 7, 7, 6, 5, 7, 6, 6, 6, 6, 5, 6, 7, 7, 8, 6, 8, 6, 6, 6, 7, 7, 4, 7, 7, 5, 3, 5, 7, 8, 6, 10, 5, 8, 7, 7, 8, 9, 10, 8, 4, 8, 4, 7, 7, 5, 8, 10, 6, 5, 9, 6, 5, 6, 7, 6, 7, 10, 7, 4, 6, 9, 7, 5, 7, 8, 7, 8, 4, 8, 6, 8, 7, 8, 8, 7, 8, 9, 8, 5, 6, 7, 8, 5, 8, 7, 7, 6, 9, 8, 6, 11, 5, 8, 5, 6, 8, 4,7, 5, 8, 9, 6, 9, 5, 7, 5, 4, 5, 8, 7, 8, 8, 8, 7, 6, 8, 1, 7, 7, 5, 7, 7, 8, 7, 6, 8, 4, 11, 8, 7, 5, 7, 3, 9, 6, 6, 7, 4, 6]
print(sorted(binom))
R = get_xi_ni_wi(binom, N)
print(R)
sr = get_sr(R, N)
disp = get_disp(R, sr)
print("Выборочное среднее: ", sr)
print("Выборочная дисперсия: ", disp)
print("Выборочное среднее квадратическое отклонение: ", sqrt(disp))
print("Выборочная мода:", get_moda(R))
print("Выборочная медиана:", get_med(R))
print("Выборочный коэффициент асимметрии: ", get_k_asim(R, sqrt(disp)))
print("Выборочный коэффициент эксцесса: ", get_k_eks(R, sqrt(disp)))


print("Geom")
#geom = get_random_geometric(p, N)
geom = [2, 2, 1, 1, 6, 2, 1, 4, 2, 1, 1, 3, 1, 6, 3, 1, 2, 1, 4, 1, 1, 1, 7, 2, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 3, 1, 3, 1, 4, 1, 1, 1, 1, 1, 1, 2, 1,1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 5, 2, 1, 4, 3, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 2, 2, 1, 5, 1, 1, 2, 1, 1, 1, 1, 1, 1, 4, 1, 3, 1, 3, 1, 2, 1, 2, 3, 3, 2, 3, 4, 1, 1, 8, 1, 3, 1, 2, 2, 2, 4, 4, 1, 3, 1, 1, 1, 2, 2, 1, 1, 1, 2, 1, 2, 2, 1, 1,1, 1, 1, 2, 1, 3, 1, 7, 2, 3, 1, 4, 1, 2, 4, 1, 6, 3, 1, 1, 1, 3, 3, 1, 1, 2, 1, 1, 1, 1, 3, 1, 2, 1, 2, 3, 4, 1, 1, 1, 1, 2, 1, 2, 3, 2, 1, 1, 2, 2, 1, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 3]
print(sorted(geom))
R = get_xi_ni_wi(geom, N)
print(R)
sr = get_sr(R, N)
disp = get_disp(R, sr)
print("Выборочное среднее: ", sr)
print("Выборочная дисперсия: ", disp)
print("Выборочное среднее квадратическое отклонение: ", sqrt(disp))
print("Выборочная мода:", get_moda(R))
print("Выборочная медиана:", get_med(R))
print("Выборочный коэффициент асимметрии: ", get_k_asim(R, sqrt(disp)))
print("Выборочный коэффициент эксцесса: ", get_k_eks(R, sqrt(disp)))


print("Poisson")
#poisson = get_random_poisson(n*p, N)
poisson = [4, 11, 11, 5, 11, 3, 8, 6, 5, 8, 6, 5, 5, 10, 4, 5, 5, 1, 3, 4, 5, 4, 5, 4, 2,11, 11, 6, 6, 4, 6, 6, 3, 10, 7, 7, 5, 2, 7, 3, 8, 11, 4, 9, 6, 6, 4, 9, 4, 6, 7, 5, 5, 5, 5, 6, 3, 9, 2, 10, 1, 5, 4, 1, 6, 14, 8, 6, 6, 6, 4, 4, 4, 2, 7, 6, 5, 2, 8, 1, 8, 6, 6, 6, 5, 5, 5, 4, 5, 7, 5, 3, 2, 7, 8, 5, 3, 5, 5, 6, 6, 4, 8,7, 6, 5, 3, 4, 10, 7, 4, 3, 3, 3, 6, 6, 6, 9, 5, 8, 3, 5, 2, 7, 12, 7, 7, 8, 6,2, 8, 5, 7, 5, 10, 4, 3, 0, 5, 8, 2, 3, 5, 6, 5, 7, 5, 7, 10, 3, 7, 10, 8, 8, 7, 7, 2, 8, 4, 5, 7, 4, 7, 6, 7, 11, 1, 3, 4, 7, 5, 7, 7, 7, 2, 7, 7, 10, 5, 9, 5, 6, 7, 7, 7, 2, 13, 6, 5, 5, 5, 8, 5, 0, 10, 2, 5, 6, 3, 13]
print(sorted(poisson))
R = get_xi_ni_wi(poisson, N)
print(R)
sr = get_sr(R, N)
disp = get_disp(R, sr)
print("Выборочное среднее: ", sr)
print("Выборочная дисперсия: ", disp)
print("Выборочное среднее квадратическое отклонение: ", sqrt(disp))
print("Выборочная мода:", get_moda(R))
print("Выборочная медиана:", get_med(R))
print("Выборочный коэффициент асимметрии: ", get_k_asim(R, sqrt(disp)))
print("Выборочный коэффициент эксцесса: ", get_k_eks(R, sqrt(disp)))