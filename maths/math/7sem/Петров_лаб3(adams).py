from matplotlib import pyplot
from numpy import arange
from math import log, fabs

print("Метод Адамса\n")
left, right = 1, 2
func = lambda x, y: (y**2 + x*y) / x**2 # определение данной функции (производная из варианта 3)
originFunc = lambda x: -x/(log(x) - 1) # точное решение

def adams(h):
	x = arange(left, right+h, h) # определение точек x
	# определение коэффициентов K
	K1 = lambda x, y: func(x, y)
	K2 = lambda x, y, h: func(x + h/2, y + h*K1(x, y)/2)
	K3 = lambda x, y, h: func(x + h/2, y + h*K2(x, y, h)/2)
	K4 = lambda x, y, h: func(x + h, y + h*K3(x, y, h))

	yk_plus_1 = 1 # начальное значение
	y = [yk_plus_1] # список с значениями y
	mx = 0 # переменная для поиска отклонения

	# рассчет согласно формулам (первые 3 рассчитываются методом Рунге-Кутты 4 порядка)
	for index, i in enumerate(x[1:]):
		if index < 4:
			yk_plus_1 = yk_plus_1 + (h/6) * (K1(i, yk_plus_1) + 2*K2(i, yk_plus_1, h) + 2*K3(i, yk_plus_1, h) + K4(i, yk_plus_1, h))
		else:
			yk_plus_1 = yk_plus_1 + (h/24) * (55 * func(i, y[-1]) - 59*func(i, y[-2]) + 37*func(i, y[-3]) -9*func(i, y[-4]))
		y.append(yk_plus_1)
		mx = max(mx, fabs(yk_plus_1 - originFunc(i))) # поиск максимального отклонения
	print("Максимальное отклонение от исходной функции (шаг {}: {}".format(h, mx)) 
	pyplot.grid(True)
	pyplot.plot(x, y, label="Метод Адамса с шагом {}".format(h)) # результирующий график

adams(0.1)
adams(0.01)

# график исходной функции
x = arange(left, right+0.01, 0.01) # определение точек x
pyplot.plot(x, [originFunc(i) for i in x], label="Целевая функция")
pyplot.legend()
pyplot.show()