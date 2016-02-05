//Notes:All the Printf() or PrintMatrix() which had been hidden are for testing
#include <stdio.h>
#include <stdlib.h>
#include "allmatrix.h"
int main()
{
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    //matrix*X = B;matrix2=matrix. inver is the inverse of matrix.P*matrix=LU.
    double *matrix, *matrix2, *U, *P, *inver;
    //E & idmatrix are identity matrix.
    double *E, *L, *idmatrix;
    //UX=Y,LY=B
    double *B, *X, *Y;
    int n_row,n_column;//the dimension of the matrix.
    int j;//for counting

    //To get the dimension of the matrix
    printf("please input the dimonsion of the Matrix you'll make:m & n:\n");
    scanf("%d %d",&n_row,&n_column);

/*--intialize the matrix--*/
    matrix = InitMatrix(n_row, n_column, matrix,0);
    matrix2 = InitMatrix(n_row, n_column, matrix2,0);
    //inver = InitMatrix(n_row, n_column, inver);
    //E = InitIdMatrix(n_row, n_column, E);
    P = InitIdMatrix(n_row, n_column, P);
    idmatrix = InitIdMatrix(n_row, n_column, idmatrix);

/*--assign the value of each matrix's element--*/
    matrix = SetMatrix(n_row, n_column, matrix);
    matrix2 = SetMatrix(n_row, n_column, matrix2);
/*--show the matrixs--*/
    printf("\nthe A(matrix) = ");
    PrintMatrix(n_row, n_column, matrix);
    //PrintMatrix(n_row, n_column, E);

/*--To intialize the matrix, and assign the value of each matrix's element--*/
    B = InitMatrix(n_row, 1, B,0);
    B = SetMatrix(n_row, 1, B);
    printf("\nB = ");
    PrintMatrix(n_row, 1, B);

/*--pivote the matrix--*/
    Pivoting(n_row, n_column, matrix,P);
    //change the B accordingly
    B = AB(n_row,n_column,1,P,B);
    printf("after pivoting, P = ");
    PrintMatrix(n_row,n_column,P);
    printf("after pivoting, B = ");
    PrintMatrix(n_row,1,B);
    printf("after pivoting, matrix = ");
    PrintMatrix(n_row,n_column,matrix);
/*--Using the triangular factorization to factorize the matrix--*/
//matrix had been changed
    LUFact(n_row, n_column, matrix, idmatrix);

/*--show the result of the matrix had been factorized--*/
    printf("L = ");//show the lower-triangular matrix
    L = idmatrix;
    PrintMatrix(n_row, n_column, L);
    printf("U = ");//show the upper-triangular matrix
    U = matrix;
    PrintMatrix(n_row, n_column, U);

    X = InitMatrix(n_row, 1, X,0);
    Y = InitMatrix(n_row, 1, Y,0);

    BackSub4Y(n_row, n_column, L, Y, B);
    BackSub4X(n_row, n_column, U, X, Y);

    printf("AX(A*X) = ");
    B = AB(n_row,n_column,1,matrix2,X);
    PrintMatrix(n_row,1,B);
    return 0;
}
