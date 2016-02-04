#include <stdio.h>
#include <stdlib.h>
#include "allmatrix.h"
int main()
{
    freopen("in2.txt","r",stdin);//for testing, load data from a file
    double *matrix, *X, *B;//matrix*X = B;matrix is the tridiagonal matrix.
    int n_row,n_column;//the number of matrix's row and column
    int single = 1;//the number of X and B's column

    //printf("please input the dimonsion of the Matrix you'll make:m & n:\n");
    scanf("%d%d",&n_row,&n_column);//Get the dimension of the matrix

    matrix = InitMatrix(n_row,n_column,matrix,0);//produce a matrix, all elements are 0
    X = InitMatrix(n_row, single, X,0);//produce a X, all elements are 0
    B = InitMatrix(n_row, single, B,0);//produce a B, all elements are 0

    matrix = TridiagMatrix(n_row,n_column,matrix);//change the matrix into a tridiagonal matrix
    B = SetMatrix(n_row, 1, B);//set the B
    //display the matrix
    printf("\nTriMatrix = ");
    PrintMatrix(n_row,n_column,matrix);//display the matrix
    //display the B
    printf("\nB = ");
    PrintMatrix(n_row, 1, B);//display the matrix

    //eliminate the matrix's elements
    TridiagEliminate(n_row,n_column,matrix,B);
    //display the matrix after elimination
    printf("\nAfter the elimination the matrix = ");
    PrintMatrix(n_row,n_column,matrix);
    //display the matrix after elimination with matrix
    printf("\nAfter the elimination the B = ");
    PrintMatrix(n_row,1,B);

    //solve the equation matrix*X = B
    SolveAXB(n_row, n_column, matrix, X, B);
}
