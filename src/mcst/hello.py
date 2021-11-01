import ctypes
import numpy as np
import glob

libfile = glob.glob('./build/*/hello*.so')[0]

print(libfile)

mylib = ctypes.CDLL(libfile)
print(mylib)

mylib.hello.restype = ctypes.c_void_p

mylib.hello()