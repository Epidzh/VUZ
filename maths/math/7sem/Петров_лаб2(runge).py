from numpy import arange
from matplotlib import pyplot
from math import fabs

print("Метод Рунге-Кутты:\n")

left, right = 1, 2
func = lambda x, y: -y/x - x**2 # определение данной функции (производная из варианта 3)
originFunc = lambda x: (1 - 0.25*x**4)/x # точное решение

def runge(h):
	x = arange(left, right+h, h) # определение точек x
	# определение коэффициентов K
	K1 = lambda x, y: func(x, y)
	K2 = lambda x, y, h: func(x + h/2, y + h*K1(x, y)/2)
	K3 = lambda x, y, h: func(x + h/2, y + h*K2(x, y, h)/2)
	K4 = lambda x, y, h: func(x + h, y + h*K3(x, y, h))

	yk_plus_1 = 0.75 # начальное значение
	y = [yk_plus_1] # список с значениями y
	mx = 0 # переменная для поиска отклонения

	# рассчет согласно формулам
	for i in x[1:]:
		yk_plus_1 = yk_plus_1 + (h/6) * (K1(i, yk_plus_1) + 2*K2(i, yk_plus_1, h) + 2*K3(i, yk_plus_1, h) + K4(i, yk_plus_1, h))
		y.append(yk_plus_1) # добавление значения
		mx = max(mx, fabs(yk_plus_1 - originFunc(i))) # поиск максимального отклонения
	print("Максимальное отклонение от исходной функции (шаг {}): {}".format(h, mx)) 
	pyplot.grid(True)
	pyplot.plot(x, y, label="Метод Рунге-Кутты 4 порядка с шагом {}".format(h)) # результирующий график

runge(0.1)
runge(0.01)

# график исходной функции
x = arange(left, right+0.01, 0.01) # определение точек x
pyplot.plot(x, [originFunc(i) for i in x], label='Точное решение')
pyplot.legend()
pyplot.show()