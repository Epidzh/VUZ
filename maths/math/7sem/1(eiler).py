from math import exp
from numpy import arange
import matplotlib.pyplot as plot


h1, h2 = 0.1, 0.01

def func(x, y):
		return (y / x**2) + exp(x - 1 / x)


def funcOrigin(x):
	return (0.367879 * exp(1))*exp(-1/x) + exp(x - (1/x))


def eiler():
	x1, x2, test_x = arange(1, 2, h1), arange(1, 2, h2), arange(1, 2, 0.2)
	y1, y2, test_y = [1.367879], [1.367879], [1.367879]
	for point in x1[1:]:
		y1.append(y1[-1] + h1*func(point, y1[-1]))

	for point in x2[1:]:
		y2.append(y2[-1] + h2*func(point, y2[-1]))

	for point in test_x[1:]:
		test_y.append(test_y[-1] + 0.2*func(point, test_y[-1]))

	return [x1, y1, x2, y2, test_x, test_y]


def eiler2():
	x3, x4, test_x = arange(1, 2, h1), arange(1, 2, h2), arange(1, 2, 0.2)
	y3, y4, test_y = [1.367879], [1.367879], [1.367879]

	for point_num in range(len(x3) - 1):
		new_y = y3[-1] + h1*func(x3[point_num], y3[-1])
		y3.append(y3[-1] + (h1 / 2)* (func(x3[point_num], y3[-1]) + func(x3[point_num+1], new_y)))

	for point in range(len(x4) - 1):
		new_y = y4[-1] + h2*func(x4[point], y4[-1])
		y4.append(y4[-1] + (h2 / 2)* (func(x4[point], y4[-1]) + func(x4[point+1], new_y)))

	for point in range(len(test_x) - 1):
		new_y = test_y[-1] + 0.2*func(test_x[point], test_y[-1])
		test_y.append(test_y[-1] + (0.2 / 2) * (func(test_x[point], test_y[-1]) + func(test_x[point+1], new_y)))

	return [x3, y3, x4, y4, test_x, test_y]


x1, y1, x2, y2, test_x1, test_y1 = eiler()
print("h=0.1")
for index, item in enumerate(x1):
	print("x={} : {}".format(item, y1[index]))

print("h=0.2")
for index, item in enumerate(test_x1):
	print("x={} : {}".format(item, test_y1[index]))

print("\nh=0.01")
for index, item in enumerate(x2):
	print("x={} : {}".format(item, y2[index]))

x3, y3, x4, y4, test_x2, test_y2 = eiler2()
print("\nh=0.1")
for index, item in enumerate(x3):
	print("x={} : {}".format(item, y3[index]))
print("\nh=0.2")
for index, item in enumerate(test_x2):
	print("x={} : {}".format(item, test_y2[index]))
print("\nh=0.01")
for index, item in enumerate(x4):
	print("x={} : {}".format(item, y4[index]))

plot.grid(True)
plot.plot(x1, y1, color="#FF0000", label="eiler h=0.1")
plot.plot(test_x1, test_y1, color="#FFFF00", label="eiler h=0.2")
plot.plot(x2, y2, color="#00FF00", label="eiler h=0.01")
plot.plot(x3, y3, color="#0000FF", label="eiler2 h=0.1")
plot.plot(test_x2, test_y2, color="#FF00FF", label="eiler2 h=0.2")
plot.plot(x4, y4, color="#00FFFF", label="eiler2 h=0.01")
plot.plot(arange(1, 2, h2 / 100), [funcOrigin(t) for t in arange(1, 2, h2 / 100)], color="#000000", label="origin")
plot.legend()
plot.show()