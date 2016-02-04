#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

/***********************************************************
Module Name: operation.h
Module Date: 11/15/14
Module Auth: Xuanyu Wang
Description: all operation needed in this question.
***********************************************************/
/*----------------Includes---------------*/
#include <math.h>
/*---------Structures and Typedefs-------*/
struct Vector
{
    int num;
    double *value;
};
typedef struct Vector vector;
/*---------------Defines-----------------*/
#define a_mn (i * n_column + j +1)//a(m,n) is the true serial number of the element
#define a_jk ((j+1)*n_column+i+k)//the i+(j-i+1) line, i+k column element. i.e.
#define B 3.267
#define D -0.606


/***********************************************************
Function Name: InitVector
Function Description: Initialize the variable of vector.
Inputs: Need a point of variable Vector. And a sign jud to judge which kind
           of initializtion will be used.
Outputs: None
************************************************************/
void InitVector(vector *Vec,int jud)
{
	int i;
		//Get the number of elements of vector
	printf("Input the Number of Node:\n");
	scanf("%d", &(Vec->num));
		//initialize the vector's elements
	Vec->value = malloc((Vec->num)*sizeof(double));
    //assign the value of vector's elements'
	//There are two modes. if jud=1, get values from stdin
	//if jud=0. assign 0 to all elements' value.
	for (i = 0; i < Vec->num; i++){
		if (jud == 1){
				printf("Input the No.%d's value:", i + 1);
				scanf("%lf", Vec->value + i);
			}
		else{
			*(Vec->value + i) = 0;
		}
	}
}

/***********************************************************
 Function Name: ShowVector(Vec *vec)
 Function Description: display the vector's info.
Inputs: need the point of Vec, and the point had been initialized.
 Outputs: No output
************************************************************/
void ShowVector(vector *vec)
{
    int i;
    //for every display the number of it and the value of it.
    for(i = 0; i < vec->num; i++){
        printf("The No.%d value is :%lf \n", i, *((vec->value)+i));
    }
}

/***********************************************************
Function Name:Sum
Function Description: the sum of all elements
Inputs: Need a point of variable Vector.
Outputs: return the result as double
************************************************************/
double sum_vector(vector *Vec)
{
    int i,n;
    n=Vec->num;
    double sum=0;
    for(i=0;i<n;i++){
        sum += fabs(*(Vec->value+i));
    }
    return sum;
}
/***********************************************************
Function Name:calcu_coe
Function Description: In this case, there are 9 elements in matrix.
            this function calculate every element.
Inputs: Need three points of variable Vector. matrix, x, y.
Outputs: return the point of matrix as vector.
************************************************************/
vector* calcu_coe(vector* matrix, vector* x, vector* y)
{
    //the matrix is a symmetrical matrix, so there are elements pairs.
    matrix->value = malloc(9 * sizeof(double));
    calcu_coe0(matrix->value+0,x,y);
    calcu_coe1(matrix->value+1,x,y);
    calcu_coe2(matrix->value+2,x,y);
    *(matrix->value+3) = *(matrix->value+1);//(2,1)=(1,2)
    calcu_coe4(matrix->value+4,x,y);
    calcu_coe5(matrix->value+5,x,y);
    *(matrix->value+6) = *(matrix->value+2);//(3,1)=(1,3)
    *(matrix->value+7) = *(matrix->value+5);//(3,2)=(2,3)
    calcu_coe8(matrix->value+8,x,y);

    return (matrix);
}
/***********************************************************
Function Name:calcu_Q
Function Description: In this case, there are 3 elements in matrix Q.
            this function calculate every element of Q.
Inputs: Need three points of variable Vector. Q, x, y.
Outputs: return the point of matrix as vector.
************************************************************/
vector* calcu_Q(vector* Q, vector* x, vector* y)
{
    Q->value = malloc(3 * sizeof(double));
    calcu_Q0(Q->value+0,x,y);
    calcu_Q1(Q->value+1,x,y);
    calcu_Q2(Q->value+2,x,y);
    return Q;
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
            printf("%f   ",*(matrix + i * n_column + j));//attention:the format should adjust when you need
        }
        printf("\n");
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
Function Name: AB
Function Description: to calculate the result of A times B
Inputs:  The first is the number of A's row. It should be a positive int.
            The second is the number of the A's column and it should be positive int,too. The third
            is the number of the B's column. The forth is matrix A and the fifth is matrix B
