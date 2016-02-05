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
//None

#include <stdio.h>
#include <stdlib.h>

/***********************************************************
Function Name: InitMatrix
Function Description: Produce a matrix which dimension had been input in main().
                                    And the matrix's member is all 0.
Inputs: Three argument are required. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes:The module is individual
************************************************************/
double* InitMatrix(int n_row,int n_column,double *matrix)
{
    int i,j;//counting the row and column
    matrix = (double *)malloc((n_row*n_column)*sizeof(double));//allocate the space for the matrix
    double value = 0;//define the matrix's value
    for(i = 0;i < n_row;i++){//for row
        for(j = 0;j < n_column;j++){//for column
            *(matrix + i* n_column + j ) = value;//give a(i+1,j+i) a value
        }
    }
    return (matrix);//return a one-dimension double array
}
/***********************************************************
Function Name: TridiagMatrix
Function Description: Produce a matrix which is a tridiagonal matrix.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes: This function is depended on InitMatrix. Before you use this function, you should
            initialize a matrix.
************************************************************/
double* TridiagMatrix(int n_row,int n_column,double *matrix)
{
    int i;//i is for counting
    for(i = 0;i < n_row;i++){
        //for the first row, we need two coefficients
        if((i + 1) == 1){
            printf("first row:input the coefficient of the a(%d,%d) & a(%d,%d):\n",1,1,1,2);
            scanf("%lf %lf",matrix,(matrix+1));
        }
        //for the last row, we need two coefficients
        else if((i + 1) == n_row){
            printf("input the coefficient of the a(%d,%d) & a(%d,%d):\n",n_row,n_row-1,n_row,n_row);
            scanf("%lf %lf",matrix+n_row*n_column-2,matrix+n_row*n_column-1);
        }
        //for each row except first and last need three coefficient
        else{
            printf("input the coefficient of the a(%d,%d) & a(%d,%d) & a(%d,%d):\n",i+1,i,i+1,i+1,i+1,i+2);
            scanf("%lf %lf %lf",matrix+i*n_column+i-1,matrix+i*n_column+i,matrix+i*n_column+i+1);
        }
    }
    return (matrix);//return the point of one-dimension array
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
    int i,j;//for counting

    //display every member of the matrix
    for(i = 0;i < n_row;i++){
        for(j = 0;j < n_column;j++){
            printf("%f   ",*(matrix + i * n_column + j));//attention:the format should adjust when you need
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
    //matrix = (double *)malloc((n_row*n_column)*sizeof(double));//allocate the space for the matrix

    for(i = 0; i < n_row; i++){//for row
        printf("the %d line is waiting for your:\n", i + 1);
        for(j = 0; j < n_column; j++){//for column
            printf("the a(%d,%d) = ", i + 1, j + 1);
            scanf("%lf", (matrix + a_mn - 1 ));//give a(i+1,j+i) a value
        }
    }

    return (matrix);
}

/***********************************************************
Function Name: SolveAXB
Function Description: Solve the matrix A*X=B.
Inputs: The n_row is the number of A's rows. It's a positive int.
            The n_column is the number of the column and it's positive int,too. The third
            is the point of the A. The X & B are n_row*1 matrixs.
Outputs: Display the matrix of the X(solution).
Notes:The function need PrintMatrix function. And in this project,
            A and B had been eliminated.
************************************************************/
void SolveAXB(int n_row, int n_column, double *A, double *X, double *B)
{
    int i = 0, j = 0;//for counting
    //'sum' is the sum of  i line of A timed with X, then reduce the a(i,i)*X(i)
    double sum = 0;
    //from the last row to solve the equation
    for(i = n_row - 1; i >= 0; i--){
        //for the last row we solve the unknown x_n directly
        if(i == n_row - 1){
            //display the operation for debug
            //x_n = b_n / d_n
            //printf("\ni = %d, %lf = %lf / %lf", i, *(B + i) / *(A + i*n_column + i), *(B + i), *(A + i*n_column + i));
            *(X + i) = *(B + i) / *(A + i*n_column + i);
        }
        //for the other rows we need the [B(i)-sum]/a(i,i) to calculate the x(n)
        else{
            sum = *(X + i + 1) * (*(A + i*n_column + i + 1));
            //display the operation to debug
            //printf("\nsum = %lf",sum);
            //printf("\ni = %d, %lf = (%lf - %lf) / %lf", i, (*(B + i) -  sum)/ *(A + i*n_column + i), *(B + i),sum, *(A + i*n_column + i));
            *(X + i) = (*(B + i) -  sum)/ *(A + i*n_column + i);
        }
        sum = 0;
    }
    //display the solution of A*X = B
    printf("\nX= ");
    PrintMatrix(n_row, 1, X);
}
/***********************************************************
Function Name: Eliminate
Function Description: Use the Frobenius matrix to eliminate the matrix.
Inputs: The n_row is the number of "matrix"'s rows. It's a positive int.
            The n_column is the number of the column and it's positive int,too.
            matrix plus B to produce a argumented matrix. The B are n_row*1 matrixs.
Outputs: None
Notes:
************************************************************/
void Eliminate(int n_row,int n_column,double *matrix, double *B)
{
    int i = 0;
    double coe;
    for(i = 0;i < n_row - 1 ;i++){
            //calculate the coefficient to eliminate the next row
            coe = -(*(matrix + i * n_column + i + n_column) / (*(matrix + i * n_column + i)) );
           // printf("coe = %lf\n",coe);//for testing
           //the operation of eliminate. The B need one step, and the matrix need two steps
            *(matrix + i * n_column + i + n_column) = 0;
            *(B + i * 1 + 1) = *(B + i*1)*coe+*(B + i * 1 + 1);
            *(matrix + i * n_column + i + n_column + 1) = *(matrix + i * n_column + i + 1) * coe + (*(matrix + i * n_column + i + n_column + 1));
    }
}
#endif // MATRIX_H_INCLUDED
