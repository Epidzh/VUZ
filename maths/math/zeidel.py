from math import fabs


def check(tmp, ans, eps):
    if len(tmp) == len(ans):
        for i in range(len(tmp)):
            if fabs(tmp[i] - ans[i]) > eps:
                return True
        return False
    else:
        return True

N = 4
eps = 0.01

a = [
    [10, 0, 2, 4],
    [2, 16, -3, 8],
    [1, 5, 11, -4],
    [8, 1, 6, -17]
]

b = [110, 128, 102, 81]

slau = []
for i in range(len(a)):
    slau.append([-a[i][j] / a[i][i] for j in range(len(a[i])) if j != i])
    slau[-1].insert(0, b[i] / a[i][i])
# print(slau)

ans = [slau[0][0] if i == 0 else 0 for i in range(len(slau))]
# print(ans)
prev = [0 for i in range(N)]
while check(prev, ans, eps):
    prev = ans.copy()
    for i in range(len(slau)):
        rez = slau[i][0]
        prev_index = 0
        for j in slau[i][1:]:
            if prev_index == i:
                prev_index += 1
            rez += j * prev[prev_index]
            prev_index += 1
        ans[i] = rez

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
print('Эталонные значения: ', b)