#include <stdio.h>
#include <stdlib.h>
#include "allmatrix.h"
int main()
{
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    double *matrix, *X, *B ,*result;
    int n_row,n_column;
    int single = 1;

    printf("please input the dimonsion of the Matrix you'll make:m & n:\n");
    scanf("%d%d",&n_row,&n_column);//Get the dimension of the matrix
/*--To intialize the matrix, and assign the value of each matrix's element--*/
    matrix = InitMatrix(n_row,n_column,matrix,0);//produce a matrix
    X = InitX(n_row, single, X);
    B = InitMatrix(n_row, single, B,0);
    result = InitMatrix(n_row,single,result,0);
    //printf("Matrix = ");
    //PrintMatrix(n_row,n_column,matrix);//display the matrix
    //printf("\nX = ");
    //PrintMatrix(n_row, single, X);
    //printf("\nB = ");
    //PrintMatrix(n_row, single, B);*/
    //printf("\nresult = ");
    //PrintMatrix(n_row, single, result);
/*--To intialize the matrix, and assign the value of each matrix's element--*/
    matrix = QuintudiagMatrix(n_row,n_column,matrix);//change the matrix into a tridiagonal matrix
    B = SetMatrix(n_row, 1, B);
    printf("\nTriMatrix = ");
    PrintMatrix(n_row,n_column,matrix);//display the matrix
    printf("\nB = ");
    PrintMatrix(n_row, 1, B);//display the matrix

/*--use Gauss-seidal iteration to solve--*/
    GSIter4all(n_row, n_column,matrix, B, X);
    result = AB(n_row,n_column,single,matrix,X);
    PrintMatrix(n_row,single,result);
}
