from math import fabs
koeffs = [
    [1, 4, -9, 7, -67],
    [2, -2, -2, 3, -57],
    [-1, 3, -9, -1, -26],
    [-5, 2, 2, 1, 52]
]
# koeffs = [
#     [-5, -6, 4, -2, 64],
#     [0, 3, -4, -6, -55],
#     [2, 4, -4, 2, -48],
#     [1, -8, 2, 8, 68]
# ]

def draw(arr):
    print("-------------------------------------")
    for i in arr:
        print(i)
    print("------------------------------------\n")


def first(arr):
    steps = len(arr) - 1
    main_elem = arr[0][0]
    for iteration in range(steps):
        mx = arr[iteration][iteration]
        k = iteration
        for j in range(iteration, len(arr)):
            print(arr[j][iteration])
            if fabs(arr[j][iteration]) > mx:
                mx = fabs(arr[j][iteration])
                k = j
        arr[iteration], arr[k] = arr[k], arr[iteration]
        
            
        main_elem = arr[iteration][iteration]
        print("!", main_elem)
        if iteration == 2:
            print("index = ", k, iteration)
        if main_elem == 0:
            draw(arr)
            continue
        for j in range(iteration + 1, len(arr)):
            dev = (-arr[j][iteration] / main_elem)
            for k in range(iteration, len(arr[j])):
                arr[j][k] += (arr[iteration][k] * dev)
        draw(arr)
    return arr


def second(matrix):
    ans = {i:1 for i in range(len(matrix) + 1)}
    ans[len(matrix)] = matrix[-1][-1] / matrix[-1][-2]
    t = 0
    for i in reversed(matrix[:-1]):
        sm = 0
        for k in range(len(i) - 2 - t, len(i) - 1):
            sm += i[k] * ans[k + 1]
        ans[len(matrix) - 1 - t] = (i[-1] - sm) / i [len(i) - 2 - t - 1]
        t += 1
    return ans

matrix = first(koeffs)
ans = second(koeffs)
ans.pop(0)
for i, j in ans.items():
    print("x{} = {}".format(i, j))