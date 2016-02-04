#ifndef ALLMATRIX_H_INCLUDED
#define ALLMATRIX_H_INCLUDED

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
#define a_jk ((j+1)*n_column+i+k)//the i+(j-i+1) line, i+k column element. i.e.

/*----------extern variables-------------*/
//the variables that were defined in other modules
//None

/*-----External Function Prototypes------*/
//the functions that were implemented in other modules
//None

#include <stdio.h>
#include <stdlib.h>

double* InitMatrix(int n_row,int n_column,double *matrix, int special);
double* SetMatrix(int n_row, int n_column, double* matrix);
void PrintMatrix(int n_row,int n_column,double *matrix);
void SolveAXB(int n_row, int n_column, double *A, double *X, double *B);
void TridiagEliminate(int n_row,int n_column,double *matrix, double *B);
double* TridiagMatrix(int n_row,int n_column,double *matrix);
double* AB(int n_row, int n_column, int single, double *A, double *B);
void CopyToColumn(int n_row, int n_column, double *matrix, int j, double *B);
void CopyToMatrix(int n_row, int n_column, double *X, int j,double *matrix);
void  BackSub4Y(int n_row, int n_column, double *L, double *Y, double *B);
void BackSub4X(int n_row, int n_column, double *U, double *X, double *Y);
void LUFact(int n_row,int n_column,double *matrix, double *idmatrix);
double* InitIdMatrix(int n_row,int n_column,double *idmatrix);
void Pivoting(int n_row,int n_column,double *matrix,double *P);
void GSIter4tri(int n_row, int n_column, double *A, double *B, double *X);
void GSIter4all(int n_row, int n_column, double *A, double *B, double *X);
double* InitX(int n_row,int n_column,double *matrix);
double* QuintudiagMatrix(int n_row,int n_column,double *matrix);
double* InitBMatrix(int n_row,double *B);

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
double* InitMatrix(int n_row,int n_column,double *matrix,int special)
{
    if(special == 0){
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
    else{
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
}

/***********************************************************
Function Name: PrintMatrix
Function Description: The function display the matrix on the screen. The member of
                                    each row is equal to the number of column.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: There are no argument need to be return.
Notes:The matrix should be initialized.
************************************************************/
void PrintMatrix(int n_row,int n_column,double *matrix)
{
    printf("\n");
    int i,j;//for counting

    //display every member of the matrix
    for(i = 0;i < n_row;i++){
        for(j = 0;j < n_column;j++){
            printf("%.0lf   ",*(matrix + i * n_column + j));//attention:the format should adjust when you need
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
Notes:The matrix should be initialized.
************************************************************/
double* SetMatrix(int n_row, int n_column, double* matrix)
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
Function Name: TridiagMatrix
Function Description: Produce a matrix which is a tridiagonal matrix.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes: The matrix should be initialized.
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
Function Name: TridiagEliminate
Function Description: Use the Frobenius matrix to eliminate the tridiagonal matrix.
Inputs: The n_row is the number of "matrix"'s rows. It's a positive int.
            The n_column is the number of the column and it's positive int,too.
            matrix plus B to produce a argumented matrix. The B are n_row*1 matrixs.
Outputs: None
Notes:The matrix should be initialized and is a tridiagonal matrix.
************************************************************/
void TridiagEliminate(int n_row,int n_column,double *matrix, double *B)
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
    double *result;//the cache to save the A*B
    result = InitIdMatrix(n_row,n_column,result);//initialize the result
    int i,j,k;//for counting
    double sum = 0;//the sum of a(i,)*b(,j)
    for(i = 0; i < n_row; i++){
        for(j = 0; j < single; j++){
            //calculate the value of ab(i,j)
            for(k = 0; k < n_column; k++){
                sum += (*(A + i*n_row + k)) * (*(B + k*single + j));
            }
            *(result + i*single + j) = sum;//assign the value to ab(i,j)
            //printf("result = %lf\n\n",*(result + i*single + j));
            sum = 0;//reset the sum for next calculating
        }

    }
    return result;
}

/***********************************************************
Function Name: CopyToColumn
Function Description: copy one column of a matrix to a vector.
Inputs:The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too.
            the matrix is a matrix. the j is matrix's j column will be copied to B.
Outputs: There are no argument need to be return.
Notes:
************************************************************/
void CopyToColumn(int n_row, int n_column, double *matrix, int j, double *B)
{
    int i;
    //for each row, find the jth number.
    for(i = 0; i < n_row; i++){
        *(B+i) = *(matrix + i*n_row + j);
    }
}

/***********************************************************
Function Name: CopyToMatrix
Function Description: copy one column of a matrix to a vector.
Inputs:The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too.
            the matrix is a matrix. the j is matrix's j column will be assigned from B.
Outputs: There are no argument need to be return.
Notes:
************************************************************/
void CopyToMatrix(int n_row, int n_column, double *X, int j,double *matrix)
{
    int i;
    //for each row, change the jth element.
    for(i = 0; i < n_row; i++){
        *(matrix + i*n_row + j) = *(X+i);
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
    double sum_0i = 0;//the sum of l(i,j)*y(j), j is from 0 to i.
    for(i = 0; i < n_column; i++){
            //get the sum
        for(j = 0; j < i; j++){
            sum_0i += *(L + a_mn - 1) * (*(Y+ j));
        }
    //solve the Y(i)
        *(Y + i) = (*(B + i) - sum_0i) / *(L + i*n_column + i);//calculate the solution of Y_i
        sum_0i = 0;//reset the sum for next calculation
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
    double sum_iend = 0;//the sum of u(i,j)*x(j), j is from end to i.
    for(i = n_row - 1; i >= 0; i--){
            //calculate the sum
        for(j = n_column - 1; j > i; j--){
            sum_iend += *(U + a_mn - 1) * (*(X+ j));
        }
    //calculate the X(i)
        *(X + i) = (*(Y + i) - sum_iend) / *(U + i*n_column + i);//calculate the solution of Y_i
        sum_iend = 0;//reset the sum for next calculation
    }
    printf("X= ");
    PrintMatrix(n_row, 1, X);
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
        //if the matrix is a 1*1 dimension matrix. There are no need to be factorized.
        if(n_row == 1){
            return;
        }
        //if the matrix need to be factorized.
        for(j = i; j < n_row - 1; j++){
                //find the coefficient for interchange
            coe = -(*(matrix  + i + (j+1)*n_column) / (*(matrix + i * n_column + i)) );
            //printf("coe = %lf\n",coe);
            for(k = 0; k + i < n_column; k++){
                //interchange the matrix and identical matrix to get the U and P
                *(matrix + a_jk) = *(matrix + i * n_column +i + k) * coe + (*(matrix + a_jk));
                *(idmatrix + a_jk) = *(idmatrix + i * n_column + i + k) * (-coe) + (*(idmatrix  + a_jk));
            }
        }
    }
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
    int i, j;//for counting
    int mark;//save the line which will interchange with current line.
    int fc;//just for interchange two lines of a matrix

    for(i = 0; i < n_column; i++){
//**************************************************************************************
            //for each row,you'll find the most max element of i column
            //in this section, the max will be founded and the line will be marked
            maxium = *(matrix + i*n_column + i);
            mark = i;
            for(j = i+1; j < n_row; j++){//from i line to row-1 line
                if(fabs(maxium) < fabs(*(matrix+j*n_row+i))){//if the max is samller than a(j,i)
                    //printf("j = %d\t maxium = %lf\t*(matrix+j*n_row+i) = %lf\n",j,maxium,*(matrix+j*n_row+i));
                    maxium = *(matrix+j*n_row+i);//assign the max from a(j,i)
                    mark = j;//the j line will be marked
                }
            }
            //printf("\nmax = %lf\n",maxium);
            //printf("\nthe %d line need to interchange with %d line\n",i+1,mark+1);
            //there are need to interchange with itself.
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
            //To make the P.
            for(fc = 0; fc < n_column; fc++){
                *(temp+fc) = *(P+mark*n_row+fc);//put a(mk,fc) in cache t(fc)
                *(P+mark*n_row+fc) = *(P+i*n_row+fc);//a(mk,fc) = a(i,fc)
                *(P+i*n_row+fc) = *(temp +fc);//a(i,fc)=t(fc)
            }
            //PrintMatrix(n_row,n_column,matrix);
//*********************************************************************
    }

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
void GSIter4tri(int n_row, int n_column, double *A, double *B, double *X)
{
    int i,j,k,single = 1;
    double sum,tol = 0.000000001,err;
    double *te;//cache for the older solution
    double a[5]={0};
    PrintMatrix(n_row,n_column,A);
    te = InitX(n_row,single,te);
    //the circle will be ended while the error<tolerance
    do{
        for(k = 0;k < n_column;k++){
            *(te+k) = *(X+k);
        }
        //calculate the sum
        for(i = 0; i < n_row; i++){
            for(j = i-1; j < i+2; j++){
                    if((j>=0)&&(j<n_column)&&(j != i) ){
                        sum += *(X + j) * (*(A + i*n_column + j));
                    }
            }
        //calculate the X(i)
            *(X + i) = ((*(B + i)) - sum) / (*(A + i*n_column + i));
            sum = 0;
        }
        err = 0;
        //calculate the error
        for(k = 0;k < n_column;k++){
            err += fabs(*(X+k)-*(te+k));
        }

    }while(err > tol);
    printf("X = ");
    PrintMatrix(n_row, 1, X);
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
void GSIter4all(int n_row, int n_column, double *A, double *B, double *X)
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
#endif // ALLMATRIX_H_INCLUDED
