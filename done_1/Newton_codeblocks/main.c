#include <stdio.h>
#include <stdlib.h>
#include "Newton.h"

int main()
{
    freopen("in.txt","r",stdin);
    //freopen("test1.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Nodes *nd;
    double **DD;
    double unknown;
    Vector *coe;
    Vector *res;
    nd = malloc(sizeof(Nodes));
    coe = malloc(sizeof(Vector));
    res = malloc(sizeof(Vector));

    InitNodesInfo(nd);
    ShowNodesInfo(nd);

    DD = malloc((nd->num)*sizeof(double*));
    CalcuDD(DD,nd);
    ShowDDtable(DD,nd);

    InitCoe(DD,coe,nd);
    ShowVector(coe);

    ShowPoly(coe,nd);

    //printf("Input the unknown:");
    //scanf("%lf", &unknown);
    unknown = 1;
    CalcuVal(coe,nd,res,unknown);
    return 0;
}
