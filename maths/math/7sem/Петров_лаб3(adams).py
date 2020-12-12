from matplotlib import pyplot
from numpy import arange
from math import log, fabs

print("Метод Адамса\n")

h = 0.1 # определение шага
x = arange(1, 2+h, h) # определение точек x
func = lambda x, y: (y**2 + x*y) / x**2 # определение данной функции (производная из варианта 3)

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
	mx = max(mx, fabs(yk_plus_1 + i/(log(i) - 1))) # поиск максимального отклонения
print("Максимальное отклонение от исходной функции (шаг 0.1): {}".format(mx)) 
pyplot.grid(True)
pyplot.plot(x, y, label="Метод Адамса с шагом 0.1") # результирующий график

h = 0.01 # определение шага
x = arange(1, 2+h, h) # определение точек x

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
	mx = max(mx, fabs(yk_plus_1 + i/(log(i) - 1))) # поиск максимального отклонения
print("Максимальное отклонение от исходной функции (шаг 0.01): {}".format(mx)) 
pyplot.grid(True)
pyplot.plot(x, y, label="Метод адамса с шагом 0.01") # результирующий график

# график исходной функции
pyplot.plot(x, [-i/(log(i) - 1) for i in x], label="Целевая функция")
pyplot.legend()
pyplot.show()