slau = [
    [16, -9, -27],
    [8, -13, -5, -84],
    [-3, -21, 9, -225],
    [-9, 16, -5, -89],
    [1, -9, 69]
]


def get_p(G, length):
    p = [0 for i in range(length)]
    p[0] = -(G[0][2] / G[0][1])
    for i in range(1, length-1):
        p[i] = -(G[i][2]) / (G[i][1] + G[i][0] * p[i-1])
    return p


def get_q(G, length):
    p = get_p(G, length)
    q = [0 for i in range(length)]
    q[0] = G[0][3] / G[0][1]
    for i in range(1, length):
        q[i] = (G[i][3] - G[i][0] * q[i-1]) / (G[i][1] + G[i][0] * p[i-1])
    return q


def get_x(slau):
    G = {}
    length = len(slau)
    G[0] = (0, slau[0][0], slau[0][1], slau[0][2])
    for i in range(1, length-1):
        G[i] = (slau[i][0], slau[i][1], slau[i][2], slau[i][3])
    G[length-1] = (slau[length-1][0], slau[length-1][1], 0, slau[length-1][2])
    p = get_p(G, length)
    q = get_q(G, length)
    print("Прогоночные коэффициенты P: ", p)
    print("Прогоночные коэффициенты Q: ", q)
    x = [0 for i in range(length)]
    x[-1] = q[-1]
    for i in range(length-2, -1, -1):
        from math import fabs
        x[i] = p[i] * x[i+1] + q[i]
        x[i] = 0 if fabs(x[i]) < 1E-10 else x[i]
    return x


x = get_x(slau)
print("\nОтветы: ")
j = 1
for i in x:
    print("x{} = {}".format(j, i))
    j+=1
print("\nCHECK: ")
for i in range(len(slau)):
    if i == 0:
        print(x[0] * slau[i][0] + x[1]*slau[i][1])
    elif i == len(slau) - 1:
        print(x[i-1] * slau[i][0] + x[i] * slau[i][1])
    else:
        print(x[i-1] * slau[i][0] + x[i] * slau[i][1] + x[i+1] * slau[i][2])
