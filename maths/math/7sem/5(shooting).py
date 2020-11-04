from numpy import arange
from matplotlib import pyplot
from math import exp, fabs

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

pyplot.grid(True)
h = 0.01
x = arange(0+h, 1 + h, h)
func_z = lambda x1, y1, z1: ((2*x1 + 1)*z1 - 2*y1) / x1
n0 = 2
n = n0
aim = exp(2)
closest_value = fabs(runge(func_z, x, h, 1, n)[-1] - aim)
# print(closest_value)
closest_value_index = n
t = 0.1
while fabs(closest_value - aim) > 0.01:
	y1 = runge(func_z, x, h, 1, n)
	if fabs(y1[-1] - aim) < fabs(closest_value - aim):
		closest_value = y1[-1]
		closest_value_index = n
	if (y1[-1] > aim and t > 0) or (y1[-1] < aim and t < 0):
		t *= -1/2
	print("n={} ; Параметр корректировки : {} ; Погрешность : {}".format(n, t, fabs(y1[-1] - aim)))
	n += t


pyplot.plot(x, runge(func_z, x, h, 1, closest_value_index), label="n={}".format(round(closest_value_index, 4)))
print("Ответ: n={};  Погрешность: {}".format(closest_value_index, fabs(closest_value - aim)))
ans_y = [exp(2*i) for i in x]
pyplot.plot(x, ans_y, label="ans")
pyplot.legend()
pyplot.show()