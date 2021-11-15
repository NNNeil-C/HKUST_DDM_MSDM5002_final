import ctypes
import glob

# sample for using C++ extension
# it will print "hello" and the current time
libfile = glob.glob('./build/*/mcst_helper*.so')[0]
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
ans = getNextPosition(input, -1, -1, 0, 5000)
# finally, we got a (x, y) to place next piece
x = ans // 10
y = ans % 10
print(x, y)
