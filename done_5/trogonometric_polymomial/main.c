#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#define PI 3.1415926

int main()
{
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    vector *node_x, *node_y, *X4coe;
    vector *coe_a, *coe_b;
/*--initialize the variables--*/
    node_x = init_vector(node_x,1);
    node_y = init_vector(node_y,1);
    coe_a = init_vector(coe_a,0);
    coe_b = init_vector(coe_b,0);
    X4coe = change_nodex2X(node_x,X4coe);

/*--calculate the coefficients of polynomial--*/
    calcu_coe_a(coe_a,X4coe,node_y);
    printf("coe_a:\n");
    ShowVector(coe_a);

    calcu_coe_b(coe_b,X4coe,node_y);
    printf("coe_b:\n");
    ShowVector(coe_b);
/*--display the polynomial--*/
    show_polynomial(coe_a,coe_b);
    return 0;
}
