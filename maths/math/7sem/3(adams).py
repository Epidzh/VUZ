from matplotlib import pyplot
from numpy import arange
from math import log

h = 0.1
x = arange(1, 2, h)
func = lambda x, y: (y**2 + x*y) / x**2
K1 = lambda x, y: func(x, y)
K2 = lambda x, y, h: func(x + h/2, y + h*K1(x, y)/2)
K3 = lambda x, y, h: func(x + h/2, y + h*K2(x, y, h)/2)
K4 = lambda x, y, h: func(x + h, y + h*K3(x, y, h))
yk_plus_1 = 1
y = [yk_plus_1]
for index, i in enumerate(x[1:]):
	if index < 4:
		yk_plus_1 = yk_plus_1 + (h/6) * (K1(i, yk_plus_1) + 2*K2(i, yk_plus_1, h) + 2*K3(i, yk_plus_1, h) + K4(i, yk_plus_1, h))
	else:
		yk_plus_1 = yk_plus_1 + (h/24) * (55 * func(i, y[-1]) - 59*func(i, y[-2]) + 37*func(i, y[-3]) -9*func(i, y[-4]))
	y.append(yk_plus_1)
print("x: ", x)
print("y:", y)
pyplot.grid(True)
pyplot.plot(x, y, label="adams:0.1")

h = 0.01
x = arange(1, 2, h)
func = lambda x, y: (y**2 + x*y) / x**2
K1 = lambda x, y: func(x, y)
K2 = lambda x, y, h: func(x + h/2, y + h*K1(x, y)/2)
K3 = lambda x, y, h: func(x + h/2, y + h*K2(x, y, h)/2)
K4 = lambda x, y, h: func(x + h, y + h*K3(x, y, h))
yk_plus_1 = 1
y = [yk_plus_1]
for index, i in enumerate(x[1:]):
	if index < 4:
		yk_plus_1 = yk_plus_1 + (h/6) * (K1(i, yk_plus_1) + 2*K2(i, yk_plus_1, h) + 2*K3(i, yk_plus_1, h) + K4(i, yk_plus_1, h))
	else:
		yk_plus_1 = yk_plus_1 + (h/24) * (55 * func(i, y[-1]) - 59*func(i, y[-2]) + 37*func(i, y[-3]) -9*func(i, y[-4]))
	y.append(yk_plus_1)
print("x: ", x)
print("y:", y)
pyplot.grid(True)
pyplot.plot(x, y, label="adams:0.01")

pyplot.plot(x, [-i/(log(i) - 1) for i in x], label="answer")
pyplot.legend()
pyplot.show()