/*������ 9.28.14 ��*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//����nt_rps()Ϊţ��-����ɭ�㷨����
void nt_rps();
//f(),f_d(),r()�ֱ�Ϊ������ֱ������١���ֱ���򵼺�����ֵ��ˮƽ�����г�
double f(double t);
double f_d(double t);
double r(double t);

int main()
{
    freopen("out.txt","w",stdout);
    //����ţ��-����ɭ�㷨
    nt_rps();
    return 0;
}

void nt_rps()
{
    //tΪʱ�䣬Ԥ����ʼֵΪ5
    double t = 5;
    double temp = 0;
    double err = 0;
    //tolΪ������̷�Χ
    double tol;
    //printf("f(5) = %.10f\n",f(5));
    tol = 1E-10;

    //����
    do{//���������������̷�Χ��������
        //ţ��-����ɭ������ʽ
        printf("%.12f\n",err);
        //printf("�������㣺%.15f = %.15f-%f/%f\n",t - f(t)/f_d(t),t,f(t),f_d(t));
        temp = t - f(t)/f_d(t);
        err = fabs(temp - t);
        t = temp;
        //����ʹ�ã��۲��������ֵ�Լ�����ֵ
        //printf("f(%.10f) = %.10f\n",t,f(t));

    }while(err >= tol);
    //���������������
    printf("\nans: f(%.10f) = %.10f\nr(t) = %.10f",t,f(t),r(t));
}

double f(double t)
{
    //����y����߶�
    return ( 9600 * (1 - exp((-t) / 15)) - 480*t );
}

double f_d(double t)
{
    //����y�����˶����̵ĵ�����ֵ
    return ( 640 * (exp((-t) / 15)) - 480 );
}

double r(double t)
{
    //����x�����˶��г�
    return ( 2400 * (1 - exp((-t) / 15) ) );
}
