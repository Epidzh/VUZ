from numpy import arange
from matplotlib import pyplot
from math import exp, fabs

print("Метод стрельбы, Вариант3:")

# Решение задачи Коши (из лабораторной №4)
def runge(z_func, x, h, yk = 1, zk = 2):
	func = lambda x, y, z: z

	K1 = lambda x, y, z, h: h*func(x, y, z)
	L1 = lambda x, y, z, h: h*z_func(x, y, z)

	K2 = lambda x, y, z, h: h*func(x + h/2, y + K1(x, y, z, h)/2, z + L1(x, y, z, h)/2)
	L2 = lambda x, y, z, h: h*z_func(x + h/2, y + K1(x, y, z, h)/2, z + L1(x, y, z, h)/2)

	K3 = lambda x, y, z, h: h*func(x + h/2, y + h*K2(x, y, z, h)/2, z + L2(x, y, z, h)/2)
	L3 = lambda x, y, z, h: h*z_func(x + h/2, y + h*K2(x, y, z, h)/2, z + L2(x, y, z, h)/2)

	K4 = lambda x, y, z, h: h*func(x + h, y + h*K3(x, y, z, h), z + L3(x, y, z, h))
	L4 = lambda x, y, z, h: h*z_func(x + h, y + h*K3(x, y, z, h), z + L3(x, y, z, h))

	yk_plus_1 = yk
	zk_plus_1 = zk
	y = []
	z = []
	for index, i in enumerate(x):
		t = yk_plus_1 + (1/6) * (K1(i, yk_plus_1, zk_plus_1, h) + 2*K2(i, yk_plus_1, zk_plus_1, h) + 2*K3(i, yk_plus_1, zk_plus_1, h) + K4(i, yk_plus_1, zk_plus_1, h))
		zk_plus_1 = zk_plus_1 + (1/6) * (L1(i, yk_plus_1, zk_plus_1, h) + 2*L2(i, yk_plus_1, zk_plus_1, h) + 2*L3(i, yk_plus_1, zk_plus_1, h) + L4(i, yk_plus_1, zk_plus_1, h))
		yk_plus_1 = t
		y.append(yk_plus_1)
		z.append(zk_plus_1)
	return y


h = 0.025 # Задаем точность (взял не слишком маленькое значение, чтобы графики были хорошо видны, а не сливались в один (вернее, были бы слишком близки друг к другу))
x = arange(0+h, 1 + h, h) # Задаем точки x
func_z = lambda x1, y1, z1: ((2*x1 + 1)*z1 - 2*y1) / x1 # Заданная функция (из варианта, выражена y'')
n0 = 2 # Значение y'(0)
n = n0 # Значение тангенса угла касательной (по условию)
aim = exp(2) # Значение y(1) - цель для приближения
closest_value = fabs(runge(func_z, x, h, 1, n)[-1] - aim) # Ближайшее значение на конце (будем оптимизировать в ходе решения)
closest_value_index = n # Индекс ближашего значения
t = 0.1 # Параметр, с помощью которого будем приближать функцию (в ходе решения будет уменьшаться и менять знак) - назовем "параметром корректировки"

print("Ход решения (n - значение тангенса угла касательной): \n")
iter_num = 0
while fabs(closest_value - aim) > h: # Пока на конце точность больше h=0.01
	iter_num += 1
	y1 = runge(func_z, x, h, 1, n) # Считаем значения y для точек x
	if fabs(y1[-1] - aim) < fabs(closest_value - aim): # Обновляем значения и индекс ближайшей точки, если результат улучшился
		closest_value = y1[-1]
		closest_value_index = n
	# Если функция отклонилась по знаку (например, в прошлый раз точка на конце была выше цели, а теперь ниже или наоборот), то меняем параметр корректировки
	if (y1[-1] > aim and t > 0) or (y1[-1] < aim and t < 0):
		t *= -1/2
	print("Итерация №{}: n={} ; Параметр корректировки : {} ; Погрешность : {}".format(iter_num, n, t, fabs(y1[-1] - aim)))
	n += t # Меняем значение тангенса угла касательной
print("\nОтвет: n={};  Погрешность: {}".format(closest_value_index, fabs(closest_value - aim)))

# Рисуем графики целевой и полученной функций (параметр корректировки округлим до 4 знака для удобства отображения)
pyplot.grid(True)
pyplot.plot(x, runge(func_z, x, h, 1, closest_value_index), label="Метод стрельбы, n={}".format(round(closest_value_index, 4)))
ans_y = [exp(2*i) for i in x] # Целевая функция - e в степени 2х
pyplot.plot(x, ans_y, label="Целевая функция")
pyplot.legend()
pyplot.show()