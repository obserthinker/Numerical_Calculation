//王旋宇 2014,9,15 误差序列分析
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void iterate_x(double* ,int );//对无初始误差的计算，作为准确值
void iterate_r(double* ,double* ,int );//对第一组情况的计算
void iterate_p(double* ,double* ,int );//对第二组情况的计算
void iterate_q(double* ,double* ,int );//对第三组情况的计算

int main()
{
    //freopen("out.txt","w",stdout);//将测试数据写入文件方便使用Python画图
    double x[10] = {0},r[10] = {0},p[10] = {0},q[10] = {0};//对四种情况分别建立数组并初始化
    int n;//n为需要计算次数
    n = 10;
    x[0] = 2;//对无初始误差进行赋初始值
    r[0] = 0.994;//对第一种情况进行赋初始值
    p[0] = 1;p[1] = 0.497;//对第二种情况尽情赋初始值
    q[0] = 1;q[1] = 0.497;//对第三种情况进行赋初始值
    iterate_x(x,n);//计算无初始误差结果
    iterate_r(x,r,n);//计算第一种情况结果，传入x[]标准值进行误差计算
    iterate_p(x,p,n);//计算第二种情况结果，传入x[]标准值进行误差计算
    iterate_q(x,q,n);//计算第三种情况结果,传入x[]标准值进行误差计算
    //getchar();//直接打开程序的时候可以计算完毕不立即关闭
    return 0;
}

//计算无初始误差结果
void iterate_x(double x[],int n)
{
    int i;
    for(i = 1;i < n;i++){//利用递推公式计算左右的标准值
        x[i] = x[i-1]/2;
    }
    printf("x\n");
    for(i = 0;i < n;i++){//输出标准值
        //printf("x %d = %.10f \n",i,x[i]);//直接显示时采用此行
        printf("%.10f,",x[i]);//输出到文件时采用此行
    }
    printf("\n");
}

//计算第一种情况结果，传入x[]标准值进行误差计算
void iterate_r(double x[],double r[],int n)
{
    int i;
    //printf("Check out the x\[\]\n:");//输出标准值看是否有变化
    //for(i = 0;i < n;i++){
    //    printf("x %d = %f \n",i,x[i]);
    //}
    for(i = 1;i < n;i++){//利用递推公式计算左右的标准值
        r[i] = r[i-1]/2;
    }
    for(i = 0;i < n;i++){//输出计算值
        printf("r %d = %.10f \t |x%d - r%d| = %.10f\n",i,r[i],i,i,fabs(x[i] - r[i]));//直接显示时采用此行
        //printf("%.10f,",fabs(x[i] - r[i]));//输出到文件时采用此行
    }
    printf("\n");
}

//计算第二种情况结果，传入x[]标准值进行误差计算
void iterate_p(double x[],double p[],int n)
{
    int i;

    for(i = 2;i < n;i++){//利用递推公式计算左右的标准值
        p[i] = (3*p[i-1])/2-p[i-2]/2;
    }
    printf("p\n");
    for(i = 0;i < n;i++){//输出计算值
        printf("p %d = %.10f \t |x%d - p%d| = %.10f\n",i,p[i],i,i,fabs(x[i] - p[i]));//直接显示时采用此行
        //printf("%.10f,",fabs(x[i] - p[i]));//输出到文件时采用此行
    }
    printf("\n");
}

//计算第三种情况结果,传入x[]标准值进行误差计算
void iterate_q(double x[],double q[],int n)
{
    int i;

    for(i = 2;i < n;i++){//利用递推公式计算左右的标准值
        q[i] = (5*q[i-1])/2-q[i-2];
    }
    printf("q\n");
    for(i = 0;i < n;i++){//输出计算值
        printf("q %d = %.10f \t |x%d - q%d| = %.10f\n",i,q[i],i,i,fabs(x[i] - q[i]));//直接显示时采用此行
        //printf("%.10f,",fabs(x[i] - q[i]));//输出到文件时采用此行
    }
}
