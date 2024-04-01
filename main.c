#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

//#define SIZE 3
//#define SIZE 1048576 // 2^20
//#define SIZE 16777216// 2^24
#define SIZE 536870912// 2^29
//#define SIZE 1073741824// 2^30

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

	//// assign value to given
	//X[0] = 1.0;
	//X[1] = 2.0;
	//X[2] = 3.0;

	//Y[0] = 11.0;
	//Y[1] = 12.0;
	//Y[2] = 13.0;

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


	printf("\nExecution time in C: %.4lf seconds\n", c_time_spent);
	printf("Execution time in Assembly: %.4lf seconds\n", asm_time_spent);

	return 0;
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