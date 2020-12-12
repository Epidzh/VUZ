from matplotlib import pyplot
from numpy import arange
from math import pi, sin, cos, fabs

print("Решение задачи Коши для ОДУ второго или более высокого порядков\n")

h = 0.1 # определение шага
z_func = lambda x, y, z: (2*x*z - (x**2 + 2)*y) / x**2 # заданная функция с новой переменной (производная 2 порядка, 3 вариант)
func = lambda x, y, z: z # введение новой переменной

# определение коэффициентов K и L
K1 = lambda x, y, z, h: h*func(x, y, z)
L1 = lambda x, y, z, h: h*z_func(x, y, z)

K2 = lambda x, y, z, h: h*func(x + h/2, y + K1(x, y, z, h)/2, z + L1(x, y, z, h)/2)
L2 = lambda x, y, z, h: h*z_func(x + h/2, y + K1(x, y, z, h)/2, z + L1(x, y, z, h)/2)

K3 = lambda x, y, z, h: h*func(x + h/2, y + h*K2(x, y, z, h)/2, z + L2(x, y, z, h)/2)
L3 = lambda x, y, z, h: h*z_func(x + h/2, y + h*K2(x, y, z, h)/2, z + L2(x, y, z, h)/2)

K4 = lambda x, y, z, h: h*func(x + h, y + h*K3(x, y, z, h), z + L3(x, y, z, h))
L4 = lambda x, y, z, h: h*z_func(x + h, y + h*K3(x, y, z, h), z + L3(x, y, z, h))



def calculate(h):
	x = arange(pi/2, (pi/2) + 1+h, h)
	yk_plus_1 = pi / 2 # начальное значение y
	zk_plus_1 = 1 - (pi / 2) # начальное значение z
	y = []
	z = []
	mx = 0

	# рассчет согласно формулам
	for index, i in enumerate(x):
		t = yk_plus_1 + (1/6) * (K1(i, yk_plus_1, zk_plus_1, h) + 2*K2(i, yk_plus_1, zk_plus_1, h) + 2*K3(i, yk_plus_1, zk_plus_1, h) + K4(i, yk_plus_1, zk_plus_1, h))
		zk_plus_1 = zk_plus_1 + (1/6) * (L1(i, yk_plus_1, zk_plus_1, h) + 2*L2(i, yk_plus_1, zk_plus_1, h) + 2*L3(i, yk_plus_1, zk_plus_1, h) + L4(i, yk_plus_1, zk_plus_1, h))
		yk_plus_1 = t
		y.append(yk_plus_1)
		z.append(zk_plus_1)
		mx = max(mx, fabs(yk_plus_1 - i*(cos(i) + sin(i)))) # поиск максимального отклонения

	# Вывод программы и график
	print("Максимальное отклонение от исходной функции (шаг {}): {}".format(h,mx)) 
	pyplot.grid(True)
	pyplot.plot(x, y, label="Решение задачи Коши, h={}".format(h))

# Вызовы рассчетной функции
calculate(0.1)
calculate(0.01)

# График исходной функции
x = arange(pi/2, (pi/2) + 1+0.01, 0.01)
y = [i*(cos(i) + sin(i)) for i in x]
pyplot.plot(x, y, label='Целевая функция')
pyplot.legend()
pyplot.show()