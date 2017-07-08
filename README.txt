-------------------------------------------
Parallel Matrix Multiplication Using OpenMP
-------------------------------------------

This project focuses on how to use “parallel for” and optimize a matrix-matrix multiplication to gain better performance. C++ and OpenMP library will be used.

This program contains three main components.
    1. Serial Matrix-Matrix Multiplication
    2. Parallel Matrix-Matrix Multiplication
    3. Parallel Optimized Matrix-Matrix Multiplication


-----------------------------------------------
Instruction to Compile and Execute this program
-----------------------------------------------

Step 1:

Open the command prompt or the terminal in the project folder. Windows users, make sure to have a C/C++ compiler like MinGW or TDM-GCC installed in the machine, and proper environment variables set.


Step 2:

Run the following command in the terminal/ command prompt to compile the program. Make sure to link the openmp library by the command "- fopenmp".

g++ MatrixMultiplierFinal.cpp -o MatrixMultiplierFinal -fopenmp


Step 3:

Windws Users : Now, an executable file named "MatrixMultiplierFinal.exe" is created in the folder. Double click and open it Or type MatrixMultiplierFinal.exe in the command prompt.

Linux Users : Use the terminal to run the executable file. By running the following command in the terminal ./MatrixMultiplierFinal


Step 4:

Insert a letter according to your need. And then enter the sample size required. The letter representation is given below.
    s - serial
    p - parallel
    o - optimized

Eg:
First Enter "s" or "p" or "o"
Second Enter the sample size "200"

Program will run and print necessary details accordingly.
