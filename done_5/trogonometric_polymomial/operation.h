#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
/***********************************************************
Module Name: operation.h
Module Date: 101/13/2014
Module Auth: Xuanyu Wang

Description: To produce,display a matrix.
    Revision History: None
***********************************************************/
/*----------------Includes---------------*/
//the head files that were included
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.141592653589793

/*---------Structures and Typedefs-------*/
struct v{
    int N;
    double *value;
};
typedef struct v vector;

/*---------------Defines-----------------*/
//#define a_mn (i * n_column + j +1)//a(m,n) is the true serial number of the element
//#define a_jk ((j+1)*n_column+i+k)//the i+(j-i+1) line, i+k column element. i.e.

/***********************************************************
Function Name: InitVector
Function Description: Initialize the variable of vector.
Inputs: Need a point of variable Vector. And a sign jud to judge which kind
           of initializtion will be used.
Outputs: None
************************************************************/
vector* init_vector(vector *v,int jud)
{
    int i;
    v = malloc(sizeof(vector*));

    if(jud==0){
        //printf("Input the Number of Node:\n");
        scanf("%d",&(v->N));
        v->value = malloc((v->N)*sizeof(double));
        return v;
    }
    if(jud==1){
        //printf("Input the Number of Node:\n");
        scanf("%d",&(v->N));
        v->value = malloc((v->N)*sizeof(double));
        for(i = 0; i < v->N; i++){
            printf("Input No.%d's value: ",i);
            scanf("%lf",v->value+i);
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
        //printf("The No.%d value is :%lf \n", i, *((vec->value)+i));
                printf("$b_%d$ & %lf \\\\\n", i, *((vec->value)+i));
    }
    printf("\n");
}

/***********************************************************
 Function Name: change_nodex2X
 Function Description: change the x to x' to use trigonometric polynomial.
Inputs: node_x is the original value, and X is value had been mapped.
 Outputs: No output
************************************************************/
vector* change_nodex2X(vector *node_x, vector *X)
{
    int i;
    X = malloc(sizeof(vector*));
    X->N = node_x->N;
    X->value = malloc((X->N-1) * sizeof(double));
    for(i = 0;i < node_x->N; i++){
        *(X->value+i) = -PI + i*(2*PI)/(node_x->N-1);
    }
    return X;
}

/***********************************************************
 Function Name: calcu_coe_a
 Function Description: calculate the coefficients a_j of trigonometric polynomial
Inputs: X4coe is the value for trigonometric polynomial.
        coe_a is the coefficient of polynomial. node_y are value of f(x_k)
 Outputs: No output
************************************************************/
void calcu_coe_a(vector *coe_a,vector *X4coe, vector *node_y)
{
    int j, k,N;
    double sum = 0;
    N = X4coe->N-1;

    for(j = 0; j < coe_a->N; j++){
        sum = 0;
        for(k = 1; k <= N; k++){
            sum += *(node_y->value+k) * cos( j * (*(X4coe->value+k)));
            //if(j==0){
        //printf("sum+f(%d)*cos(%d*%lf)=%lf=%lf\n",k,j,*(X4coe->value+k),*(node_y->value+k) * cos( j * (*(X4coe->value+k))),sum);
            //}
        }
        //if(j==0){
            //sum+=*(node_y->value+0);
        //}
        *(coe_a->value+j) = (2* sum/N) ;
    }
    *(coe_a->value+0) /= 2;
}
/***********************************************************
 Function Name: calcu_coe_b
 Function Description: calculate the coefficients b_j of trigonometric polynomial
Inputs: X4coe is the value for trigonometric polynomial.
        coe_b is the coefficient of polynomial. node_y are value of f(x_k)
 Outputs: No output
************************************************************/
void calcu_coe_b(vector *coe_b,vector *X4coe, vector *node_y)
{
    int j, k,N;
    double sum = 0;
    N = X4coe->N-1;
    for(j = 1; j < coe_b->N; j++){
        sum = 0;
        for(k = 1; k <= N; k++){
            sum += *(node_y->value+k) * sin( j * (*(X4coe->value+k)));
             if(j==1){
        printf("sum+f(%d)*sin(%d*%lf)=%lf=%lf\n",k,j,*(X4coe->value+k),*(node_y->value+k) * sin( j * (*(X4coe->value+k))),sum);
            }
        }
        *(coe_b->value+j) = (2* sum/N) ;
    }
}
/***********************************************************
 Function Name: show_polynomial
 Function Description: display the polynomial
Inputs: coe_a and coe_b
 Outputs: No output
************************************************************/
void show_polynomial(vector *coe_a,vector *coe_b)
{
    int j;
    printf("\n%lf",*(coe_a->value) / 2);
    for(j = 1; j <= coe_b->N; j++){
        printf("+");
        printf("(%lf*cos(%d*x*pi/12) + (%lf)*sin(%d*x*pi/12))",*(coe_a->value+j),j,*(coe_b->value+j),j);
    }
}
#endif // OPERATION_H_INCLUDED
