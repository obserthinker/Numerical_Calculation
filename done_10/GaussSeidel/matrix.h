#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

/***********************************************************
Module Name: matrix.h
Module Date: 10/12/2014
Module Auth: Xuanyu Wang

Description: To produce,display a matrix.
    Revision History: None
***********************************************************/
/*----------------Includes---------------*/
//the head files that were included
//#include <stdio.h>
//#include <stdlib.h>

/*---------Structures and Typedefs-------*/
/*None
*/

/*---------------Defines-----------------*/
#define a_mn (i * n_column + j +1)//a(m,n) is the true serial number of the element

/*----------extern variables-------------*/
//the variables that were defined in other modules
//None

/*-----External Function Prototypes------*/
//the functions that were implemented in other modules


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* InitMatrix(int n_row,int n_column,double *matrix);
double* QuintudiagMatrix(int n_row,int n_column,double *matrix);
void PrintMatrix(int n_row,int n_column,double *matrix);
double* ChangeMatrix(int n_row, int n_column, double* matrix);
void GSIter(int n_row, int n_column, double *A, double *B, double *X);
double* AB(int n_row, int n_column, int single, double *A, double *B, double *result);
double* InitX(int n_row,int n_column,double *matrix);

/***********************************************************
Function Name: InitMatrix
Function Description: Produce a matrix which dimension had been input in main().
                                    And the matrix's member is all 0.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes:
************************************************************/
double* InitMatrix(int n_row,int n_column,double *matrix)
{
    int i,j;//counting the row and column
    matrix = (double *)malloc((n_row*n_column)*sizeof(double));//allocate the space for the matrix
    int count = 0;//initialize the matrix's value
    for(i = 0;i < n_row;i++){//for row
        for(j = 0;j < n_column;j++){//for column
            *(matrix + i* n_column + j ) = count;//give a(i+1,j+i) a value
        }
    }
    return (matrix);
}

/***********************************************************
Function Name: InitX
Function Description: Produce a matrix which dimension had been input in main().
                                    And the matrix's member is all 0.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes:
************************************************************/
double* InitX(int n_row,int n_column,double *matrix)
{
    int i,j;//counting the row and column
    matrix = (double *)malloc((n_row*n_column)*sizeof(double));//allocate the space for the matrix
    double coun = 0.49;//initialize the matrix's value
    for(i = 0;i < n_row;i++){//for row
        for(j = 0;j < n_column;j++){//for column
            *(matrix + i* n_column + j ) = coun;//give a(i+1,j+i) a value
        }
    }
    return (matrix);
}

/***********************************************************
Function Name: QuintudiagMatrix
Function Description: Produce a matrix which is a tridiagonal system.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes: This function is depended on InitMatrix. Before you use this function, you should
            built a matrix.
************************************************************/
double* QuintudiagMatrix(int n_row,int n_column,double *matrix)
{
    int i;
    for(i = 0;i < n_row;i++){
        //printf("\ni+1=%d\n",i+1);
        if((i + 1) == 1){
            //printf("first row:input the coefficient of the a(%d,%d) & a(%d,%d) & a(%d,%d):\n",1,1,1,2,1,3);
            scanf("%lf %lf %lf",matrix,(matrix+1),(matrix + 2));
            //printf("a(1,1)=%f\ta(1,2)=%f\n",*matrix,*(matrix+1));//for testing
        }
        else if((i + 1) == 2){
            //printf("first row:input the coefficient of the a(%d,%d) & a(%d,%d) & a(%d,%d) & a(%d,%d):\n",2,1,2,2,2,3,2,4);
            scanf("%lf %lf %lf %lf",matrix+n_column,(matrix+1+n_column),(matrix + 2+n_column),(matrix + 3+n_column));
        }
        else if((i + 1) == n_row-1){
            //printf("input the coefficient of the a(%d,%d) & a(%d,%d) & a(%d,%d) & a(%d,%d):\n",n_row-1,n_row-3,n_row-1,n_row-2,n_row-1,n_row-1,n_row-1,n_row);
            scanf("%lf %lf %lf %lf",matrix+(n_row-1)*n_column-4,matrix+(n_row-1)*n_column-3,matrix+(n_row-1)*n_column-2,matrix+(n_row-1)*n_column-1);
        }
        else if((i + 1) == n_row){
            //printf("input the coefficient of the a(%d,%d) & a(%d,%d) & a(%d,%d):\n",n_row,n_row-2,n_row,n_row-1,n_row,n_row);
            scanf("%lf %lf %lf",matrix+n_row*n_column-3,matrix+n_row*n_column-2,matrix+n_row*n_column-1);
            //printf("a(%d,%d)=%f\ta(%d,%d)=%f",n_row,n_row-1,*(matrix+n_row*n_column-2),n_row,n_row,*(matrix+n_row*n_column-1));//for testing
        }
        else{
            //printf("input the coefficient of the a(%d,%d) & a(%d,%d) & a(%d,%d):\n",i+1,i,i+1,i+1,i+1,i+2);
            scanf("%lf %lf %lf %lf %lf",matrix+i*n_column+i-2,matrix+i*n_column+i-1,matrix+i*n_column+i,matrix+i*n_column+i+1,matrix+i*n_column+i+2);
            //printf("a(%d,%d)=%f & a(%d,%d)=%f & a(%d,%d) =%f\n",i+1,i,*(matrix+i*n_row+i-1),i+1,i+1,*(matrix+i*n_row+i),i+1,i+2,*(matrix+i*n_row+i+1));
        }
    }
    return matrix;
}

