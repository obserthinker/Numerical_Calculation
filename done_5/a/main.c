#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    vector *time,*tmpr;
    vector *matrix;
    vector *Q;
/*--initialize the variables --*/
    time=malloc(sizeof(vector*));
    tmpr=malloc(sizeof(vector*));
    matrix = malloc(sizeof(vector*));
    Q = malloc(sizeof(vector*));
/*--assign every variables every element--*/
    InitVector(time,1);
    ShowVector(time);
    InitVector(tmpr,1);
    ShowVector(tmpr);
    matrix->num = 9;
    matrix = calcu_coe(matrix, time, tmpr);
    PrintMatrix(3,3,matrix->value);
    Q->num = 3;
    Q = calcu_Q(Q, time, tmpr);
    PrintMatrix(3,1,Q->value);

/*--using LU factorization to solve the equation----*/
    double *P,*idmatrix,*X,*Y,*L,*U;

    P = InitIdMatrix(3, 3, P);
    idmatrix = InitIdMatrix(3, 3, idmatrix);

/*--pivote the matrix--*/
    Pivoting(3, 3, matrix->value,P);
    Q->value = AB(3,3,1,P,Q->value);

/*--Using the triangular factorization to factorize the matrix--*/
//matrix had been changed
    LUFact(3, 3, matrix->value, idmatrix);
    L = idmatrix;
    U = matrix->value;

    X = InitMatrix(3, 1, X,0);
    Y = InitMatrix(3, 1, Y,0);

    BackSub4Y(3, 3, L, Y, Q->value);
    BackSub4X(3, 3, U, X, Y);

    return 0;
}
