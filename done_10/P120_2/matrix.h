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
/*None*/

/*---------------Defines-----------------*/
#define a_mn (i * n_column + j +1)//a(m,n) is the true serial number of the element
#define a_jk ((j+1)*n_column+i+k)//the i+(j-i+1) line, i+k column element. i.e.
//from the m-1 line to n_row, the m+k true element.
/*----------extern variables-------------*/
//the variables that were defined in other modules
//None

/*-----External Function Prototypes------*/
//the functions that were implemented in other modules
//None

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    //int count = 0;//initialize the matrix's value
    for(i = 0; i < n_row; i++){//for row
        for(j = 0; j < n_column;j++){//for column
            *(matrix + a_mn - 1 ) = pow((double)(i+1),(double)(j));//give a(i+1,j+i) a value
        }
    }
    return (matrix);
}

/***********************************************************
Function Name: InitBMatrix
Function Description: Produce a vector B.
Inputs: The first is the number of row. It should be a positive int.
Outputs: Return the point of B.
Notes:
************************************************************/
double* InitBMatrix(int n_row,double *B)
{
    int i,j;//counting the row and column
    int n_column=1;
    B = (double *)malloc(n_row*sizeof(double));//allocate the space for the matrix
    //int count = 0;//initialize the matrix's value
    *(B+0) = (double)(n_row);
    for(i = 1; i < n_row; i++){//for row
            *(B + i ) = (pow((double)(i+1), n_row) - 1) / (i);//give a(i+1,1) a value
    }
    return (B);
}

