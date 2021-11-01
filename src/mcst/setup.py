from setuptools import setup, Extension

setup(
    ext_modules=[Extension('hello', ['hello.cpp'], ), ],
)