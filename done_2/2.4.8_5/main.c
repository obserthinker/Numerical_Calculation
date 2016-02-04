/*������ 9.28.14��*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//f()Ϊ����⺯������Ϊ����ֵ
double f(double x);
//����f_d()Ϊ����⺯���ĵ�������Ϊ����ֵ
double f_d(double x);
//����ac_nt_rps()Ϊ����ţ��-����ɭ�㷨����
void ac_nt_rps();

int main()
{
    //freopen("out.txt","w",stdout);
    //�������ţ��-����ɭ�㷨����
    ac_nt_rps();
    return 0;
}

void ac_nt_rps()
{
    //M��P�ֱ�Ϊ�������Ľ����Ӧ�ĸ�
    double M;
    double p;
    //nͳ�Ƶ�������
    int n = 0;
    //���������Ľ�
    printf("order M = ");
    scanf("%lf",&M);
    //����������ĳ�ʼֵ
    printf("start with p0 = ");
    scanf("%lf",&p);

    //����
    printf("��ʼ������\n");
    while(f(p) != 0 && n<200){//����������ֵ�����������ʱ��
        //����ʹ�ã������ǰ����ֵ�Լ�����ֵ
        printf("f(%f) = %.10f\n",p,f(p));
        //����ţ��-����ɭ������ʽ����������ֵ
        //��ţ�ٵ������Ƚ�ʹ��
        //printf("�������㣺%.25f = %.15f-%f/%f\n",p - (f(p))/f_d(p),p,f(p),f_d(p));
        p = p - (f(p))/f_d(p);
        //��ţ�ٵ������Ƚ�ʹ��
        //printf("����֮��f(%f) = %.10f\n",p,f(p));
        n++;//ÿ�ε���֮��n+1
        //printf("��%d�ε���\n",n);
        //����ʹ�ã�����ÿ��������ĺ���ֵ
        //getchar();
    }
    printf("��������\n");
    //�����
    printf("��������n=%d\n",n);
    printf("anser:p = %f",p);
}

double f(double x)
{
    //�ֱ�Ϊ�����һ�⡢�ڶ��⡢������ĺ���ֵ
    //return ( pow((x - 2),5) );
    //return ( sin(pow(x,3)) );
    return ( (x-1)*log(x) );
}

double f_d(double x)
{
    //�ֱ�Ϊ�����һ�⡢�ڶ��⡢������ĵ�����ֵ
    //return (5 * pow(x - 2,4));
    //return (3 * pow(x,2) * cos(pow(x,3)));
    return (log(x) + (x - 1)/x);
}
