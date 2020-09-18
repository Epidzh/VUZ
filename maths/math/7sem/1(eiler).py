from math import exp
from numpy import arange
import matplotlib.pyplot as plot


h1, h2 = 0.1, 0.01

def func(x, y):
		return (y / x**2) + exp(x - 1 / x)


def eiler():
	x1, x2 = arange(1, 2, h1), arange(1, 2, h2)
	y1, y2 = [1.367879], [1.367879]
	for point in x1[1:]:
		y1.append(y1[-1] + h1*func(point, y1[-1]))

	for point in x2[1:]:
		y2.append(y2[-1] + h2*func(point, y2[-1]))

	return [x1, y1, x2, y2]


def eiler2():
	x3, x4 = arange(1, 2, h1), arange(1, 2, h2)
	y3, y4 = [1.367879], [1.367879]

	for point_num in range(len(x3) - 1):
		new_y = y3[-1] + h1*func(x3[point_num], y3[-1])
		y3.append(y3[-1] + (h1 / 2)* (func(x3[point_num], y3[-1]) + func(x3[point_num+1], new_y)))

	for point in range(len(x4) - 1):
		new_y = y4[-1] + h2*func(x4[point_num], y4[-1])
		y4.append(y4[-1] + (h2 / 2)* (func(x4[point_num], y4[-1]) + func(x4[point_num+1], new_y)))

	return [x3, y3, x4, y4]


x1, y1, x2, y2 = eiler()
x3, y3, x4, y4 = eiler2()

plot.grid(True)
plot.plot(x1, y1, color="#FF0000", label="first h=0.1")
plot.plot(x2, y2, color="#00FF00", label="first h=0.01")
plot.plot(x3, y3, color="#0000FF", label="second h=0.1")
plot.plot(x4, y4, color="#00FFFF", label="second h=0.01")
plot.legend()
plot.show()