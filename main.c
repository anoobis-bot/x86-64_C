#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define SIZE 3

void cSAXPY(float* Z, float* X, float* Y, float A, int size);
extern void asmSAXPY(float* Z, float* X, float* Y,  int size, float A );
void displayArray(float* Z, int size);

int main() {
	float cZ[SIZE] = { 0 };
	float asmZ[SIZE] = { 0 };
	float X[SIZE] = { 1.0, 2.0, 3.0 };
	float Y[SIZE] = { 11.0, 12.0, 13.0 };
	float A = 2.0;

	cSAXPY(cZ, X, Y, A, SIZE);
	asmSAXPY(asmZ, X, Y, SIZE, A);

	printf("C results: ");
	displayArray(cZ, SIZE);
	printf("x86-64 results: ");
	displayArray(asmZ, SIZE);

	return 0;
}

void cSAXPY(float* Z, float* X, float* Y, float A, int size) {
	for (int i = 0; i < size; i++) {
		Z[i] = A * X[i] + Y[i];
	}
}

void displayArray(float* Z, int size) {
	for (int i = 0; i < size; i++) {
		printf("%.2f, ", Z[i]);
	}
	printf("\n");
}