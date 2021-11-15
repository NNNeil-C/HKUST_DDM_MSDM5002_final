import ctypes
import glob

libfile = glob.glob('./build/*/mcst_helper*.so')[0]

print(libfile)

mylib = ctypes.CDLL(libfile)
print(mylib)

mylib.hello.restype = ctypes.c_void_p

mylib.hello()

INPUT = ctypes.c_int * 64
mylib.getNextPosition.argtype = [INPUT, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
mylib.getNextPosition.restype = ctypes.c_int
input = INPUT()
for i in range(64):
    input[i] = 0
getNextPosition = mylib.getNextPosition
ans = getNextPosition(input, -1, -1, 0, 60000)
print(ans)