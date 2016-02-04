#ifndef NEWTON_H_INCLUDED
#define NEWTON_H_INCLUDED
/***********************************************************
Module Name: Newton.h
Module Date: 10/29/14
Module Auth: Xuanyu Wang
Description: Use Newton approximation method.
Revision History:
Date Rel Ver. Notes
month/day/year x.x [e.g.] Module created
***********************************************************/
/*----------------Includes---------------*/
#include <math.h>
/*---------Structures and Typedefs-------*/
struct Vec
{
    int num;//the number of vector's elements
    double *v;//the value of vector's element
};
typedef struct Vec Vector;
struct Nodes
{
    int num;//the number of nodes
    double *node;//the value of node
    double *node_value;//the value of f(node)
};
typedef struct Nodes Nodes;

/***********************************************************
 Function Name: InitNodesInfo(Nodes* nd)
 Function Description: assign the number of nodes. assign every node's info include
                                    node's value and the value of f(node)
Inputs: need the point of Nodes, and the point had been allocated room/
 Outputs: No output
************************************************************/
void InitNodesInfo(Nodes* nd)
{
    int i;

    printf("Please input the number of nodes you have:");
    scanf("%d", &(nd->num));//get the number of nodes
    printf("nd->num = %d\n",nd->num);//verify the number
    //allocate the room for node and it's value
	nd->node = (double*)malloc(nd->num * sizeof(double));
    nd->node_value = (double*)malloc(nd->num * sizeof(double));
    //assign the node's value and f(node)'s value
	for (i = 0; i < nd->num; i++){
		printf("the NO.%d node and it's value are:",i);
		scanf("%lf%lf", (nd->node + i),(nd->node_value + i));
	}
}

/***********************************************************
 Function Name: ShowNodesInfo(Nodes* nd)
 Function Description: display the info of Nodes,including  the number of nodes, every node's info include
                                    node's value and the value of f(node)
Inputs: need the point of Nodes, and the point had been initialized in function
                InitNodesInfo(Nodes* nd)
 Outputs: No output
************************************************************/
void ShowNodesInfo(Nodes* nd)
{
    int i;
    printf("nd->num = %d\n",nd->num);
    //display the info of each node.
	for (i = 0; i < nd->num; i++){
		printf("the NO.%d node and it's value are :\t%lf\t%lf:\n", i, *((nd->node)+i),*(nd->node_value+i));
	}
}

/***********************************************************
 Function Name: ShowNodesInfo(Nodes* nd)
 Function Description: calculate the divided difference.
Inputs: need the point of Nodes and double**. points had been
                initialized in function InitNodesInfo(Nodes* nd)
 Outputs: No output
************************************************************/
void CalcuDD(double** DD,Nodes* nd)
{
    int i, n, j;
    n = nd->num;
    for(i = 0; i < n; i++){
            //allocate the room
        *(DD+i) = (double*)malloc((n-i)*sizeof(double));
        for(j = 0; j < n-i; j++){
            //the first-order divided difference would be assigned directly
            if(i == 0){
                *(*(DD+i)+j) = *((nd->node_value)+j);
            }
            //other divided difference would be calculated
            else{
                *(*(DD+i)+j) = (*(*(DD+i-1)+j+1) - *(*(DD+i-1)+j)) / (((nd->node)+i+i+j)-((nd->node)+i+j));
            }
        }
    }
}

/***********************************************************
 Function Name: ShowDDtable(double **DD,Nodes *nd)
 Function Description: display the divided difference table.
Inputs: need the point of Nodes and double**. points had been
            initialized in function InitNodesInfo(Nodes* nd).
 Outputs: No output
************************************************************/
void ShowDDtable(double **DD,Nodes *nd)
{
    int i, n, j;
    n = nd->num;
    for(i = 0; i < n; i++){
        for(j = 0;j<n-i;j++){
            printf("No.(%d,%d) = %.1lf\t\t",i, j, *(*(DD+i)+j));
        }
        printf("\n");
    }
}

/***********************************************************
 Function Name: InitCoe(double **DD, Vector *coe, Nodes *nd)
 Function Description: As we had divided difference table,
                    we can assign a_k.
Inputs: need the point of Nodes and double**. points had been
            initialized in function InitNodesInfo(Nodes* nd).
            the coe is used to save coefficient.
 Outputs: No output
************************************************************/
void InitCoe(double **DD, Vector *coe, Nodes *nd)
{
    int i;
    //initialize the coe
    coe->num = nd->num;
    coe->v = malloc((coe->num)*sizeof(double));
    //assign value to a_k
    for(i = 0; i < coe->num; i++){
        *((coe->v) + i) = *(*(DD+i)+0);
    }
}

/***********************************************************
 Function Name: ShowVector(Vec *vec)
 Function Description: display the vector's info.
Inputs: need the point of Vec, and the point had been initialized.
 Outputs: No output
************************************************************/
void ShowVector(Vector *vec)
{
    int i;
    //for every display the number of it and the value of it.
    for(i = 0; i < vec->num; i++){
        printf("The No.%d value is :%lf \n", i, *((vec->v)+i));
    }
}
/***********************************************************
Function Name: ShowPoly(Vector *coe, Nodes *nd)
Function Description: display the polynomial.
Inputs: need the point of Nodes, and the point had been initialized.
            need the point of coe, and the point had been initialized.
Outputs: No output
************************************************************/
void ShowPoly(Vector *coe, Nodes *nd)
{
    int i, n, j;
    n = nd->num;
    for(i = 0; i < n; i++){
        //the 1st coefficient and the negative coefficient don;t need '+'
        if(i != 0 && *((coe->v)+i) > 0){
            printf("+");
        }
        //0 don't need to output
        if(*((coe->v)+i) != 0){
            printf("%lf",*((coe->v)+i));
            //for node which is negative don't need '+'
            for(j = 0; j < i; j++){
                //some number is too little might can't judge whether it's
                //positive or negative.
                if(*((nd->node)+j)*1000 >= 0){
                    printf("*(x-%lf)",*((nd->node)+j));
                }
                else if(*((nd->node)+j)*1000 < 0){
                    printf("*(x%lf)",-*((nd->node)+j));
                }
            }
        }
        if(*((coe->v)+i+1) != 0){
            //this section can show the polynomial in multiline
            //printf("\n");
        }
    }
}
/***********************************************************
Function Name: CalcuVal(Vector *coe, Nodes *nd,Vector *res, double unknown)
Function Description: the result of substitution of unknown.
Inputs: need the point of Nodes, and the point had been initialized.
            need the point of coe, and the point had been initialized.
            and need the unknown.
Outputs: No output
************************************************************/
void CalcuVal(Vector *coe, Nodes *nd,Vector *res, double unknown)
{
    int i, n, j;
    double test = 0, temp = 1;
    n = nd->num;

    res->v = malloc((res->num)*sizeof(double));
    for(i = 0; i < n; i++){
        temp *= *((coe->v)+i);
        for(j = 0; j < i; j++){
            temp *= (unknown - *((nd->node)+j));
        }
        test += temp;
    }
    printf("result = %lf\n",test);
}

#endif // NEWTON_H_INCLUDED
