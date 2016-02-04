#include <stdio.h>
#include <stdlib.h>
#include "allmatrix.h"
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double *matrix, *U, *P;
    double *idmatrix, *L;
    double *B, *X, *Y;
    int n_row,n_column;
    int i;
    printf("please input the dimonsion of the Matrix you'll make:m & n:\n");
    scanf("%d %d",&n_row,&n_column);

/*--intialize the matrix which would be triangular factorize and the identity matrix--*/
    matrix = InitMatrix(n_row, n_column, matrix,1);
    double *matrix2;
    matrix2 = InitMatrix(n_row, n_column, matrix2,1);
    idmatrix = InitIdMatrix(n_row, n_column, idmatrix);
    P = InitIdMatrix(n_row, n_column, P);

/*--show the matrixs--*/
    //printf("\nthe A(matrix) = ");
    //PrintMatrix(n_row, n_column, matrix);
    //PrintMatrix(n_row, n_column, idmatrix);

    B = InitBMatrix(n_row, B);
    printf("\nB = ");
    PrintMatrix(n_row, 1, B);
//pivoting the matrix
    Pivoting(n_row, n_column, matrix,P);
    B = AB(n_row,n_column,1,P,B);
    //printf("after pivoting, P = ");
    //PrintMatrix(n_row,n_column,P);
    //printf("after pivoting, B = ");
    //PrintMatrix(n_row,1,B);
    //printf("after pivoting, matrix = ");
    //PrintMatrix(n_row,n_column,matrix);
/*--Using the triangular factorization to factorize the matrix--*/
//matrix had been changed
    LUFact(n_row, n_column, matrix, idmatrix);

/*--show the result of the matrix had been factorized--*/
    //printf("L = ");//show the lower-triangular matrix
    L = idmatrix;
    //PrintMatrix(n_row, n_column, L);
    //printf("U = ");//show the upper-triangular matrix
    U = matrix;
    //PrintMatrix(n_row, n_column, U);

    X = InitMatrix(n_row, 1, X,0);
    Y = InitMatrix(n_row, 1, Y,0);
    //printf("check the B will used:");
    //PrintMatrix(n_row,1,B);
    /*--use back sub to calculate X and Y--*/
    BackSub4Y(n_row, n_column, L, Y, B);
    BackSub4X(n_row, n_column, U, X, Y);

    /*printf("X = ");
    PrintMatrix(n_row, 1, X);
    B=AB(n_row,n_column,1,U,X);
    printf("UX = ");
    PrintMatrix(n_row, 1, B);
    B=AB(n_row,n_column,1,L,B);
    printf("LUX = ");
    PrintMatrix(n_row, 1, B);
    printf("A=");
    PrintMatrix(n_row,n_column,matrix2);*/
    //verify the answer
    B = AB(n_row,n_column,1,matrix2,X);
    printf("AX = ");
    PrintMatrix(n_row,1,B);
    return 0;
}
