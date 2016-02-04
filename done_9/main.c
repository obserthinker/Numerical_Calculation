//������ 2014,9,15 ������з���
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void iterate_x(double* ,int );//���޳�ʼ���ļ��㣬��Ϊ׼ȷֵ
void iterate_r(double* ,double* ,int );//�Ե�һ������ļ���
void iterate_p(double* ,double* ,int );//�Եڶ�������ļ���
void iterate_q(double* ,double* ,int );//�Ե���������ļ���

int main()
{
    //freopen("out.txt","w",stdout);//����������д���ļ�����ʹ��Python��ͼ
    double x[10] = {0},r[10] = {0},p[10] = {0},q[10] = {0};//����������ֱ������鲢��ʼ��
    int n;//nΪ��Ҫ�������
    n = 10;
    x[0] = 2;//���޳�ʼ�����и���ʼֵ
    r[0] = 0.994;//�Ե�һ��������и���ʼֵ
    p[0] = 1;p[1] = 0.497;//�Եڶ���������鸳��ʼֵ
    q[0] = 1;q[1] = 0.497;//�Ե�����������и���ʼֵ
    iterate_x(x,n);//�����޳�ʼ�����
    iterate_r(x,r,n);//�����һ��������������x[]��׼ֵ����������
    iterate_p(x,p,n);//����ڶ���������������x[]��׼ֵ����������
    iterate_q(x,q,n);//���������������,����x[]��׼ֵ����������
    //getchar();//ֱ�Ӵ򿪳����ʱ����Լ�����ϲ������ر�
    return 0;
}

//�����޳�ʼ�����
void iterate_x(double x[],int n)
{
    int i;
    for(i = 1;i < n;i++){//���õ��ƹ�ʽ�������ҵı�׼ֵ
        x[i] = x[i-1]/2;
    }
    printf("x\n");
    for(i = 0;i < n;i++){//�����׼ֵ
        //printf("x %d = %.10f \n",i,x[i]);//ֱ����ʾʱ���ô���
        printf("%.10f,",x[i]);//������ļ�ʱ���ô���
    }
    printf("\n");
}

//�����һ��������������x[]��׼ֵ����������
void iterate_r(double x[],double r[],int n)
{
    int i;
    //printf("Check out the x\[\]\n:");//�����׼ֵ���Ƿ��б仯
    //for(i = 0;i < n;i++){
    //    printf("x %d = %f \n",i,x[i]);
    //}
    for(i = 1;i < n;i++){//���õ��ƹ�ʽ�������ҵı�׼ֵ
        r[i] = r[i-1]/2;
    }
    for(i = 0;i < n;i++){//�������ֵ
        printf("r %d = %.10f \t |x%d - r%d| = %.10f\n",i,r[i],i,i,fabs(x[i] - r[i]));//ֱ����ʾʱ���ô���
        //printf("%.10f,",fabs(x[i] - r[i]));//������ļ�ʱ���ô���
    }
    printf("\n");
}

//����ڶ���������������x[]��׼ֵ����������
void iterate_p(double x[],double p[],int n)
{
    int i;

    for(i = 2;i < n;i++){//���õ��ƹ�ʽ�������ҵı�׼ֵ
        p[i] = (3*p[i-1])/2-p[i-2]/2;
    }
    printf("p\n");
    for(i = 0;i < n;i++){//�������ֵ
        printf("p %d = %.10f \t |x%d - p%d| = %.10f\n",i,p[i],i,i,fabs(x[i] - p[i]));//ֱ����ʾʱ���ô���
        //printf("%.10f,",fabs(x[i] - p[i]));//������ļ�ʱ���ô���
    }
    printf("\n");
}

//���������������,����x[]��׼ֵ����������
void iterate_q(double x[],double q[],int n)
{
    int i;

    for(i = 2;i < n;i++){//���õ��ƹ�ʽ�������ҵı�׼ֵ
        q[i] = (5*q[i-1])/2-q[i-2];
    }
    printf("q\n");
    for(i = 0;i < n;i++){//�������ֵ
        printf("q %d = %.10f \t |x%d - q%d| = %.10f\n",i,q[i],i,i,fabs(x[i] - q[i]));//ֱ����ʾʱ���ô���
        //printf("%.10f,",fabs(x[i] - q[i]));//������ļ�ʱ���ô���
    }
}
