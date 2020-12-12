from numpy import arange
from matplotlib import pyplot
from math import fabs

print("Метод Рунге-Кутты:\n")

h = 0.1 # определение шага
x = arange(1, 2+h, h) # определение точек x
func = lambda x, y: -y/x - x**2 # определение данной функции (производная из варианта 3)

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
	mx = max(mx, fabs(yk_plus_1 - (1 - 0.25*i**4)/i)) # поиск максимального отклонения
print("Максимальное отклонение от исходной функции (шаг 0.1): {}".format(mx)) 
pyplot.grid(True)
pyplot.plot(x, y, label="Метод Рунге-Кутты 4 порядка с шагом 0.1") # результирующий график


h = 0.01 # определение шага
x = arange(1, 2+h, h) # определение точек x
func = lambda x, y: -y/x - x**2 # определение данной функции (производная из варианта 3)

# определение коэффициентов K
K1 = lambda x, y: func(x, y)
K2 = lambda x, y, h: func(x + h/2, y + h*K1(x, y)/2)
K3 = lambda x, y, h: func(x + h/2, y + h*K2(x, y, h)/2)
K4 = lambda x, y, h: func(x + h, y + h*K3(x, y, h))

yk_plus_1 = 0.75# начальное значение
y = [yk_plus_1] # список с значениями y
mx = 0 # переменная для поиска отклонения

# рассчет согласно формулам
for i in x[1:]:
	yk_plus_1 = yk_plus_1 + (h/6) * (K1(i, yk_plus_1) + 2*K2(i, yk_plus_1, h) + 2*K3(i, yk_plus_1, h) + K4(i, yk_plus_1, h))
	y.append(yk_plus_1)
	mx = max(mx, fabs(yk_plus_1 - (1 - 0.25*i**4)/i)) # поиск максимального отклонения
print("Максимальное отклонение от исходной функции (шаг 0.01): {}".format(mx)) 
pyplot.grid(True)
pyplot.plot(x, y, label="Метод Рунге-Кутты 4 порядка с шагом 0.01") # результирующий график

# график исходной функции
pyplot.plot(x, [(1 - 0.25*i**4)/i for i in x], label='Целевая функция')
pyplot.legend()
pyplot.show()