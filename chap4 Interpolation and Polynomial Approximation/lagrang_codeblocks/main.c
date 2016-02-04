#include <stdlib.h>
#include <stdio.h>
#include "Lagrange.h"

int main()
{
    freopen("in.txt","r",stdin);//get data from in.txt
    //freopen("out.txt","w",stdout);//print the result in out.txt
    Nodes* nd;//include nodes and all info of every node
    Vec *coe;//the coefficient of P_k
    Vec *nmrt;//the linear factor of P_k
    Vec *exam;//the data for testing
    Vec *results;//
    double unknown;//the value of unknown
    int i, n;//for counting
    nd = (Nodes*)malloc(sizeof(Nodes));//allocate the space for the nodes
    coe = (Vec*)malloc(sizeof(Vec));//allocate space for data
    nmrt = (Vec*)malloc(sizeof(Vec));//allocate space for data
    exam = (Vec*)malloc(sizeof(Vec));//allocate space for data
    results = (Vec*)malloc(sizeof(Vec));//allocate space for data

    //freopen("test.txt","r",stdin);
    InitNodesInfo(nd);//get the necessary data for every node
	ShowNodesInfo(nd);//display the info of every node
	n = nd->num;//for convinient, let the n represent the number of nodes

//for every unknown, calculate the result
    for(i = 0; i < n; i++){
        //printf("the unknown is :");
        //scanf("%lf", &unknown);
        unknown = *((nd->node)+i);

        CalcuCoef(coe,nd);//calculate the coefficient
        //printf("display the denominator\n");
        //ShowVector(coe);
        CalcuNumerator(nmrt,nd,unknown);//calculate the value of P_k
        //printf("display the numerator\n");
        //ShowVector(nmrt);

        LrVal(coe,nmrt,exam);//calculate the result, namely the sum of numerator*coefficient
}
    //printf("display the sum\n");
    //ShowVector(exam);
    //printf("examult = ")
    //ShowVector(exam);
    ShowPoly(coe,nmrt,nd);//display the polynomial
	return 0;
}
