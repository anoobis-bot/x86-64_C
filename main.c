#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define SIZE 1048576 // 2^20
//#define SIZE 16777216// 2^24
//#define SIZE 536870912// 2^29
//#define SIZE 1073741824// 2^30

void c_asm_correctnessCheck();
void cSAXPY(float* Z, float* X, float* Y, float A, int size);
extern void asmSAXPY(float* Z, float* X, float* Y, float A, int size);
void displayArray(float* Z, int size);
void randomNumberGenerator(float* array, int size, int seed);

int main() {
	float *cZ = (float*)malloc(SIZE * sizeof(float));
	float *asmZ = (float*)malloc(SIZE * sizeof(float));
	float *X = (float*)malloc(SIZE * sizeof(float));
	float *Y = (float*)malloc(SIZE * sizeof(float));
	float A = 2.0;
	double c_time_spent = 0;
	double asm_time_spent = 0;
	double total_c_time_spent = 0;
	double total_asm_time_spent = 0;

	c_asm_correctnessCheck();

	for (int i = 0; i < 30; i++) {

		randomNumberGenerator(X, SIZE, 1);
		randomNumberGenerator(Y, SIZE, 3);

		clock_t begin = clock();
		cSAXPY(cZ, X, Y, A, SIZE);
		//printf("C results:\n");
		//displayArray(cZ, SIZE);
		clock_t end = clock();
		c_time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

		clock_t begin_asm = clock();
		asmSAXPY(asmZ, X, Y, A, SIZE);
		//printf("\nx86-64 results:\n");
		//displayArray(asmZ, SIZE);
		clock_t end_asm = clock();
		asm_time_spent = (double)(end_asm - begin_asm) / CLOCKS_PER_SEC;

		total_c_time_spent += c_time_spent;
		total_asm_time_spent += asm_time_spent;
		
		printf("Iteration %d", i + 1);
		printf("\nExecution time in C: %.4lf seconds\n", c_time_spent);
		printf("Execution time in Assembly: %.4lf seconds\n\n", asm_time_spent);

	}

	printf("\nAverage Execution time in C: %.4lf seconds\n", total_c_time_spent / 30);
	printf("Average Execution time in Assembly: %.4lf seconds\n\n", total_asm_time_spent / 30);

	free(cZ);
	free(asmZ);
	free(X);
	free(Y);

	return 0;
}

void c_asm_correctnessCheck() {
	float cZ[3] = { 0 };
	float asmZ[3] = { 0 };
	float X[3] = { 1.0, 2.0, 3.0 };
	float Y[3] = { 11.0, 12.0, 13.0 };
	float A = 2.0;

	cSAXPY(cZ, X, Y, A, 3);
	asmSAXPY(asmZ, X, Y, A, 3);

	printf("Correctness Check for C & x86-64\n\n");
	printf("C results: ");
	displayArray(cZ, 3);
	printf("x86-64 results: ");
	displayArray(asmZ, 3);
	printf("\n\n");
}

void cSAXPY(float* Z, float* X, float* Y, float A, int size) {
	for (int i = 0; i < size; i++) {
		Z[i] = A * X[i] + Y[i];
	}
}

void displayArray(float* Z, int size) {
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			printf("%.2f ", Z[i]);
		else
			printf("%.2f, ", Z[i]);
	}
	printf("\n");
}

void randomNumberGenerator(float* array, int size, int seed) {
	srand( ((unsigned int)time(NULL)) / seed );
	for (int i = 0; i < size; i++) {
		array[i] = (float)(rand() % 10000 + 1) / 100;
	}
}