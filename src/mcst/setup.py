from setuptools import setup, Extension

setup(
    ext_modules=[Extension('mcst_helper',
                           sources=['mcst_helper.cpp'],
                           language="c++",
                           include_dirs=[
                               "exceptions",
                               "includes"
                           ],
                           extra_compile_args=['-std=c++11']
                           )
                 ],
)