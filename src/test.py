import group17 as g17
import numpy as np

mat = np.zeros((8, 8), int)
count = 0
while count < 30:
    count += 1
    print("count:", count)
    mat = g17.update_by_pc(mat)
    print(mat)
    mat *= -1
