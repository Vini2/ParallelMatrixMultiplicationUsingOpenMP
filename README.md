# Parallel Matrix Multiplication Using OpenMP
This project focuses on how to use “parallel for” and optimize a matrix-matrix multiplication to gain better performance. C++ and OpenMP library will be used.

This program contains three main components.

1) Serial Matrix-Matrix Multiplication
2) Parallel Matrix-Matrix Multiplication
3) Parallel Optimized Matrix-Matrix Multiplication

This repository contains 4 important files

1)	MatrixMultiplierFinal.cpp	-	C++ Source code for this program
2)	MatrixMultiplierFinal.exe	-	Executable file to directly run the program
3)	Lab 3 and 4.pdf				-	Includes details about this program. Lab details
4)	Concurrent Programming Lab3 4 - Graphs.xlsx 	-	Excel Sheet containing values related to execution and speedup (includes graphs)

## Instruction to Compile and Execute this program

### Step 1:

Open the command prompt or the terminal in the project folder. Windows users, make sure to have a C/C++ compiler like MinGW or TDM-GCC installed in the machine, and proper environment variables set.

### Step 2:

Run the following command in the terminal/ command prompt to compile the program (The compiled program executable is provided in the same folder as "MatrixMultiplierFinal.exe".).Make sure to link the openmp library by the comman "-fopenmp".

```g++ MatrixMultiplierFinal.cpp -o MatrixMultiplierFinal -fopenmp```

### Step 3:

Now, an executable file named "MatrixMultiplierFinal.exe" is created in the folder. Double click and open it. (Windows users). Or type MatrixMultiplierFinal.exe in the command prompt.

Linux users can use the terminal to run the executable file. By running the following command in the terminl
./MatrixMultiplierFinal

### Step 4:

Insert a letter according to you need. And then enter the sample size required. The letter representation is given below

1) s - serial
2) p - parallel
3) o - optimized