/***********************************************************
Function Name: InitIdMatrix
Function Description: Produce a matrix which dimension is n_row*n_column
                                        and the diagonal element is 1 and other elements are 0.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return the point of the matrix.
Notes:
************************************************************/
double* InitIdMatrix(int n_row,int n_column,double *idmatrix)
{
    int i,j;//counting the row and column
    idmatrix = (double *)malloc((n_row*n_column)*sizeof(double));//allocate the space for the matrix
    int ii = 1;//when the element in diagonal line, assign the element ii
    int ij = 0;//when the element isn't in diagonal line, assign the element ij
    for(i = 0; i < n_row; i++){//for row
        for(j = 0; j < n_column;j++){//for column
                if(i+1 == j+1){
                    *(idmatrix + a_mn - 1 ) = ii;//give a(i+1,j+i) a value
                }
                else{
                    *(idmatrix + a_mn - 1 ) = ij;
                }
        }
    }
    return (idmatrix);
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
/*double* SetMatrix(int n_row, int n_column, double* matrix)
{
    int i,j;//counting the row and column
    matrix = (double *)malloc((n_row*n_column)*sizeof(double));//allocate the space for the matrix

    for(i = 0; i < n_row; i++){//for row
        printf("the %d line is waiting for your:\n", i + 1);
        for(j = 0; j < n_column; j++){//for column
            printf("the a(%d,%d) = ", i + 1, j + 1);
            scanf("%lf", (matrix + a_mn - 1 ));//give a(i+1,j+i) a value
        }
    }

    return (matrix);
}*/

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
            printf("%7.1f   ",*(matrix + a_mn - 1));//attention:the format should adjust when you need
        }
        printf("\n");
    }
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
double* AB(int n_row, int n_column, int single, double *A, double *B)
{
    printf("\n");
    double *result;
    result = InitIdMatrix(n_row,n_column,result);
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

/***********************************************************
Function Name: Pivoting
Function Description: To find the interchange matrix of matrix with using partial pivoting.
Inputs: The n_row is the number of "matrix"'s rows. It's a positive int.
            The n_column is the number of the column and it's positive int,too.
            the matrix is which would be pivoted. The P is the interchange matrix.
Outputs: None
Notes:
************************************************************/
void Pivoting(int n_row,int n_column,double *matrix,double *P)
{
    double maxium = 0;
    double *temp;//save the row would be changed
    temp = (double*)malloc(n_column*sizeof(double));
    int i, j;
    int mark;
    int fc;//just for interchange two lines of a matrix

    for(i = 0; i < n_column; i++){
//**************************************************************************************
            //for each row,you'll find the most max element of i column
            //in this section, the max will be founded and the line will be marked
            maxium = *(matrix + i*n_column + i);
            mark = i;
            for(j = i+1; j < n_row; j++){//from i line to row-1 line
                if(fabs(maxium) < fabs(*(matrix+j*n_row+i))){//if the max is samller than a(j,i)
                    maxium = *(matrix+j*n_row+i);//assign the max from a(j,i)
                    //printf("i=%d,j = %d\t maxium = %lf\t*(matrix+j*n_row+i) = %lf\n",i+1,j+1,maxium,*(matrix+j*n_row+i));
                    mark = j;//the j line will be marked
                    //printf("mark = %d,j = %d\n",mark,j);
                }
            }
            //printf("\nmax = %lf\n",maxium);
            //printf("\nthe %d line need to interchange with %d line\n",i+1,mark+1);
            if(mark == i){
                continue;
            }
//*********************************************************************
            //then, you need interchange the i line with "mark" line
            for(fc = 0; fc < n_column; fc++){
                *(temp+fc) = *(matrix+mark*n_row+fc);//put a(mk,fc) in cache t(fc)
                *(matrix+mark*n_row+fc) = *(matrix+i*n_row+fc);//a(mk,fc) = a(i,fc)
                *(matrix+i*n_row+fc) = *(temp +fc);//a(i,fc)=t(fc)
            }
            //PrintMatrix(n_row,n_column,P);
            for(fc = 0; fc < n_column; fc++){
                *(temp+fc) = *(P+mark*n_row+fc);//put a(mk,fc) in cache t(fc)
                //printf("mark = %d, mark*n_row+fc=%d\n",mark,mark*n_row+fc);
                //printf("temp(%d) = %lf\t%lf\n",fc,*(temp+fc),*(P+mark*n_row+fc));
                *(P+mark*n_row+fc) = *(P+i*n_row+fc);//a(mk,fc) = a(i,fc)
                *(P+i*n_row+fc) = *(temp +fc);//a(i,fc)=t(fc)
            }
            //PrintMatrix(n_row,n_column,matrix);
//*********************************************************************
    }

}

/***********************************************************
Function Name: LUFact
Function Description: The function to find the L and U with triangular factorization
Inputs:The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double and it will be U. The idmatrix is a
            identical matrix.
Outputs: There are no argument need to be return.
Notes:
************************************************************/
void LUFact(int n_row,int n_column,double *matrix, double *idmatrix)
{
    int i = 0, j = 0,k = 0;
    double coe;//the coefficient to eliminate
    for(i = 0;i < n_row - 1 ;i++){
        if(n_row == 1){
            return;
        }
        for(j = i; j < n_row - 1; j++){
            coe = -(*(matrix  + i + (j+1)*n_column) / (*(matrix + i * n_column + i)) );
            //printf("coe = %lf\n",coe);
            for(k = 0; k + i < n_column; k++){
                *(matrix + a_jk) = *(matrix + i * n_column +i + k) * coe + (*(matrix + a_jk));
                *(idmatrix + a_jk) = *(idmatrix + i * n_column + i + k) * (-coe) + (*(idmatrix  + a_jk));
            }
        }
    }
}
/***********************************************************
Function Name: BackSub4Y
Function Description: solve the Y in LY=B.
Inputs:The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too.
Outputs: There are no argument need to be return.
Notes:
************************************************************/
void  BackSub4Y(int n_row, int n_column, double *L, double *Y, double *B)
{
    int i = 0, j = 0;
    double sum_0i = 0;//the sum of member form 0 to i column of i line.
    for(i = 0; i < n_column; i++){
        for(j = 0; j < i; j++){
            sum_0i += *(L + a_mn - 1) * (*(Y+ j));
        }
        *(Y + i) = (*(B + i) - sum_0i) / *(L + i*n_column + i);//calculate the solution of Y_i
        sum_0i = 0;
    }
    printf("Y = ");
    PrintMatrix(n_row, 1, Y);
}
/***********************************************************
Function Name: BackSub4X
Function Description: solve the X in UX=Y.
Inputs:The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too.
Outputs: There are no argument need to be return.
Notes:
************************************************************/
void BackSub4X(int n_row, int n_column, double *U, double *X, double *Y)
{
    int i = 0, j = 0;
    double sum_iend = 0;
    for(i = n_row - 1; i >= 0; i--){
        for(j = n_column - 1; j > i; j--){
            sum_iend += *(U + a_mn - 1) * (*(X+ j));
        }
        *(X + i) = (*(Y + i) - sum_iend) / *(U + i*n_column + i);//calculate the solution of Y_i
        sum_iend = 0;
    }
    printf("X= ");
    PrintMatrix(n_row, 1, X);
}
#endif // MATRIX_H_INCLUDED
