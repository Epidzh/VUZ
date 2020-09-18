import numpy as np
from numpy.linalg import matrix_power
from numpy import matmul
from math import fabs

variant = 53
matrix = np.array([[0.7, 0, 0.3], [0.135, 0.123, 0.742], [0.552, 0, 0.448]])

def convert_float(num):
    return "{:f}".format(float(num))

# 1 task
def getMatrixes1(matrix):
    ans = [matrix]
    deltas = []
    matrix_old = matrix
    delta = 0.00001
    delta_k = 0
    n = 1
    while delta_k > delta or n == 1:
        n += 1
        matrix_new = matrix_power(matrix, n)
        ans.append(np.array(matrix_new))
        for i in range(len(matrix)):
            delta_k = max([fabs(matrix_new[i][k] - matrix_old[i][k]) for k in range(len(matrix))])
        matrix_old = matrix_new
        deltas.append(delta_k)
    return [ans, n, deltas, ans[-1]]


matrixes, n, deltas, final_matrix = getMatrixes1(matrix)
print(n)
for i in matrixes:
    print(i)
    print()

print(deltas)

# 2 task

r = [46/71, 0, 25/71]

# 3 task

def getMatrixes3(matrix, vector, r):
    ans = [vector]
    n = 0
    delta = 0.00001
    delta_k = 0
    deltas = [max((1 - r[0]), r[1], r[2])]
    while delta_k > delta or n == 0:
        n += 1
        vector = matmul(vector, matrix)
        ans.append(list(vector))
        delta_k = max([fabs(vector[i] - r[i]) for i in range(3)])
        deltas.append(delta_k)
        print(ans)
    return [ans, n, deltas]


# (1, 0, 0)
vectors, m_min, deltas = getMatrixes3(matrix, [1, 0, 0], r)
print("100:")
print(vectors)
print(m_min)
print(deltas)
# (0, 1, 0)
vectors, m_min, deltas = getMatrixes3(matrix, [0, 1, 0], r)
print("010:")
print(vectors)
print(m_min)
print(list(map(convert_float, deltas)))
# print(vectors)
# print(getMatrixes3(matrix, [0, 1, 0], r))
# (0, 0, 1)
vectors, m_min, deltas = getMatrixes3(matrix, [0, 0, 1], r)
print("001:")
print(vectors)
print(m_min)
print(deltas)
# print(vectors)
# print(getMatrixes3(matrix, [0, 0, 1], r))
