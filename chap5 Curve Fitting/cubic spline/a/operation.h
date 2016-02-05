#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
/***********************************************************
Module Name: operation.h
Module Date: 101/13/2014
Module Auth: Xuanyu Wang

Description: 包含三次紧压样条插值会用到的操作
Revision History: 第三次修改
***********************************************************/
/*----------------Includes---------------*/
//the head files that were included
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*---------Structures and Typedefs-------*/
struct v{
    int N;//包含变量的个数
    double *value;//变量值的指针
};
typedef struct v vector;

/*---------------Defines-----------------*/
#define a_mn (i * n_column + j +1)//a(m,n) is the true serial number of the element
#define a_jk ((j+1)*n_column+i+k)//the i+(j-i+1) line, i+k column element. i.e.


double* InitMatrix(int n_row,int n_column,double *matrix,int special);
double* TridiagMatrix(int n_row,int n_column,double *matrix,vector *h);
double* InitX(int n_row,int n_column,double *matrix);
void PrintMatrix(int n_row,int n_column,double *matrix);
double* AB(int n_row, int n_column, int single, double *A, double *B);
double* InitIdMatrix(int n_row,int n_column,double *idmatrix);

/***********************************************************
Function Name: InitVector
Function Description: Initialize the variable of vector.
Inputs: Need a point of variable Vector. And a sign jud to judge which kind
           of initializtion will be used.
Outputs: None
************************************************************/
vector* init_vector(vector *v,int jud)
{
    int i;//控制循环次数
    v = malloc(sizeof(vector));//分配内存
    v->value = malloc((v->N)*sizeof(double));
    //分情况初始化，判断依据为jud的值
    //第一种情况下所有元素数值为0
    if(jud==0){
        printf("Input the Number of Node:\n");
        scanf("%d",&(v->N));
        return v;
    }
    //第二种情况所有元素按照输入赋值
    if(jud==1){
        printf("Input the Number of Node:\n");
        scanf("%d",&(v->N));

        for(i = 0; i < v->N; i++){
            printf("Input No.%d's value: ",i);
            scanf("%lf",v->value+i);//赋值
        }
        return v;
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
    for(i = 0; i < vec->N; i++){
        printf("The No.%d value is :%lf \n", i, *((vec->value)+i));
    }
    printf("\n");
}

/***********************************************************
 Function Name: calcu_h
 Function Description: calculate the h_k for clamped cubic spline.
Inputs: h and X are points of vector. X is the node.
 Outputs: No output
************************************************************/
void calcu_h(vector *h,vector *X)
{
    int i;
    for(i = 0;i < h->N; i++){
        *(h->value + i) = *(X->value + i + 1) - *(X->value + i);
    }
}
/***********************************************************
 Function Name: calcu_d
 Function Description: calculate the d_k for clamped cubic spline.
Inputs: h ,Y and X are points of vector. X and Y are the nodes.
 Outputs: No output
************************************************************/
void calcu_d(vector *d, vector *X, vector *Y)
{
    int i;
    for(i = 0; i < d->N; i++){
        *(d->value + i) = (*(Y->value + i+1) - *(Y->value + i)) / (*(X->value + i+1) - *(X->value + i));
    }
}
/***********************************************************
 Function Name: calcu_u
 Function Description: calculate the u_k for clamped cubic spline.
Inputs: h ,u and X are points of vector. X is nodes.
 Outputs: No output
************************************************************/
void calcu_u(vector *d, vector *u, vector *X)
{
    int i;
    for(i = 1; i <= X->N - 2; i++){
        *(u->value+i) = 6 * (*(d->value+i) - *(d->value+i-1));
    }
}
/***********************************************************
 Function Name: calcu_S
 Function Description: calculate the S(i,j) for clamped cubic spline.
Inputs: h ,Y and d,m are points of vector.S is the point of double's point.
 Outputs: No output
************************************************************/
void calcu_S(double **S, vector *Y, vector *d, vector *h, vector *m)
{
    int i, j;
    for(i = 0; i < Y->N-1; i++){
        *(S+i) = malloc( 4 * sizeof(double));//分配内存
        //分别计算三次插值多项式的四个系数
        *(*(S+i)+0) = *(Y->value+i);
        *(*(S+i)+1) = *(d->value+i) - *(h->value+i) * (2* (*(m->value+i)) + *(m->value+i+1))/6;
        printf("%lf\t%lf\n",*(d->value+i),*(h->value+i)*(2* (*(m->value+i)) + *(m->value+i+1))/6);
        *(*(S+i)+2) = *(m->value+i)/2;
        *(*(S+i)+3) = (*(m->value+i+1)-*(m->value+i))/(6*(*(h->value+i)));
        //printf("%lf\t%lf\n",(*(m->value+i+1)-*(m->value+i)),(6*(*(h->value+i))));
    }
}

/***********************************************************
Function Name: calcu_m
Function Description: calculate the m_k for clamped cubic spline.
Inputs: m, d, u, h, X are points of vector. ds_a and ds_b is the difference of endpoint.
Outputs: No output
************************************************************/
void calcu_m(vector *m, vector *d, vector *u, vector *h, vector *Xnode,double ds_a,double ds_b)
{
    //matrix为系数矩阵
    //X为未知元矩阵
    //B为方程组等号右边矩阵
    //result为
    double *matrix, *X, *B,*result;
    //n_row, n_column分别代表矩阵的行、列数
    int n_row,n_column;
    //single符号代表1
    int single = 1;
    int i;//控制循环次数

    //设置矩阵规模
    n_row = (Xnode->N) - 2;
    n_column = (Xnode->N) - 2;

    //初始化各个矩阵
    matrix = InitMatrix(n_row,n_column,matrix,0);//produce a matrix
    X = InitX(n_row, single, X);
    B = InitMatrix(n_row, single, B,0);
    result = InitMatrix(n_row,single,result,0);

    //使用高斯-塞德尔迭代求解矩阵
    for(i = 0; i < n_row; i++){
        if(i == 0){
            printf("i=%d,in 1\n",i);
            *(B+i) = *(u->value+1) - 3*( *(d->value+0) -  ds_a);
        printf("B+%d=%lf\n",i,*(B+i));
            //printf("\n(%lf+1) - 3*( *(%lf+0) -  0.2) = %lf\n",*(u->value),*(d->value+0),*(B+i));
        }
        else if(1<=i || i<=n_row - 1){
            printf("i=%d,in 2\n",i);
            *(B+i) = *(u->value + i+1);
            printf("B+%d=%lf\n",i,*(B+i));
        }
        if(i == n_row - 1){
            printf("i=%d,in 3\n",i);
            *(B+i) = *(u->value+n_row) - 3*(ds_b - *(d->value+n_row));
            printf("B+%d=%lf\n",i,*(B+i));
        }

    }
    //printf("Matrix = ");
    //PrintMatrix(n_row,n_column,matrix);//display the matrix
    //printf("\nX = ");
    //PrintMatrix(n_row, single, X);
    //printf("\nB = ");
    //PrintMatrix(n_row, single, B);


    matrix = TridiagMatrix(n_row,n_column,matrix,h);//change the matrix into a tridiagonal matrix
    printf("\nTriMatrix = ");
    PrintMatrix(n_row,n_column,matrix);//display the matrix
    printf("\nB = ");
    PrintMatrix(n_row, 1, B);//display the matrix

    GSIter4tri(n_row, n_column,matrix, B, X);
    for(i = 1; i <= n_row; i++){
            *(m->value+i) = *(X+i-1);
    }
    //ShowVector(m);
    result = AB(n_row,n_column,single,matrix,X);
    PrintMatrix(n_row,single,result);
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
    double coun = 0;//initialize the matrix's value
    for(i = 0;i < n_row;i++){//for row
        for(j = 0;j < n_column;j++){//for column
            *(matrix + i* n_column + j ) = coun;//give a(i+1,j+i) a value
        }
    }
    return (matrix);
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
            printf("%.3lf   ",*(matrix + i * n_column + j));//attention:the format should adjust when you need
        }
        printf("\n");
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
    //PrintMatrix(n_row,n_column,A);
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
Function Name: TridiagMatrix
Function Description: Produce a matrix which is a tridiagonal matrix.
Inputs: Three argument are asked. The first is the number of row. It should be a positive int.
            The second is the number of the column and it should be positive int,too. The third
            is the point of the matrix and it should be double.
Outputs: Return a point of the matrix.
Notes: The matrix should be initialized.
************************************************************/
double* TridiagMatrix(int n_row,int n_column,double *matrix,vector *h)
{
    int i;//i is for counting
    for(i = 0;i < n_row;i++){
        //for the first row, we need two coefficients
        if((i + 1) == 1){
            printf("first row:input the coefficient of the a(%d,%d) & a(%d,%d):\n",1,1,1,2);
            //scanf("%lf %lf",matrix,(matrix+1));
            *(matrix) = 3*(*(h->value))/2 + 2*(*(h->value+1));
            *(matrix + 1) = *(h->value+1);
        }
        //for the last row, we need two coefficients
        else if((i + 1) == n_row){
            printf("input the coefficient of the a(%d,%d) & a(%d,%d):\n",n_row,n_row-1,n_row,n_row);
            //scanf("%lf %lf",matrix+n_row*n_column-2,matrix+n_row*n_column-1);
            *(matrix+n_row*n_column-2) = *(h->value+n_row-1);
            *(matrix+n_row*n_column-1) = 2 * (*(h->value+n_row-1)) + 3 * (*(h->value+n_row))/2;
        }
        //for each row except first and last need three coefficient
        else{
            printf("input the coefficient of the a(%d,%d) & a(%d,%d) & a(%d,%d):\n",i+1,i,i+1,i+1,i+1,i+2);
            //scanf("%lf %lf %lf",matrix+i*n_column+i-1,matrix+i*n_column+i,matrix+i*n_column+i+1);
            *(matrix+i*n_column+i-1) = *(h->value+i);
            *(matrix+i*n_column+i) = 2*(*(h->value+i) + *(h->value+i+1));
            *(matrix+i*n_column+i+1) = *(h->value+i+1);
        }
    }
    return (matrix);//return the point of one-dimension array
}


#endif // OPERATION_H_INCLUDED
