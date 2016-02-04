/*������ 9.28.14 ��*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//����f()���������
double f(double rate);
//����bisevtion()����������ַ�
void bisection(double a0,double b0);

int main()
{
    //freopen("out.txt","w",stdout);
    //a,b�ֱ�Ϊ�������Ҷ˵�ֵ
    double a,b;
    //��ʼ���丳ֵ
    a = 0.14;
    b = 0.16;
    //������ַ���ʼ����
    bisection(a,b);

    return 0;
}

void bisection(double a,double b)
{
    //errΪ���
    double err;
    //tolΪ����ֵ���������Χ
    double tol = 1E-10;
    //cΪ�����е�
    double c;
    //��¼��������
    int n = 0;

    //ʹ��do...whileѭ�������һ��ѭ����Ҫ�ж�
    do{
        //���������е�
        c = (a+b)/2;
        //����ʹ�ã��۲����估���е�ȡֵ����������Ƿ�����ȷ
        //printf("a = %.10f\tb = %.10f\tc = %.10f\n",a,b,c);
        //printf("%.13f\n",b);
        //����������
        if(f(c) != 0){//�ж��е��ǲ�����㣬���ǵĻ������µ������������
            //����ʹ�á����c���ĺ���ֵ���Ƿ��������
            //printf("f(c) = %.10f\n",f(c));
            //�ж������[a,c]����[b,c]�У����������µ�����
            if(f(c) * f(a) > 0)a = c;
            else b = c;
            n++;
        }
        else break;//���c����㣬����ѭ��
        //�������
        err = fabs(b - a);
        printf("err = %.13f\n",err);
    }while(err >= tol);//����������Χ��ʱ���������
    //������
    printf("������%d��\n",n);
    printf("ans:rate = %.10f",c);
}

double f(double rate)
{
    //monthly��month��total�ֱ����½������������
    double monthly;
    double nmonth;
    double total;
    //r12�������湫ʽ�е�I/12���Ա�ʹ��ʽ����಻���׳���
    double r12;
    r12 = rate/12;
    //��ʼ����ֵ
    monthly = 300;
    nmonth = 240;
    total = 500000;
    //������𲢷���
    return (12*monthly/(rate))*( pow(1+r12,nmonth) -1)-total;
}
