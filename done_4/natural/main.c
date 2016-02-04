#include <stdio.h>
#include <stdlib.h>
#include "operation.h"


int main()
{
    freopen("last_experience10.txt","r",stdin);
    freopen("last_experience_out10.txt","w",stdout);
    //freopen("in.txt","r",stdin);

/************变量声明区*********************************/
    //h 代表自变量之间的间距。 h_n=x_(n+1)-x(n)
    //d 表示相邻两点之之间的斜率。d_n=(y_(n+1)-y_n)/h_n
    //m 代表在某点处的二次导数值
    //u 代表解m的方程组时等号右边的数。u_n=6(d_(n+1)-d_n)
    vector *d, *h, *m, *u;
    //Xnode, Ynode代表已知点的横、纵坐标值。
    vector *Xnode, *Ynode;
    //S 为二重指针，存储多项式系数。
    double **S;
    //ds_a、ds_b 分别表示左、右端点出的一次导数值
    double ds_a = -7;
    double ds_b = 0.5;
    int i;
/*--initialize the vectors--*/
    d = init_vector(d,0);
    h = init_vector(h,0);
    m = init_vector(m,0);
    u = init_vector(m,0);
    Xnode = init_vector(Xnode,1);
    Ynode = init_vector(Ynode,1);
    ShowVector(Xnode);
    ShowVector(Ynode);
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

/*--using Gauss-Seidel iteration to solve the equation HM=V--*/
    calcu_m(m,d,u,h,Xnode,ds_a,ds_b);
    *(m->value+0) = 0;
    *(m->value+Xnode->N - 1) = 0;
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
