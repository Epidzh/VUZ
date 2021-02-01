import numpy as np
import copy


A = [[-7.18, 3.17, 0, 0, 0, 0], [7.18, -10.35, 6.34, 0, 0, 0], [0, 7.18, -13.52, 9.51, 0, 0], [0, 0, 7.18, -16.69, 12.68, 0], [0, 0, 0, 7.18, -19.86, 15.85], [0, 0, 0, 0, 7.18, -23.03]]
tmp = copy.deepcopy(A)
tmp = np.transpose(copy.deepcopy(A))
tmp = np.append(tmp, [[1, 1, 1, 1, 1, 1]], axis=0)
print(tmp)
r = np.linalg.solve(tmp[1:], [0, 0, 0, 0, 0,1])
print(r)
print("sum: ", sum(r))
print(np.matmul(r, A))

A = [[-7.18, 3.17, 0, 0, 0], [7.18, -10.35, 6.34, 0, 0], [0, 7.18, -13.52, 9.51, 0], [0, 0, 7.18, -16.69, 12.68], [0, 0, 0, 7.18, -19.86]]
tmp = copy.deepcopy(A)
tmp = np.transpose(copy.deepcopy(A))
tmp = np.append(tmp, [[1, 1, 1, 1, 1]], axis=0)
print(tmp)
r = np.linalg.solve(tmp[1:], [0, 0, 0, 0, 1])
print(r)
print("sum: ", sum(r))
print(np.matmul(r, A))

A = [[-7.18, 3.17, 0, 0], [7.18, -10.35, 6.34, 0], [0, 7.18, -13.52, 9.51], [0, 0, 7.18, -16.69]]
tmp = copy.deepcopy(A)
tmp = np.transpose(copy.deepcopy(A))
tmp = np.append(tmp, [[1, 1, 1, 1]], axis=0)
print(tmp)
r = np.linalg.solve(tmp[1:], [0, 0, 0, 1])
print(r)
print("sum: ", sum(r))
print(np.matmul(r, A))