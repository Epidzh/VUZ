from numpy import arange
from matplotlib import pyplot
# h1 = 0.1
# h2 = 0.01

# h = 0.1
# x = arange(1, 2, h)
# func = lambda x, y: -y/x - x**2
# K1 = lambda x, y: func(x, y)
# K2 = lambda x, y, h: func(x + h/3, y + h*K1(x, y)/3)
# K3 = lambda x, y, h: func(x + 2*h/3, y + 2*h*K2(x, y, h)/3)
# yk_plus_1 = 0.75
# y = [yk_plus_1]
# for i in x[1:]:
# 	yk_plus_1 = yk_plus_1 + (h/4) * (K1(i, yk_plus_1) + 3*K3(i, yk_plus_1, h))
# 	y.append(yk_plus_1)
# print("x: ", x)
# print("y:", y)
# pyplot.grid(True)
# pyplot.plot(x, y, label="3:0.1")

# h = 0.01
# x = arange(1, 2, h)
# func = lambda x, y: -y/x - x**2
# K1 = lambda x, y: func(x, y)
# K2 = lambda x, y, h: func(x + h/3, y + h*K1(x, y)/3)
# K3 = lambda x, y, h: func(x + 2*h/3, y + 2*h*K2(x, y, h)/3)
# yk_plus_1 = 0.75
# y = [yk_plus_1]
# for i in x[1:]:
# 	yk_plus_1 = yk_plus_1 + (h/4) * (K1(i, yk_plus_1) + 3*K3(i, yk_plus_1, h))
# 	y.append(yk_plus_1)
# print("x: ", x)
# print("y:", y)
# pyplot.grid(True)
# pyplot.plot(x, y, label="3:0.01")

h = 0.1
x = arange(1, 2, h)
func = lambda x, y: -y/x - x**2
K1 = lambda x, y: func(x, y)
K2 = lambda x, y, h: func(x + h/2, y + h*K1(x, y)/2)
K3 = lambda x, y, h: func(x + h/2, y + h*K2(x, y, h)/2)
K4 = lambda x, y, h: func(x + h, y + h*K3(x, y, h))
yk_plus_1 = 0.75
y = [yk_plus_1]
for i in x[1:]:
	yk_plus_1 = yk_plus_1 + (h/6) * (K1(i, yk_plus_1) + 2*K2(i, yk_plus_1, h) + 2*K3(i, yk_plus_1, h) + K4(i, yk_plus_1, h))
	y.append(yk_plus_1)
print("x: ", x)
print("y:", y)
pyplot.grid(True)
pyplot.plot(x, y, label="4:0.1")

h = 0.01
x = arange(1, 2, h)
func = lambda x, y: -y/x - x**2
K1 = lambda x, y: func(x, y)
K2 = lambda x, y, h: func(x + h/2, y + h*K1(x, y)/2)
K3 = lambda x, y, h: func(x + h/2, y + h*K2(x, y, h)/2)
K4 = lambda x, y, h: func(x + h, y + h*K3(x, y, h))
yk_plus_1 = 0.75
y = [yk_plus_1]
for i in x[1:]:
	yk_plus_1 = yk_plus_1 + (h/6) * (K1(i, yk_plus_1) + 2*K2(i, yk_plus_1, h) + 2*K3(i, yk_plus_1, h) + K4(i, yk_plus_1, h))
	y.append(yk_plus_1)
print("x: ", x)
print("y: ", y)
pyplot.grid(True)
pyplot.plot(x, y, label="4:0.01")

pyplot.plot(x, [(1 - 0.25*i**4)/i for i in x], label='answer')
pyplot.legend()
pyplot.show()