import numpy as np
from numpy.linalg import matrix_power
from math import fabs

variant = 53
matrix = np.array([[0.7, 0, 0.3], [0.135, 0.123, 0.742], [0.552, 0, 0.448]])

# 1 task
def getMatrixes(matrix):
    ans = [matrix]
    matrix_old = matrix
    delta = 0.00001
    delta_k = 0
    n = 1
    while delta_k > delta or n == 1:
        n += 1
        matrix_new = matrix_power(matrix, n)
        ans.append(matrix_new)
        for i in range(len(matrix)):
            delta_k = max([fabs(matrix_new[i][k] - matrix_old[i][k]) for k in range(len(matrix))])
        matrix_old = matrix_new
    print(delta_k)
    return [ans, n]


matrixes, n = getMatrixes(matrix)
print(n)
for i in matrixes:
    print(i)
    print()

# 2 task