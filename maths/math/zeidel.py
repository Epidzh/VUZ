from math import fabs, sqrt
import numpy as np


def check(tmp, ans, eps):
    if len(tmp) == len(ans):
        for i in range(len(tmp)):
            if fabs(tmp[i] - ans[i]) > eps:
                return True
        return False
    else:
        return True


# def zeidel(slau):
#     iterations = 0
#     ans = [slau[0][0] if i == 0 else 0 for i in range(len(slau))]
#     # print(ans)
#     prev = [0 for i in range(N)]
#     while check(prev, ans, eps):
#         iterations += 1
#         prev = ans.copy()
#         for i in range(len(slau)):
#             rez = slau[i][0]
#             prev_index = 0
#             for j in slau[i][1:]:
#                 if prev_index == i:
#                     prev_index += 1
#                 rez += j * prev[prev_index]
#                 prev_index += 1
#             ans[i] = rez
#     print("Количество итераций: ", iterations)
#     return ans

def seidel(A, b, eps):
    n = len(A)
    x = [.0 for i in range(n)]
    print("Начальное приближение: ", x)

    converge = False
    iterations = 0
    while not converge:
        iterations += 1
        x_new = np.copy(x)
        for i in range(n):
            s1 = sum(A[i][j] * x_new[j] for j in range(i))
            s2 = sum(A[i][j] * x[j] for j in range(i + 1, n))
            x_new[i] = (b[i] - s1 - s2) / A[i][i]

        converge = sqrt(sum((x_new[i] - x[i]) ** 2 for i in range(n))) <= eps
        x = x_new
        # print(x)

    print("Количество итераций: ", iterations)
    return x


def simple(slau, a, b):
    iterations = 0
    alpha = [[-a[i][j]/a[i][i] if i != j else 0 for j in range(len(a[i]))] for i in range(len(a))]
    beta = [b[i] / a[i][i] for i in range(len(b))]
    ans = [0 for i in beta]
    print("Начальное приближение: ", ans)
    prev = []
    while check(prev, ans, eps):
        iterations += 1
        prev = ans.copy()
        for i in range(len(alpha)):
            sm = 0
            for j in range(len(prev)):
                sm += alpha[i][j] * prev[j]
            sm += beta[i]
            ans[i] = sm
        # print(ans)
    print("Количество итераций: ", iterations)
    return ans


def print_ans(ans, a, b):
    results = []
    print("Ответы: ")
    for i in enumerate(ans):
        print("x{} = {}".format(i[0]+1, i[1]))

    print("\nПодстановка:")
    for i in enumerate(a):
        print("{}-ое уравнение ->".format(i[0]+1), end=' ')
        sm = 0
        for j in enumerate(i[1]):
            sm += j[1] * ans[j[0]]
            if j[0] == 0:
                print("{} * {}".format(j[1], ans[j[0]]), end=' ')
            else:
                if j[1] * ans[j[0]] < 0:
                    print(" - {} * {}".format(fabs(j[1]), fabs(ans[j[0]])), end=' ')
                else:
                    print(" + {} * {}".format(fabs(j[1]), fabs(ans[j[0]])), end=' ')
        print("= ", sm)
        results.append(sm)
    print("Погрешность результатов: ", [fabs(b[i] - results[i]) for i in range(len(b))])

N = 4
eps = 0.01
a = [
    [10, 0, 2, 4],
    [2, 16, -3, 8],
    [1, 5, 11, -4],
    [8, 1, 6, -17]
]

b = [110, 128, 102, 81]
print("Вариант - ", 4)
print("\nЗадаваемая точность: ", eps)
print('\nЭталонные значения: ', b)

slau = []
for i in range(len(a)):
    slau.append([-a[i][j] / a[i][i] for j in range(len(a[i])) if j != i])
    slau[-1].insert(0, b[i] / a[i][i])


print("\nМетод простой итерации: \n")
ans = simple(slau, a, b)
print_ans(ans, a, b)

print("\nМетод Зейделя: \n")
# ans = zeidel(slau)
ans = seidel(a, b, eps)
print_ans(ans, a, b)