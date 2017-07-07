#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#define THREADS 20

using namespace std;

int SAMPLES = 1;

//MatrixA and MatrixB will  be the input Matrices - maximum size 2000
double matrixA[2000][2000];
double matrixB[2000][2000];

//this matrix will be the multiplication of Matrix A and B
double matrixC[2000][2000];

int min(int a, int b);
void populate_matrix(int n);
double serial_multiplication(int n);
double parallel_for_multiplication(int n);
double parallel_for_multiplication_optimized(int n);

void step4_1();
void step4_2();
void step8();

int main() {

	char method;

	//Enter method
	//printf("Enter one of the options given below\n \ts - for serial program \n\tp - for parallel program \n\to - for optimized program\n");
	//scanf("%c", &method);

	//Enter sample size
	printf("Enter sample size: ");
	scanf("%d", &SAMPLES);

/*	switch (method) {
		case 's':
			step4_1();
			break;

		case 'p':
			step4_2();
			break;

		case 'o':
			step8();
			break;
			
	}*/
	
	step8();
	step4_2();
	step4_1();
	return 0;


}

/*
This method will preturn the minimum out of two numbers
*/
int min(int a, int b){
	return a < b ? a : b;
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

	int i, j, k;
	double sum;

	//start time from the wall clock
	double startTime = omp_get_wtime();

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			sum = 0;
			for (k = 0; k < n; k++){
				sum = sum + matrixA[i][k] * matrixB[k][j];
			}
			matrixC[i][j] = sum;
			//printf("%f\n" , sum);
		}
	}

	//get the end time
	double endTime = omp_get_wtime();

	return endTime - startTime;
}

/*
This method will do parallel for loop multiplication
*/
double parallel_for_multiplication(int n){
		
	//start time from the wall clock
	double startTime = omp_get_wtime();
	int chunks = n/THREADS;

	#pragma omp parallel for shared(matrixA,  matrixB, matrixC) schedule(static) num_threads(THREADS)
	for (int i = 0; i < n ; i++ ){
		
		for (int j = 0; j < n ; j++ ){
			double sum = 0;
			for (int k = 0; k < n ; k++ ){
				sum = sum + matrixA[i][k]*matrixB[k][j];
				
			}
			matrixC[i][j] = sum;
			//printf("%f\n" , sum);
		
		}
		
	}

	//get the end time
	double endTime = omp_get_wtime();

	return endTime - startTime;

}


/*
This method will do parallel for loop multiplication with optimization using block algorithms
*/
double parallel_for_multiplication_optimized(int n){

	int block_size = n / THREADS;
	int i, j, k, i0, j0, k0;
	double sum;
	int chunks = n / THREADS;

	//start time from the wall clock
	double startTime = omp_get_wtime();

	//divide the matrix in to blocks and calculate
	//use block algorithms
	
	#pragma omp parallel for shared(matrixA,  matrixB, matrixC) private(i, j, k, sum) schedule(static) num_threads(THREADS)
	for (i0 = 0; i0 < n; i0 += block_size){
		for (j0 = 0; j0 < n; j0 += block_size){
			for (k0 = 0; k0 < n; k0 += block_size){
				for (i = i0; i < min(i0 + block_size, n); i++){
					for (j = j0; j < min(j0 + block_size, n); j++){
						sum = 0;
						for (k = k0; k < min(k0 + block_size, n); k++){
							sum += matrixA[i][k] * matrixB[k][j];
						}
						matrixC[i][j] += sum;
					}
				}
			}
		}
	}

	//get the end time
	double endTime = omp_get_wtime();

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
