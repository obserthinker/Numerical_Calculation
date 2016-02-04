#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main()
{
    //freopen("in1.txt","r",stdin);
    freopen("in2.txt","r",stdin);
    freopen("out.txt","w",stdout);
    double *matrix, *X, *B;
    int n_row,n_column;
    int single = 1;

    printf("please input the dimonsion of the Matrix you'll make:m & n:\n");
    scanf("%d%d",&n_row,&n_column);//Get the dimension of the matrix

    matrix = InitMatrix(n_row,n_column,matrix);//produce a matrix
    X = InitMatrix(n_row, single, X);
    B = InitMatrix(n_row, single, B);
    printf("Matrix = ");
    PrintMatrix(n_row,n_column,matrix);//display the matrix
    printf("\nX = ");
    PrintMatrix(n_row, single, X);
    printf("\nB = ");
    PrintMatrix(n_row, single, B);

    matrix = TridiagMatrix(n_row,n_column,matrix);//change the matrix into a tridiagonal matrix
    B = ChangeMatrix(n_row, 1, B);
    printf("\nTriMatrix = ");
    PrintMatrix(n_row,n_column,matrix);//display the matrix
    printf("\nB = ");
    PrintMatrix(n_row, 1, B);//display the matrix

    Eliminate(n_row,n_column,matrix,B);
    printf("\nAfter the elimination the matrix = ");
    PrintMatrix(n_row,n_column,matrix);//display the matrix
    printf("\nAfter the elimination the B = ");
    PrintMatrix(n_row,1,B);//display the matrix

    SolveAXB(n_row, n_column, matrix, X, B);
}