/***********************************************************
Function Name: PrintMatrix
Function Description: The function display the matrix on the screen. The member of
                                    each row is equal to the number of column.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: There are no argument need to be return.
Notes:
************************************************************/
void PrintMatrix(int n_row,int n_column,double *matrix)
{
    printf("\n");
    int i,j;
    for(i = 0;i < n_row;i++){//display every member of the matrix
        for(j = 0;j < n_column;j++){
            //printf("(%d,%d)",i,j);
            printf("%lf   ",*(matrix + i * n_column + j));//attention:the format should adjust when you need
        }
        printf("\n");
    }
}

/***********************************************************
Function Name: ChangeMatrix
Function Description: Produce a matrix which dimension had been input in main().
                                    And the member's value is decided by user.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes:
************************************************************/
double* ChangeMatrix(int n_row, int n_column, double* matrix)
{
    int i,j;//counting the row and column
    matrix = (double *)malloc((n_row*n_column)*sizeof(double));//allocate the space for the matrix

    for(i = 0; i < n_row; i++){//for row
        //printf("the %d line is waiting for your:\n", i + 1);
        for(j = 0; j < n_column; j++){//for column
            //printf("the a(%d,%d) = ", i + 1, j + 1);
            scanf("%lf", (matrix + a_mn - 1 ));//give a(i+1,j+i) a value
        }
    }

    return (matrix);
}

/***********************************************************
Function Name: GSIter
Function Description: Use the Gauss-Seidel iteration to solve the matrix euqation.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double. Generally, the matrix is a
            n*n matrix and the X and B are n*1 matrix.
Outputs: Print the solution X.
Notes:
************************************************************/
void GSIter(int n_row, int n_column, double *A, double *B, double *X)
{
    int i,j,k,single = 1;
    double sum,tol = 0.00001,err;
    double *te;
    double a[5]={0};
    PrintMatrix(n_row,n_column,A);
    te = InitX(n_row,single,te);
    do{
        for(k = 0;k < n_column;k++){
            *(te+k) = *(X+k);
        }
        for(i = 0; i < n_row; i++){
            for(j = 0; j < n_column; j++){
                if(j != i){
                    sum += *(X + j) * (*(A + i*n_column + j));
                }
            }
            *(X + i) = ((*(B + i)) - sum) / (*(A + i*n_column + i));
            sum = 0;
        }
        err = 0;
        for(k = 0;k < n_column;k++){
            err += fabs(*(X+k)-*(te+k));
        }

    }while(err > tol);
    printf("X = ");
    PrintMatrix(n_row, 1, X);
}
/***********************************************************
Function Name: AB
Function Description: to calculate the result of A times B
Inputs:  The first is the number of A's row. It should be a positive int.
            The second is the number of the A's column and it should be positive int,too. The third
            is the number of the B's column. The forth is matrix A and the fifth is matrix B
Outputs: Return the result of A*B.
Notes:The function assume A's column is equal with B's row.
************************************************************/
double* AB(int n_row, int n_column, int single, double *A, double *B, double *result)
{
    printf("\n");
    int i,j,k;
    double sum = 0;
    for(i = 0; i < n_row; i++){
        for(j = 0; j < single; j++){
            for(k = 0; k < n_column; k++){
                sum += (*(A + i*n_row + k)) * (*(B + k*single + j));
            }
            *(result + i*single + j) = sum;
            //printf("result = %lf\n\n",*(result + i*single + j));
            sum = 0;
        }

    }
    return result;
}


/*
void SolveAXB(int n_row, int n_column, double *A, double *X, double *B)
{
    int i = 0, j = 0;
    double sum = 0;
    for(i = n_row - 1; i >= 0; i--){
        if(i == n_row - 1){
            printf("\ni = %d, %lf = %lf / %lf", i, *(B + i) / *(A + i*n_column + i), *(B + i), *(A + i*n_column + i));
            *(X + i) = *(B + i) / *(A + i*n_column + i);
        }
        else{
            sum = *(X + i + 1) * (*(A + i*n_column + i + 1));
            printf("\nsum = %lf",sum);
            printf("\ni = %d, %lf = (%lf - %lf) / %lf", i, (*(B + i) -  sum)/ *(A + i*n_column + i), *(B + i),sum, *(A + i*n_column + i));
            *(X + i) = (*(B + i) -  sum)/ *(A + i*n_column + i);
        }
        sum = 0;
    }
    printf("\nX= ");
    PrintMatrix(n_row, 1, X);
}
*/

/*void Eliminate(int n_row,int n_column,double *matrix, double *B)
{
    int i = 0;
    double coe;
    for(i = 0;i < n_row - 1 ;i++){
            coe = -(*(matrix + i * n_column + i + n_column) / (*(matrix + i * n_column + i)) );
            printf("coe = %lf\n",coe);
            //printf("%lf/%lf=coefficient=%lf\n",*(matrix + n_column),(*(matrix)),coe);
            *(matrix + i * n_column + i + n_column) = 0;
            *(B + i * 1 + 1) = *(B + i*1)*coe+*(B + i * 1 + 1);
            *(matrix + i * n_column + i + n_column + 1) = *(matrix + i * n_column + i + 1) * coe + (*(matrix + i * n_column + i + n_column + 1));
    }



}*/
#endif // MATRIX_H_INCLUDED
