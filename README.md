# HKUST_DDM_MSDM5002_final
final Project(Gomoku) for HKUST MSDM 5002

## UML

![Gomoku](https://github.com/NNNeil-C/HKUST_DDM_MSDM5002_final/blob/main/Gomoku.png?raw=true)

## How to use the monte carlo c++ extension in python file
### step 1 : build .so file or .dll file
Generally, you should build the .so file(Unix) or .dll file(Windows) by yourself.
- run ./src/mcst/setup.py to build the .so files or .dll files
### step 2 : load the extension file using `ctype` package
- check the ./src/mcst/hello.py for help