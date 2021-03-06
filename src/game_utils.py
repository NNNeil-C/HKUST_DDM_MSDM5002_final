# -*- coding: utf-8 -*-
# @Time    : 27/11/2021 4:03 pm
# @Author  : ZIFENG NEIL CHEN
# @FileName: game_utils.py
# @Software: PyCharm
# @Github    ：https://github.com/NNNeil-C/
import ctypes
import glob
import numpy as np

game_board_size = 8
mylib = None

def get_click_position(event):
    x, y = event.pos
    row = round((x - 25) / 50)
    col = round((y - 25) / 50)
    return col, row


def is_valid_position(board, col, row):
    if col < 0 or col >= game_board_size or row < 0 or row >= game_board_size:
        return False
    if board[row, col] != 0:
        return False
    return True


def load_dynamic_lib(so_file_path):
    libfile = glob.glob(so_file_path)[0]
    global mylib
    mylib = ctypes.CDLL(libfile)
    mylib.hello.restype = ctypes.c_void_p
    mylib.hello()

    INPUT = ctypes.c_int * 64
    mylib.getNextPosition.argtype = [INPUT, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
    mylib.getNextPosition.restype = ctypes.c_int

    mylib.check_win_cpp.argtype = [INPUT, ctypes.c_int, ctypes.c_int]
    mylib.check_win_cpp.restype = ctypes.c_bool


def ask_monte_carlo_search_tree(board, last_x, last_y, last_piece_type, time_limit=5000):
    global mylib
    INPUT = ctypes.c_int * 64
    input = INPUT()
    for i in range(64):
        input[i] = 0
    for i in range(game_board_size):
        for j in range(game_board_size):
            input[i * game_board_size + j] = board[i, j]
    getNextPosition = mylib.getNextPosition
    ans = getNextPosition(input, last_x, last_y, int(last_piece_type), time_limit)
    x = ans // 10
    y = ans % 10
    return x, y


def check_win_cpp(board, last_x, last_y):
    global mylib
    INPUT = ctypes.c_int * 64
    input = INPUT()
    for i in range(64):
        input[i] = 0
    for i in range(game_board_size):
        for j in range(game_board_size):
            input[i * game_board_size + j] = board[i, j]
    return mylib.check_win_cpp(input, last_x, last_y)
