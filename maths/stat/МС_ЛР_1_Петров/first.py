from math import sqrt
from matplotlib import pyplot
from numpy.random import binomial, geometric, poisson
import docx


"""Генерация size псевдослучайных чисел, распределенных по
биномиальному закону с параметрами n и p
"""
def get_random_binomial(n, p, size=1):
    return binomial(n, p, size)


"""Генерация size псевдослучайных чисел, распределенных по
геометрическому закону с параметром p
"""
def get_random_geometric(p, size=1):
    return [i-1 for i in geometric(p, size)]


"""Генерация псевдослучайных чисел, распределенных по
закону Пуассона с параметром l
"""
def get_random_poisson(l, size=1):
    return poisson(l, size)


"""Получение выборочного среднего из коллекции R"""
def get_sr(R):
    ans = 0
    for xi, ni, wi in R:
        ans += xi * wi
    return ans


"""Получение выборочной дисперсии из коллекции R с выборочным средним sr"""
def get_disp(R, sr):
    ans = 0
    for xi, ni, wi in R:
        ans += (xi - sr)*(xi - sr)*wi
    return ans


"""Получение генерация коллекции R - статистического ряда"""
def get_xi_ni_wi(xi, N):
    xi = sorted(xi)
    mx = xi[-1]
    ni = [0 for i in range(mx + 1)]
    wi = [0 for i in range(len(ni))]
    for i in range(mx + 1):
        for j in xi:
            ni[i] = ni[i] + 1 if i == j else ni[i]
        wi[i] = ni[i] / N
    return list(zip(*[(list(range(mx + 1))), (ni), (wi)]))


"""Получение значения эмпирической функции распределения в точке x"""
def get_func(R, x):
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


"""Получение выборочной медианы из коллекции R"""
def get_med(R):
    ans = 0
    for i in range(len(R) - 1):
        if get_func(R, R[i][0]) > 0.5:
            ans = R[i][0]
            break
        elif get_func(R, R[i][0]) == 0.5:
            ans = 0.5*(R[i][0] + R[i+1][0])
            break
    return ans


"""Получение выборочной моды из коллекции R"""
def get_moda(R):
    moda = max([(j, i) for i, j, _ in R])[1]
    count = [i for i, _, _ in R].count(moda)
    if count > 1:
        moda *= 0.5 * count
    return moda


"""Получение выборочного момента порядка k из коллекции R"""
def get_moment(R, k):
    ans = 0
    for xi, ni, wi in R:
        ans += (xi**k)*wi
    return ans


"""Получение выборочного коэффициента асимметрии из коллекции R"""
def get_k_asim(R, disp):
    ans = get_moment(R, 3) - 3*get_moment(R, 2)*get_moment(R, 1)
    return (ans + 2*(get_moment(R, 1)**3)) / (disp**3)


"""Получение выборочного коэффициента эксцесса из коллекции R"""
def get_k_eks(R, disp):
    ans = get_moment(R, 4) - 4*get_moment(R, 3)*get_moment(R, 1)
    ans += 6* get_moment(R, 2)*(get_moment(R, 1)**2)
    ans -= 3*(get_moment(R, 1)**4)
    return (ans / (disp**4)) - 3


"""Получение теоретического значения биномиального распределения"""
def get_teoretic_binom(n, k, p):
    from math import factorial
    return (factorial(n) * (p**k) * (1 - p)**(n-k)) / (factorial(k)* factorial(n - k))


"""Получение теоретического значения геометрического распределения"""
def get_teoretic_geometric(k, p):
    return (1 - p)**k * p


"""Получение теоретического значения распределения Пуассона"""
def get_teoretic_poisson(l, k):
    from math import exp, factorial
    return (l**k * exp(-l)) / factorial(k)


"""Получение информации о выборке"""
def get_info(R, N):
    sr = get_sr(R)
    disp = get_disp(R, sr)
    print("Выборочное среднее: ", sr)
    print("Выборочная дисперсия: ", disp)
    print("Выборочное среднее квадратическое отклонение: ", sqrt(disp))
    print("Выборочная мода:", get_moda(R))
    print("Выборочная медиана:", get_med(R))
    print("Выборочный коэффициент асимметрии: ", get_k_asim(R, sqrt(disp)))
    print("Выборочный коэффициент эксцесса: ", get_k_eks(R, sqrt(disp)))


"""Отрисовка стрелок"""
def draw_arrows(plt, R):
    plt.figure()
    plt.grid(True)
    plt.axis([0, max([i for i, _, _ in R]), 0, 1.0])
    for i in range(len(R)-1):
        x1 = R[i][0]+0.0001
        x2 = R[i+1][0] - 0.0001
        y1 = get_func(R, x1)
        y2 = get_func(R, x2)
        plt.arrow(x1, y1, x2-x1, 0, head_width=0.01, head_length=0.2, length_includes_head=True)


"""Отрисовка графика"""
def draw(R1, R2, R3, n, p):
    pyplot.figure()
    pyplot.grid(True)
    pyplot.plot([i for i in range(n+1)], [(R1[i][2] if i <= len(R1) - 1 else 0) for i in range(n+1)], color='blue')
    pyplot.plot([i for i in range(n+1)], [get_teoretic_binom(n, i, p) for i in range(n+1)], color='red')
    draw_arrows(pyplot, R1)

    pyplot.figure()
    pyplot.grid(True)
    pyplot.plot([i for i, _, _ in R2], [k for _, _, k in R2], color='blue')
    pyplot.plot([i for i, _, _ in R2], [get_teoretic_geometric(i, p) for i, _, _ in R2], color='red')
    draw_arrows(pyplot, R2)

    pyplot.figure()
    pyplot.grid(True)
    pyplot.plot([i for i, _, _ in R3], [k for _, _, k in R3], color='blue')
    pyplot.plot([i for i, _, _ in R3], [get_teoretic_poisson(l, i) for i, _, _ in R3], color='red')
    draw_arrows(pyplot, R3)

    # pyplot.show()

N = 200
v = 44
n = 5 + (v % 16)
p = 0.3 + 0.005 * v
print("n={} ; p={}".format(n, p))

print("Binom")
binom = get_random_binomial(n, p, N)
print(binom)
R1 = get_xi_ni_wi(binom, N)
print(R1)
get_info(R1, N)

print("Geom")
# geom = get_random_geometric(p, N)
geom = []
for _ in range(100):
    geom.append(0)
for _ in range(51):
    geom.append(2)
for _ in range(28):
    geom.append(2)
for _ in range(13):
    geom.append(3)
for _ in range(6):
    geom.append(4)
for _ in range(2):
    geom.append(5)
print(geom)
R2 = get_xi_ni_wi(geom, N)
print(R2)
get_info(R2, N)

print("Poisson")
l = 0.5+0.01*v
print("l = ", l)
poisson = get_random_poisson(l, N)
print(poisson)
R3 = get_xi_ni_wi(poisson, N)
print(R3)
get_info(R3, N)
draw(R1, R2, R3, n, p)
