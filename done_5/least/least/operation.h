#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
/***********************************************************
Module Name: operation.h
Module Date: 11/7/14
Module Auth: Xuanyu Wang
Description: all operation needed in this question.
***********************************************************/
/*----------------Includes---------------*/
#include <math.h>
/*---------Structures and Typedefs-------*/
struct Vector
{
	double *X;
	int N;
};
typedef struct Vector Vector;
/*---------------Defines-----------------*/


void PrintMatrix(int n_row, int n_column, double *matrix);
void InitVector(Vector *Vec, int jud);
void ShowVector(Vector *Vec);
double Sum(Vector *Vec);
void Square(Vector *Vec);
void VPXY(Vector *X, Vector *Y, Vector *XY);
void SolveAXB(int n_row, int n_column, double *A, double *X, double *B);

/***********************************************************
Function Name: InitVector
Function Description: Initialize the variable of vector.
Inputs: Need a point of variable Vector. And a sign jud to judge which kind 
           of initializtion will be used.
Outputs: None
************************************************************/
void InitVector(Vector *Vec,int jud)
{
	int i;
	//Get the number of elements of vector
	printf("Input the Number of Node:");
	scanf_s("%d", &(Vec->N));
	//initialize the vector's elements
	Vec->X = malloc((Vec->N)*sizeof(double));
	//assign the value of vector's elements'
	//There are two modes. if jud=1, get values from stdin
	//if jud=0. assign 0 to all elements' value.
	for (i = 0; i < Vec->N; i++){
		if (jud == 1){
				printf("Input the No.%d's value:", i + 1);
				scanf_s("%lf", Vec->X + i);
			}
		else{
			*(Vec->X + i) = 0;
		}
	}
}
/***********************************************************
Function Name: ShowVector
Function Description: Display elements of a vector.
Inputs: Need a point of variable Vector.
Outputs: print elements' value in the stdout
************************************************************/
void ShowVector(Vector *Vec)
{
	int i;
	for (i = 0; i < Vec->N; i++){
		printf("The No.%d's value is:%lf\n", i + 1, *((Vec->X) + i));
	}
}
/***********************************************************
Function Name:Sum
Function Description: the sum of all elements
Inputs: Need a point of variable Vector.
Outputs: return the result as double
************************************************************/
double Sum(Vector *Vec)
{
	int i;
	double result = 0;//initlize the sum
	for (i = 0; i < Vec->N; i++){
		result += *(Vec->X+ i);
	}
	return result;
}
/***********************************************************
Function Name:Square
Function Description: square every element's value
Inputs: Need a point of variable Vector.
Outputs: None
************************************************************/
void Square(Vector *Vec)
{
	int i;
	for (i = 0; i < Vec->N; i++){
		*(Vec->X + i) = pow(*(Vec->X + i), 2);
	}
}
/***********************************************************
Function Name:VPXY
Function Description: the element's value of vector XY is corresponded the 
								X's element times Y's element.
Inputs: Need three points of variable Vector, X,Y,and XY.
Outputs: None
************************************************************/
void VPXY(Vector *X, Vector *Y,Vector *XY)
{
	int i;
	for (i = 0; i < X->N; i++){
		*(XY->X + i) = (*(X->X + i)) * (*(Y->X + i));
	}
}

/***********************************************************
Function Name: SolveAXB
Function Description: Solve the matrix A*X=B. A is a 2 deminsion matrix.
Inputs:The third is the point of the A. The X & B are 2*1 matrixs.
Outputs: Display the matrix of the X(solution).
Notes:The function need PrintMatrix function. And in this project,
A and B had been eliminated.
************************************************************/
void SolveAXB(double *A, double *X, double *B)
{
	int i;
	double coe;
	//use gauss elemination to change the A and B.
	coe = -*(A + 2) / *(A);
	*(A + 2) = 0;
	*(A + 3) += *(A + 1)*coe;
	*(B + 1) += *(B)*coe;
	//show A and B
	PrintMatrix(2, 2, A);
	PrintMatrix(2, 1, B);

	//solve the equation.
	*(X + 1) = *(B + 1) / *(A + 3);
	*(X) = (*(B)-(*(X + 1))* (*(A + 1))) / (*(A + 0));
	//show the solution of equation
	printf("\nX= ");
	PrintMatrix(2, 1, X);
}

/***********************************************************
Function Name: PrintMatrix
Function Description: The function display the matrix on the screen. The member of
each row is equal to the number of column.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
The second is the number of the column and it should be positive int,too. The third
is the point of the matrix and it should be double.
Outputs: There are no argument need to be return.
Notes:The matrix should be initialized.
************************************************************/
void PrintMatrix(int n_row, int n_column, double *matrix)
{
	printf("\n");
	int i, j;//for counting

	//display every member of the matrix
	for (i = 0; i < n_row; i++){
		for (j = 0; j < n_column; j++){
			printf("%f   ", *(matrix + i * n_column + j));//attention:the format should adjust when you need
		}
		printf("\n");
	}
}
#endif // OPERATION_H_INCLUDED
