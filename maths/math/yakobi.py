from math import fabs, sqrt, sin, cos, atan
from numpy import copy


def is_continue(A, eps):
    return sqrt(sum([A[i][j]**2 for i in range(len(A)) for j in range(len(A[i])) if i < j])) > eps


def get_new_A(m_list):
    res = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    for i in range(len(m_list[0])):
        for j in range(len(m_list[0][0])):
            res[i][j] = m_list[0][i][j]
    for M in m_list[1:]:
        tmp = copy(res)
        for i in range(len(M)):
            for j in range(len(M[0])):
                g = [res[i][k]*M[k][j] for k in range(len(M))]
                s = sum([res[i][k]*M[k][j] for k in range(len(M))])
                tmp[i][j] = s
        res = tmp
    return res


eps = 0.01
print("Погрешность:", eps)
A = [
    [1, sqrt(2), 0],
    [sqrt(2), 1, sqrt(2)],
    [0, sqrt(2), 1]
]

A0 = A
# print(get_new_A([A, A, [[1, 0, 0], [0, 1, 0], [0, 0, 1]]]))
U = []
UT = []
U_list = []
while is_continue(A, eps):
    mx = None
    index = [0, 0]
    for i in range(len(A)):
        for j in range(len(A[i])):
            if i != j and (mx is None or fabs(A[i][j]) > mx):
                mx = fabs(A[i][j])
                index = [i, j]
    U = [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
    phi = 0.5 * atan(2*mx / (A[index[0]][index[0]] - A[index[1]][index[1]]))
    U[index[0]][index[1]] = -sin(phi)
    U[index[1]][index[0]] = sin(phi)
    U[index[0]][index[0]] = U[index[1]][index[1]] = cos(phi)
    # UT = [[i for i in U[:][0]], [i for i in U[:][1]], [i for i in U[:][2]]]
    UT = [[U[0][0], U[1][0], U[2][0]], [U[0][1], U[1][1], U[2][1]], [U[0][2], U[1][2], U[2][2]]]
    # for i in A:
    #     UT[0].append(i[0])
    #     UT[1].append(i[1])
    #     UT[2].append(i[2])
    A = get_new_A([UT, A, U])
    U_list.append(U)

    # print(mx)

print("\nСобственные значения: l1 = {}, l2 = {}, l3 = {}".format(A[0][0], A[1][1], A[2][2]))
v = get_new_A(U_list)
# print(v)
v1 = [i[0] for i in v]
v2 = [i[1] for i in v]
v3 = [i[2] for i in v]
print("\nПервый собственный вектор: ", v1)
print("Второй собственный вектор: ", v2)
print("Третий собственный вектор: ", v3)

print("\nA * v1 = ", [A0[i][0] * v1[0] + A0[i][1] * v1[1] + A0[i][2] * v1[2] for i in range(len(v1))])
print("A * v2 = ", [A0[i][0] * v2[0] + A0[i][1] * v2[1] + A0[i][2] * v2[2] for i in range(len(v2))])
print("A * v3 = ", [A0[i][0] * v3[0] + A0[i][1] * v3[1] + A0[i][2] * v3[2] for i in range(len(v3))])

# print("A*v = ")
# print(get_new_A([A0, v]))

print("\nl1 * v1 = ", [A[0][0] * v1[i] for i in range(len(v1))])
print("l2 * v2 = ", [A[1][1] * v2[i] for i in range(len(v2))])
print("l3 * v3 = ", [A[2][2] * v3[i] for i in range(len(v3))])