Outputs: Return the result of A*B.
Notes:The function assume A's column is equal with B's row.
************************************************************/
double* AB(int n_row, int n_column, int single, double *A, double *Q)
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
                sum += (*(A + i*n_row + k)) * (*(Q + k*single + j));
            }
            *(result + i*single + j) = sum;//assign the value to ab(i,j)
            //printf("result = %lf\n\n",*(result + i*single + j));
            sum = 0;//reset the sum for next calculating
        }

    }
    return result;
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
Function Name: BackSub4Y
Function Description: solve the Y in LY=B.
Inputs:The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too.
Outputs: There are no argument need to be return.
Notes:
************************************************************/
void  BackSub4Y(int n_row, int n_column, double *L, double *Y, double *Q)
{
    int i = 0, j = 0;
    double sum_0i = 0;//the sum of l(i,j)*y(j), j is from 0 to i.
    for(i = 0; i < n_column; i++){
            //get the sum
        for(j = 0; j < i; j++){
            sum_0i += *(L + a_mn - 1) * (*(Y+ j));
        }
    //solve the Y(i)
        *(Y + i) = (*(Q + i) - sum_0i) / *(L + i*n_column + i);//calculate the solution of Y_i
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
Function Name:calcu_coe0
Function Description: calculate the (1,1)of the matrix
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_coe0(double* coe, vector* x,vector *y)
{
    int i;
    *coe = 0;
    for(i = 0; i < x->num; i++){
        *coe += pow(cos(B* (*(x->value+i)) ), 2);
    }
}
/***********************************************************
Function Name:calcu_coe1
Function Description: calculate the (1,2)of the matrix
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_coe1(double* coe, vector* x,vector *y)
{
    int i;
    *coe = 0;
    for(i = 0; i < x->num; i++){
        *coe += cos(B * (*(x->value+i)) ) * sin(D * (*(x->value+i)) );
    }
}
/***********************************************************
Function Name:calcu_coe2
Function Description: calculate the (1,3)of the matrix
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_coe2(double* coe, vector* x,vector *y)
{
    int i;
    *coe = 0;
    for(i = 0; i < x->num; i++){
        *coe += cos(B * (*(x->value+i)) );
    }
}
/***********************************************************
Function Name:calcu_coe4
Function Description: calculate the (2,1)of the matrix
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_coe4(double* coe, vector* x,vector *y)
{
    int i;
    *coe = 0;
    for(i = 0; i < x->num; i++){
        *coe += pow(sin(D * (*(x->value+i)) ), 2);
    }
}
/***********************************************************
Function Name:calcu_coe5
Function Description: calculate the (2,3)of the matrix
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_coe5(double* coe, vector* x,vector *y)
{
    int i;
    *coe = 0;
    for(i = 0; i < x->num; i++){
        *coe += sin(D * (*(x->value+i)) );
    }
}
/***********************************************************
Function Name:calcu_coe8
Function Description: calculate the (3,3)of the matrix
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_coe8(double* coe, vector* x,vector *y)
{
    int i;
    *coe = 0;
    for(i = 0; i < x->num; i++){
        *coe += 1;
    }
}
/***********************************************************
Function Name:calcu_coeQ0
Function Description: calculate the (1,1)of the Q
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_Q0(double* coe, vector* x, vector* y)
{
    int i;
    *coe = 0;
    for(i = 0; i< x->num; i++){
        *coe += cos(B * *(x->value+i)) * *(y->value+i);
    }
}

/***********************************************************
Function Name:calcu_coeQ1
Function Description: calculate the (2,1)of the Q
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_Q1(double* coe, vector* x, vector* y)
{
    int i;
    *coe = 0;
    for(i = 0; i< x->num; i++){
        *coe += sin(D * *(x->value+i)) * *(y->value+i);
    }
}

/***********************************************************
Function Name:calcu_coeQ2
Function Description: calculate the (3,1)of the Q
Inputs: Need three variables. coe, x, y. coe is a point of double.
        x,y are points vector.
Outputs: None
************************************************************/
void calcu_Q2(double* coe, vector* x, vector* y)
{
    int i;
    *coe = 0;
    for(i = 0; i< x->num; i++){
        *coe += *(y->value+i);
    }
}
#endif // OPERATION_H_INCLUDED
