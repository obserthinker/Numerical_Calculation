#include <stdio.h>
#include <stdlib.h>
#include "operation.h"


int main()
{
    freopen("last_experience10.txt","r",stdin);
    freopen("last_experience_out10.txt","w",stdout);
    //freopen("in.txt","r",stdin);

/************����������*********************************/
    //h �����Ա���֮��ļ�ࡣ h_n=x_(n+1)-x(n)
    //d ��ʾ��������֮֮���б�ʡ�d_n=(y_(n+1)-y_n)/h_n
    //m ������ĳ�㴦�Ķ��ε���ֵ
    //u �����m�ķ�����ʱ�Ⱥ��ұߵ�����u_n=6(d_(n+1)-d_n)
    vector *d, *h, *m, *u;
    //Xnode, Ynode������֪��ĺᡢ������ֵ��
    vector *Xnode, *Ynode;
    //S Ϊ����ָ�룬�洢����ʽϵ����
    double **S;
    //ds_a��ds_b �ֱ��ʾ���Ҷ˵����һ�ε���ֵ
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
