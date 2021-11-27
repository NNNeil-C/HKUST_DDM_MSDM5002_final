import numpy as np


class gameboard:
    number_of_columns = 8
    number_of_rows = 8
    none = 0
    board = np.zeros((number_of_rows, number_of_columns), dtype=np.int64)
