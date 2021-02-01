from math import exp, fabs
from numpy import arange
import matplotlib.pyplot as plot

# размер шага
h1, h2 = 0.1, 0.01


# исходная функция (вариант 3)
def func(x, y):
		return (y / x**2) + exp(x - 1 / x)

# результирующая функция
def funcOrigin(x):
	return (0.367879 * exp(1))*exp(-1/x) + exp(x - (1/x))

# метод эйлера (без пересчета)
def eiler():
	x1, x2 = arange(1, 2+h1, h1), arange(1, 2+h2, h2) # генерируем точки x
	y1, y2 = [1.367879], [1.367879] # первые значения приближений (при x = 1)

	# генерация точек согласно формулам (шаг 0.1)
	for point in x1[1:]:
		y1.append(y1[-1] + h1*func(point, y1[-1]))

	# генерация точек согласно формулам (шаг 0.01)
	for point in x2[1:]:
		y2.append(y2[-1] + h2*func(point, y2[-1])) 

	return [x1, y1, x2, y2]

# метод эйлера (с пересчетом)
def eiler2():
	x3, x4 = arange(1, 2+h1, h1), arange(1, 2+h2, h2) # генерируем точки x
	y3, y4 = [1.367879], [1.367879] # первые значения приближений (при x = 1)

	# генерация точек согласно формулам (шаг 0.1)
	for point_num in range(len(x3) - 1): 
		new_y = y3[-1] + h1*func(x3[point_num], y3[-1])
		y3.append(y3[-1] + (h1 / 2)* (func(x3[point_num], y3[-1]) + func(x3[point_num+1], new_y)))

	# генерация точек согласно формулам (шаг 0.01)
	for point in range(len(x4) - 1):
		new_y = y4[-1] + h2*func(x4[point], y4[-1])
		y4.append(y4[-1] + (h2 / 2)* (func(x4[point], y4[-1]) + func(x4[point+1], new_y)))

	return [x3, y3, x4, y4]

# вывод значений
print("Метод эйлера:")
x1, y1, x2, y2 = eiler()
print("Шаг h=0.1")
mx = 0
for index, item in enumerate(x1):
	mx = max(mx, round(fabs(y1[index] - funcOrigin(item)), 6))
print("Максимальное отклонение от исходной функции: {}".format(mx))

print("Шаг h=0.01")
mx = 0
for index, item in enumerate(x2):
	mx = max(mx, round(fabs(y2[index] - funcOrigin(item)), 6))
print("Максимальное отклонение от исходной функции: {}".format(mx))

print("\nМетод эйлера с пересчетом:")
x3, y3, x4, y4 = eiler2()
print("Шаг h=0.1")
mx = 0
for index, item in enumerate(x3):
	mx = max(mx, round(fabs(y3[index] - funcOrigin(item)), 6))
print("Максимальное отклонение от исходной функции: {}".format(mx))

print("Шаг h=0.01")
mx = 0
for index, item in enumerate(x4):
	mx = max(mx, round(fabs(y4[index] - funcOrigin(item)), 6))
print("Максимальное отклонение от исходной функции: {}".format(mx))

# вывод графиков
plot.grid(True)
plot.plot(x1, y1, color="#FF0000", label="Метод эйлера с шагом h=0.1")
plot.plot(x2, y2, color="#00FF00", label="Метод эйлера с шагом h=0.01")
plot.plot(x3, y3, color="#0000FF", label="Метод эйлера с пересчетом с шагом h=0.1")
plot.plot(x4, y4, color="#00FFFF", label="Метод эйлера с пересчетом с шагом h=0.01")
plot.plot(arange(1, 2, h2 / 100), [funcOrigin(t) for t in arange(1, 2, h2 / 100)], color="#000000", label="исходная функция")
plot.legend()
plot.show()