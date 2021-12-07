import glob
import ctypes
import numpy as np
import platform
import time

game_board_size = 8
mylib = None
last_x = -1
last_y = -1
last_piece_type = 0
last_board = np.zeros((game_board_size, game_board_size))

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
    so_file_path = r"./mcst/build/lib.macosx-11.0-arm64-3.8/mcst_helper.cpython-38-darwin.so"
    if 'Windows' in platform.platform():
        so_file_path = r".\mcst\build\lib.windows*\mcst_helper.dll"
    if mylib == None:
        load_dynamic_lib(so_file_path)
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


def update_by_pc(mat):
    print("="*50)
    print("start update_by_pc")
    start = time.time()
    x, y = ask_monte_carlo_search_tree(mat, -1, -1, -1, time_limit=4900)
    mat[x, y] = 1
    print("end update_by_pc, time cost is: {0:.3f}s".format(time.time() - start))
    print('='*50)
    return mat