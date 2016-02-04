#ifndef LAGRANGE_H_INCLUDED
#define LAGRANGE_H_INCLUDED
/***********************************************************
Module Name: Lagrange.h
Module Date: 10/29/14
Module Auth: Xuanyu Wang
Description: For Lagrange Polynomial approximation.
Revision History:
Date Rel Ver. Notes
month/day/year x.x [e.g.] Module created
***********************************************************/

/*---------Structures and Typedefs-------*/
struct Nodes
{
    int num;//the number of nodes
    double *node;//the value of node
    double *node_value;//the value of f(node)
};
typedef struct Nodes Nodes;

struct Vec
{
    int num;//the number of vector's elements
    double *v;//the value of vector's element
};
typedef struct Vec Vec;


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
 Function Name: CalcuCoef(Vec *coe, Nodes* nd)
 Function Description: calculate the coefficient of P_k.
Inputs: need the point of Nodes and Vec, and the point had been initialized in function
                InitNodesInfo(Nodes* nd).
 Outputs: No output
************************************************************/
void CalcuCoef(Vec *coe, Nodes* nd)
{
    int i, j;
    //allocate the room of the coe->v
    coe->v = (double*)malloc(nd->num * sizeof(double));
    //assign the value of coe->num
    coe->num = nd->num;

//for every coefficient, for example coe_i, you need to
//calculate the sum of (x_i-x_k), and the k from 0 to N but k != i
    for(i = 0; i < nd->num; i++){
        //initialize the value of every coefficient
        *((coe->v)+i) = 1;
        for(j = 0; j < nd->num; j++){
            if(j != i){
                //calculate x_i-x_k
                *((coe->v)+i) *= (*((nd->node)+i) - *((nd->node)+j));
            }
        }
        //coefficient = y_i/sum
        *((coe->v)+i) = *((nd->node_value)+i) / *((coe->v)+i);
    }
}

/***********************************************************
 Function Name: CalcuNumerator(Vec *nmrt, Nodes *nd,double unknown)
 Function Description: calculate the value of numerator for every P_k.
Inputs: need the point of Nodes and Vec, and the point had been initialized in function
                InitNodesInfo(Nodes* nd). And a double number as unknown.
 Outputs: No output
************************************************************/
void CalcuNumerator(Vec *nmrt, Nodes *nd,double unknown)
{
    int i,j;
    //allocate the room and assign the value
    nmrt->v = (double*)malloc(nd->num * sizeof(double));
    nmrt->num = nd->num;

//for every numerator, for example nmrt_i, you need to
//calculate the sum of (unknown-x_k), and the k from 0 to N but k != i
    for(i = 0; i < nd->num; i++){
        //initialize the value of every coefficient
        *((nmrt->v)+i) = 1;
        for(j = 0; j < nd->num; j++){
            if(j != i){
                    //the sum of (unknown-x_k)
                *((nmrt->v)+i) *= (unknown - *((nd->node)+j));
            }
        }
    }

}

/***********************************************************
 Function Name: ShowVector(Vec *vec)
 Function Description: display the vector's info.
Inputs: need the point of Vec, and the point had been initialized.
 Outputs: No output
************************************************************/
void ShowVector(Vec *vec)
{
    int i;
    //for every display the number of it and the value of it.
    for(i = 0; i < vec->num; i++){
        printf("The No.%d value is :%lf \n", i, *((vec->v)+i));
    }
}

/***********************************************************
 Function Name: LrVal(Vec* coe,Vec* nmrt,Vec* reser)
 Function Description: calculate the subs of the unknown.
Inputs: need the point of Vecs, and the point had been initialized.
        the first argument is the coefficient of P_k,the 2ed is the numerator
        of P_k, the reser is the result of coefficient*numerator of P_k.
 Outputs: No output
************************************************************/
void LrVal(Vec* coe,Vec* nmrt,Vec* reser)
{
    int i, n;
    double temp = 0;
    n = coe->num;
    //initialize the reser
    reser->v =  (double*)malloc(n * sizeof(double));
    reser->num = n;
    //calculate the value of coefficient*numerator for P_k
    //the sum of reser is the result
    for(i = 0; i < n; i++){
        *((reser->v)+i) = *((nmrt->v)+i) * *((coe->v)+i);
        temp += *((reser->v)+i);
    }
    printf("the result is : %lf\n",temp);
}

/***********************************************************
 Function Name: ShowPoly(Vec *coe, Vec* nmrt, Nodes* nd)
 Function Description: display the polynomial.
Inputs: need the point of Vecs, and the point had been initialized.
        the first argument is the coefficient of P_k,the 2ed is the numerator
        of P_k, the 3rd is the info of nodes.
 Outputs: No output
************************************************************/
void ShowPoly(Vec *coe, Vec* nmrt, Nodes* nd)
{
    int i, n, j;
    n = coe->num;

//diaplay P_i
    for(i = 0; i < n; i++){
        //print the coefficient of P_i
        printf("%lf",*((coe->v)+i));
        //print every linear factor of P_i
        for(j = 0; j < n; j++){
            if(j != i){
                printf("*(x-%lf)",*((nd->node)+j));
            }
        }
        printf("\n");
        //if the next coefficient is negative, there no need for "+"
        if(*((coe->v)+i+1) > 0 && i +1 < n)printf("+");
    }
}


#endif // LAGRANGE_H_INCLUDED
