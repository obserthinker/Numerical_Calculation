#include <stdio.h>
#include <stdlib.h>
#include "operation.h"


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("test.txt","r",stdin);
    //freopen("outin.txt","w",stdout);
    vector *d, *h, *m, *u;
    vector *Xnode, *Ynode;
    double **S;
    double ds_a = 0;
    double ds_b = 98;
    int i;
/*--initialize the vectors--*/
    d = init_vector(d,0);
    h = init_vector(h,0);
    m = init_vector(m,0);
    u = init_vector(m,0);
    Xnode = init_vector(Xnode,1);
    Ynode = init_vector(Ynode,1);
    S = malloc((Xnode->N-1) * sizeof(double*));
/*--calculate every element of every vector--*/
    calcu_h(h,Xnode);
    calcu_d(d,Xnode,Ynode);
    calcu_u(d,u,Xnode);
    printf("\nh\n");
    ShowVector(h);
    printf("\nd\n");
    ShowVector(d);
    printf("\nm\n");
    ShowVector(m);
    printf("\nu\n");
    printf("\nu\n");
    ShowVector(u);
    //ShowVector(X);
    //ShowVector(Y);
/*--using Gauss-Seidel iteration to solve the equation HM=V--*/
    calcu_m(m,d,u,h,Xnode,ds_a,ds_b);
    *(m->value+0) = (3 / *(h->value)) * (*(d->value) - ds_a) - *(m->value+1) / 2;
    *(m->value+Xnode->N - 1) = (3 / *(h->value+Xnode->N - 2)) * (ds_b - *(d->value+Xnode->N - 2)) - *(m->value+Xnode->N - 2) / 2;
    printf("\nm:\n");
    ShowVector(m);
/*--use what have calculated to calculate the coefficient of clamped cubic spline--*/
    calcu_S(S,Ynode,d,h,m);
/*--show the value of coefficients--*/
    for(i = 0; i < Ynode->N-1; i++){
        printf("%lf&\t%lf&\t%lf&\t%lf\n",*(*(S+i)+0),*(*(S+i)+1),*(*(S+i)+2),*(*(S+i)+3));
    }
    return 0;
}
