from matplotlib import pyplot
from numpy import arange
from math import fabs

print("Конечно-разностный метод решения краевой задачи для ОДУ второго порядка\n")

# метод прогонки (задача сдана в прошлом семестре)
def sweep(slau):

	def get_p(G, length):
	    p = [0 for i in range(length)]
	    p[0] = -(G[0][2] / G[0][1])
	    for i in range(1, length-1):
	        p[i] = -(G[i][2]) / (G[i][1] + G[i][0] * p[i-1])
	    return p


	def get_q(G, length):
	    p = get_p(G, length)
	    q = [0 for i in range(length)]
	    q[0] = G[0][3] / G[0][1]
	    for i in range(1, length):
	        q[i] = (G[i][3] - G[i][0] * q[i-1]) / (G[i][1] + G[i][0] * p[i-1])
	    return q


	def get_ans(slau):
	    G = {}
	    length = len(slau)
	    G[0] = (0, slau[0][0], slau[0][1], slau[0][2])
	    for i in range(1, length-1):
	        G[i] = (slau[i][0], slau[i][1], slau[i][2], slau[i][3])
	    G[length-1] = (slau[length-1][0], slau[length-1][1], 0, slau[length-1][2])
	    p = get_p(G, length)
	    q = get_q(G, length)
	    # print("Прогоночные коэффициенты P: ", p)
	    # print("Прогоночные коэффициенты Q: ", q)
	    y = [0 for i in range(length)]
	    y[-1] = q[-1]
	    for i in range(length-2, -1, -1):
	        from math import fabs
	        y[i] = p[i] * y[i+1] + q[i]
	        y[i] = 0 if fabs(y[i]) < 1E-10 else y[i]
	    return y

	return get_ans(slau)


# начальные условия
a = 0 # левый карй
b = 2 # правая край
N = 50 # количество вычисляемых точек
print("N =", N)
h = (b - a) / N # шаг
ya = 2 # начальное значение в левой точке
yb = 8 # начальное значение в правой точке

px = lambda x: -2*(x+2)/(x*(x+4)) # коэффициент p (после преобразования уравнения из варианта)
qx = lambda x: 2/(x*(x+4)) # коэффиицент q
A = [] # матрица коэффициентов

# заполнение трехдиагональной матрицы (согласно формулам, данным в методичке)
ans = []
for i in range(1, N+1):
	x = a + i*h
	if i == 1: # первая строка матрицы
		kf1 = (-2 + h**2 * qx(x))
		kf2 = (1 + (px(x)*h / 2))
		kf3 = -(1 - px(x)*h/2) * ya
		A.append([kf1, kf2, kf3])
	elif i == N: # последняя строка матрицы
		kf1 = 1 - px(x)*h/2
		kf2 = -2 + h**2 * qx(x)
		kf3 = -(1 + px(x)*h/2) * yb
		A.append([kf1, kf2, kf3])
		ans = sweep(A)
	else: # остальные строки матрицы
		kf1 = 1 - px(x)*h/2
		kf2 = -2 + h**2 * qx(x)
		kf3 = 1 + px(x)*h/2
		A.append([kf1, kf2, kf3, 0])

y = sweep(A) # решение системы методом прогонки
y.insert(0, ya) # вставка начального значения
x = arange(a, b+h, h) # список из точек x (для вывода графиков)

# печать полученных значений
print("Значения полученной функции:\n") 
print(["x={}, y={}".format(round(x[i[0]], 3), round(i[1], 5)) for i in enumerate(y)])
mx = max([fabs(i[1] - x[i[0]]**2 - x[i[0]] - 2) for i in enumerate(y)]) # максимальное отклонение от целевой функции
print("Максимальное отклонение от исходной функции: {}".format(mx)) 

# вывод графиков
pyplot.grid(True) # включение сетки
pyplot.plot(x, y, label="Полученная функция") # печать полученной в ходе решения функции
pyplot.plot(x, [i**2 + i + 2 for i in x], label="Целевая функция") # печать целевой функции (посчитано аналитическим способом)
pyplot.legend() # вывод подписей графиков
pyplot.show() # показ графиков