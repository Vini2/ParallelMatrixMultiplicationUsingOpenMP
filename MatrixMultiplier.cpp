#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#define THREADS 4
#define SAMPLES 100

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

	//step4_1();
	step4_2();


	
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
	
	for (int n = 200; n <= 2000; n=n+200){
		
		printf("Calculations for %d x %d matrix\n\n", n,n);

		//for mean calcuations
		double sum1 = 0;
		double sum2 = 0;
		
		//for standard deviation calculation
		double ssum1 = 0;
		double ssum2 = 0;

		populate_matrix(n);

		for (int i = 0; i < SAMPLES; i++){

			double serial = serial_multiplication(n);
			double parallel = parallel_for_multiplication(n);
			sum1 += serial;
			sum2 += parallel;
			
			ssum1 += pow(serial , 2);
			ssum2 += pow(parallel, 2);


		}

		double average1 = sum1/n;
		double average2 = sum2/n;
		
		double sd1 = sqrt ( (ssum1/n) - pow(average1,2)); 
		double sd2 = sqrt ( (ssum2/n) - pow(average2,2)); 

		printf ("Average time (mean) for Serial %d x %d with %d samples = %f\n" , n,n,SAMPLES, average1);
		printf ("SD time (sd) for Serial %d x %d with %d samples = %f\n\n" , n,n,SAMPLES, sd1);
		
		double sample1 = floor(pow( (100*1.96*sd1)/(5*average1) , 2));
		printf ("Required sample size for Serial %d x %d is: %f\n\n" , n,n, sample1);
		
		printf ("Average time (mean) for Parallel %d x %d with %d samples = %f\n" , n,n,SAMPLES, average2);
		printf ("SD time (sd) for Serial %d x %d with %d samples = %f\n\n" , n,n,SAMPLES, sd2);
		
		double sample2 = floor(pow( (100*1.96*sd2)/(5*average2) , 2));
		printf ("Required sample size for Parallel %d x %d is: %f\n\n" , n,n, sample2);
		
		printf("------------------------------\n");
		
		
	
	}

}























