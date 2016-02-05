#include <stdio.h>
#include <stdlib.h>
#include "allmatrix.h"

int main()
{
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double *matrix, *matrix2, *U, *P, *inver;
    double *E, *L, *idmatrix;
    double *B, *X, *Y;
    int n_row,n_column;
    int j;
    printf("please input the dimonsion of the Matrix you'll make:m & n:\n");
    scanf("%d %d",&n_row,&n_column);

/*--intialize the matrix which would be triangular factorize and the identity matrix--*/
    matrix = InitMatrix(n_row, n_column, matrix,0);
    matrix2 = InitMatrix(n_row, n_column, matrix2,0);
    inver = InitMatrix(n_row, n_column, inver,0);
    E = InitIdMatrix(n_row, n_column, E);
    P = InitIdMatrix(n_row, n_column, P);
    idmatrix = InitIdMatrix(n_row, n_column, idmatrix);

/*--assign the value of each matrix's element--*/
    matrix = SetMatrix(n_row, n_column, matrix);
    matrix2 = SetMatrix(n_row, n_column, matrix2);
/*--show the matrixs--*/
    printf("\nthe A(matrix) = ");
    PrintMatrix(n_row, n_column, matrix);
    //PrintMatrix(n_row, n_column, E);

    B = InitMatrix(n_row, 1, B,0);
    //B = SetMatrix(n_row, 1, B);
    //printf("\nB = ");
    //PrintMatrix(n_row, 1, B);

//pivoting the matrix
    Pivoting(n_row, n_column, matrix,P);
    E = AB(n_row,n_column,n_column,P,E);
    printf("!!!after pivoting, P = ");
    PrintMatrix(n_row,n_column,P);
    printf("after pivoting, E = ");
    PrintMatrix(n_row,n_column,E);
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

    //printf("check the B will used:");
    //PrintMatrix(n_row,1,B);
    //for each column,calculate the solution of it
    for(j = 0; j < n_column; j++){
            //get a column
        CopyToColumn(n_row,n_column,E,j,B);
        printf("the %d column of E to B:",j+1);
        PrintMatrix(n_row, 1,B);
    //solve it
        BackSub4Y(n_row, n_column, L, Y, B);
        BackSub4X(n_row, n_column, U, X, Y);
        CopyToMatrix(n_row,n_column,X,j,inver);
    }
    //display the result of [C]
    printf("inverse = ");
    PrintMatrix(n_row,n_column,inver);

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
    E = AB(n_row,n_column,n_column,matrix2,inver);
    //verify the result
    printf("AX(A*inver) = ");
    PrintMatrix(n_row,n_column,E);
    return 0;
}
