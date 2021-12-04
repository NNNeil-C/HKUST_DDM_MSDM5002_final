# HKUST_DDM_MSDM5002_final
final Project(Gomoku) for HKUST MSDM 5002

## How to play
- A demo.ipynb file is under the sir directory, it can run on MacOS and windows(x64). 
- Or you just run the game.py under the src directory
  - run "python game.py" if you want to play at first.
  - run "python game.py second" if you want to play at second.
- Enjoy it. ^_^

## UML

![Gomoku](https://github.com/NNNeil-C/HKUST_DDM_MSDM5002_final/blob/main/Gomoku.png?raw=true)

## How to use the monte carlo c++ extension in python file
### step 1 : build .so file or .dll file
Generally, you should build the .so file(Unix) or .dll file(Windows) by yourself.
- For Unix, run ./src/mcst/setup.py to build the .so files 
- For Windows, build .dll files with Visual Studio.
### step 2 : load the extension file using `ctype` package
- check the ./src/mcst/hello.py for help
