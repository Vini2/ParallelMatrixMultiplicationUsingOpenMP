#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#define THREADS 20

using namespace std;

//default sample size is 1, unless the user specifies a value
int SAMPLES = 1;

//MatrixA and MatrixB will  be the input Matrices - maximum size 2000
double matrixA[2000][2000];
double matrixB[2000][2000];
double transposeB[2000][2000];


//this matrix will be the multiplication of Matrix A and B
double matrixC[2000][2000];

//method header initialization
int min(int a, int b);
void transpose(int n);
void populate_matrix(int n);
double serial_multiplication(int n);
double parallel_for_multiplication(int n);
double parallel_for_multiplication_optimized(int n);

//these methods will run the tasks according to the given excersice "Lab 3 and 4.pdf"
void step4_1();
void step4_2();
void step8();

/*
This is the main method of the program
*/
int main() {

	char method;

	//Enter method that needs to be run
	printf("Enter one of the options given below\n \ts - for serial program \n\tp - for parallel program \n\to - for optimized program\n");
	scanf("%c", &method);

	//Enter sample size for the above selected method
	printf("Enter sample size: ");
	scanf("%d", &SAMPLES);

	switch (method) {
		case 's':
			step4_1();
			break;

		case 'p':
			step4_2();
			break;

		case 'o':
			step8();
			break;
			
	}
	
	return 0;


}

/*
This method will return the minimum out of two numbers (integers)
*/
int min(int a, int b){
	return a < b ? a : b;
}

/*
This method will get the transpose of matrixB
*/
void transpose(int n) {
    int i,j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            transposeB[i][j] = matrixB[j][i];
        }
    }
}


/*
This method will populate the matrix with random numbers
*/
void populate_matrix(int n){

	//different seed for each experiment
	srand(time(NULL));

	//populate matrices
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			matrixA[i][j] = rand();
			matrixB[i][j] = rand();

		}
	}

}

/*
This methid will do serial multiplication
*/
double serial_multiplication(int n){

	//required variable initilization
	int i, j, k;

	//start time from the wall clock
	double startTime = omp_get_wtime();

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			matrixC[i][j] = 0;
			for (k = 0; k < n; k++){
				matrixC[i][j] = matrixC[i][j] + matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	//get the end time from the wall clock
	double endTime = omp_get_wtime();

	//return the execution time
	return endTime - startTime;
}

/*
This method will do parallel for loop multiplication
*/
double parallel_for_multiplication(int n){
		
	//start time from the wall clock
	double startTime = omp_get_wtime();

	//for loop spefication with shared, private variables and number of threads
	#pragma omp parallel for shared(matrixA,  matrixB, matrixC) schedule(static) num_threads(THREADS)
	for (int i = 0; i < n ; i++ ){
		
		for (int j = 0; j < n ; j++ ){
			matrixC[i][j] = 0;
			for (int k = 0; k < n ; k++ ){
				matrixC[i][j] = matrixC[i][j] + matrixA[i][k]*matrixB[k][j];
				
			}
		
		}
		
	}

	//get the end time from wall clock
	double endTime = omp_get_wtime();

	//return the execution time
	return endTime - startTime;

}


/*
This method will do parallel for loop multiplication with optimization using block algorithms
*/
double parallel_for_multiplication_optimized(int n){

	int i, j, k;

	//get the transpose of matrixB
        transpose(n);

	//start time from the wall clock
	double startTime = omp_get_wtime();

	//calculate using transpose
	
	#pragma omp parallel for shared(matrixA, matrixB, matrixC) private(i, j, k) schedule(static) num_threads(THREADS)
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			double sum = 0;
			for (k = 0; k < n; k++){
				sum += matrixA[i][k] * transposeB[j][k];
			}		
			matrixC[i][j] = sum;
		}
		
	}


	//get the end time from wall clock
	double endTime = omp_get_wtime();

	//return the execution time
	return (endTime - startTime);

}

/*
This method will calculate the times taken to multiply matrices of different sizes using serial code
*/
void step4_1(){

	for (int n = 200; n <= 2000; n = n + 200){

		printf("\nStarting for n = %d\n\n", n);

		double sum = 0;

		for (int i = 0; i < SAMPLES; i++){

			populate_matrix(n);
			sum += serial_multiplication(n);

		}

		double average = sum / SAMPLES;

		printf("Serial: Time taken for a %d x %d matrix is %f s\n", n, n, average);
		printf("\n---------------------------------------------\n");

	}

}

/*
This method will calculate the times taken to multiply matrices of different sizes using parallel code
*/
void step4_2(){

	for (int n = 200; n <= 2000; n = n + 200){

		printf("\nStarting for n = %d\n\n", n);

		double sum = 0;

		for (int i = 0; i < SAMPLES; i++){

			populate_matrix(n);
			sum += parallel_for_multiplication(n);

		}

		double average = sum / SAMPLES;

		printf("Parallel: Time taken for a %d x %d matrix is %f s\n", n, n, average);
		printf("\n---------------------------------------------\n");

	}

}

/*
This method will calculate the times taken to multiply matrices of different sizes using optimized code
*/
void step8(){
	
	for (int n = 200; n <= 2000; n = n + 200){

		printf("\nStarting for n = %d\n\n", n);

		double sum = 0;

		for (int i = 0; i < SAMPLES; i++){

			populate_matrix(n);
			sum += parallel_for_multiplication_optimized(n);

		}

		double average = sum / SAMPLES;

		printf("Optimized: Time taken for a %d x %d matrix is %f s\n", n, n, average);
		printf("\n---------------------------------------------\n");

	}

}
