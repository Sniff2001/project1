# FYS4150 Project 1

## Project Description
This program is made to solve Project 1 in FYS4150, autumn semester 2023.
It applies some OpenMP, although this only becomes relevant for higher `n_steps` chosen in the code. This is found in main.cpp.
## Compiling and running the code
The code is written in C++ and requires a C++ compiler to be compiled.
The following compilers have been tested to work:
- g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
- Visual Studio 2022 (compiler: Microsoft (R) C/C++ Optimizing Compiler Version 19.37.32822 for x64, OS: Windows 11 22621.2134)

The compiler for Visual Studio 2022 is the default one, although the exact version is given for reference.

The python code has similarly been tested to run in PyCharm with the following versions:
- Python 3.11.2
- Matplotlib 3.7.0
- NumPy 1.24.2
## Structure of code
The code is structured where each task (that are programmed in C++) act like modules that can be imported into any file and work. There is no dependency and one does not need to compile with all the files. The only exception to this is the main.cpp file, which uses the tasks to demonstrate their functionality.
To run one task, import one module and run the function `runTask#()` where `#` is replaced by the corresponding number the module is named after. However, this does not produce the plots, and one needs to use the python script included to make figures.

Optionally the git repository also includes the project files for Visual Studio 2022; open the .sln file in Visual Studio 2022 to load the project.