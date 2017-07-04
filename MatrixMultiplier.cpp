#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define THREADS 4
#define SAMPLES 50

using namespace std;

//MatrixA and MatrixB will  be the input Matrices - maximum size 2000
double matrixA[2000][2000];
double matrixB[2000][2000];

//this matrix will be the multiplication of Matrix A and B
double matrixC[2000][2000];

void populate_matrix(int n);
double serial_multiplication(int n);
double parallel_for_multiplication(int n);

void step4_1();
void step4_2();

int main() {

	step4_1();
	//step4_2();


	
}

/*
This method will populate the matrix with random numbers
*/
void populate_matrix(int n){
	
	//different seed for each experiment
	srand(time(NULL));

	//populate matrices
	for (int i = 0; i < n ; i++ ){
		for (int j = 0; j < n ; j++ ){
			matrixA[i][j] = rand();
			matrixB[i][j] = rand();
		
		}
	}

}

/* 
This methid will do serial multiplication
*/
double serial_multiplication(int n){

	//start time from the wall clock
	double startTime = omp_get_wtime();

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
This method will do parallel for loop multiplication
*/
double parallel_for_multiplication(int n){
		
	//start time from the wall clock
	double startTime = omp_get_wtime();
	int chunks = n/THREADS;

	#pragma omp parallel for schedule(dynamic, chunks) num_threads(THREADS)
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

void step4_1(){

	for (int n = 200; n <= 2000; n=n+200){

		printf("\nStarting for n = %d\n\n" , n);
		populate_matrix(n);
		
		printf("Serial: Time taken for a %d x %d matrix is %f\n" , n,n, serial_multiplication(n));
		printf("Parallel For: Time taken for a %d x %d matrix is %f\n" , n,n, parallel_for_multiplication(n));
		printf("\n---------------------------------------------\n");

	}

}

void step4_2(){

	int n = 200;
	double sum1 = 0;
	double sum2 = 0;

	populate_matrix(n);

	for (int i = 0; i < SAMPLES; i++){

		
		sum1 += serial_multiplication(n);
		sum2 += parallel_for_multiplication(n);


	}

	double average1 = sum1/n;
	double average2 = sum2/n;

		printf ("Average time for Serial %d x %d with %d samples = %f\n" , n,n,SAMPLES, average1);
	printf ("Average time for Parallel %d x %d with %d samples = %f\n" , n,n,SAMPLES, average2);

}























