#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main()
{
	freopen("in2.txt", "r", stdin);
	freopen("out2.txt", "w", stdout);
	Vector *X, *Y;
	Vector *XSquare,*XY;
	double Sum_XSquare;
	double Sum_XY;
	double Sum_X;
	double Sum_Y;
	
	X = malloc(sizeof(Vector));
	Y = malloc(sizeof(Vector));
	XSquare = malloc(sizeof(Vector));
	XY = malloc(sizeof(Vector));
	
	/*--calculate the coefficience of regular matrix--*/
	InitVector(X,1);
	printf("\nX vector\n");
	ShowVector(X);

	InitVector(Y,1);
	printf("\nY vector\n");
	ShowVector(Y);

	InitVector(XSquare,1);
	printf("\nXSquare vector\n");
	ShowVector(XSquare);

	InitVector(XY,0);
	printf("\nXY vector\n");
	ShowVector(XY);

	Sum_X = Sum(X);
	Sum_Y = Sum(Y);

	Square(XSquare);
	printf("\nafter square\n");
	ShowVector(XSquare);

	Sum_XSquare = Sum(XSquare);
	VPXY(X, Y, XY);
	printf("aaa\n");
	ShowVector(XY);
	Sum_XY=Sum(XY);
	printf("sum_x=%lf\n", Sum_X);
	printf("sum_y=%lf\n", Sum_Y);
	printf("sum_xsquare=%lf\n", Sum_XSquare);
	printf("sum_xy=%lf\n", Sum_XY);

	/*--initialize matrixs--*/
	double *A, *solution, *B;
	A = malloc(4 * sizeof(double));
	solution = malloc(2 * sizeof(double));
	B = malloc(2 * sizeof(double));
	//assign the value to A's element
	*(A + 0) = Sum_XSquare;
	*(A + 1) = Sum_X;
	*(A + 2) = Sum_X;
	*(A + 3) = X->N;
	*(B + 0) = Sum_XY;
	*(B + 1) = Sum_Y;
	/*--solve the equation--*/
	SolveAXB(A, solution, B);
	return 0;
}
