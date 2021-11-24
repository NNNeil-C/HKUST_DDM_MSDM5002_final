import ctypes
import glob
import platform

# sample for using C++ extension
# specify the .so file path yourself
so_file_path = ""
if "Win" in platform.platform():
    so_file_path = r'./build/lib.windows-10-x64-3.7/mcst_helper*.dll'
else:
    so_file_path = r'./mcst_helper.so'
print(so_file_path)
# it will print "hello" and the current time
libfile = glob.glob(so_file_path)[0]
mylib = ctypes.CDLL(libfile)
mylib.hello.restype = ctypes.c_void_p
mylib.hello()

# sample for using C++ extension
# first we create a game board(8*8)
INPUT = ctypes.c_int * 64
# define the function arguments type
mylib.getNextPosition.argtype = [INPUT, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
# define the function return type
mylib.getNextPosition.restype = ctypes.c_int
# now, we are setting the game board value(-1 for black, 0 for empty, 1 for white)
input = INPUT()
for i in range(64):
    input[i] = 0
# now, we are ready to call the C++ extension function
getNextPosition = mylib.getNextPosition
# pass the input(game board), last drop x, last drop y, last drop piece and time limit to the function
# the getNextPosition in C++ looks like below
# int getNextPosition(const int input[], const int last_x, const int last_y, const int last_piece, const int time_limit)
ans = getNextPosition(input, -1, -1, 0, 5000)
# finally, we got a (x, y) to place next piece
x = ans // 10
y = ans % 10
print(x, y)