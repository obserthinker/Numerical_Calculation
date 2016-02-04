/*王旋宇 9.28.14 改*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//函数nt_rps()为牛顿-拉夫森算法程序
void nt_rps();
//f(),f_d(),r()分别为计算竖直方向高速、竖直方向导函数数值、水平方向行程
double f(double t);
double f_d(double t);
double r(double t);

int main()
{
    freopen("out.txt","w",stdout);
    //进入牛顿-拉夫森算法
    nt_rps();
    return 0;
}

void nt_rps()
{
    //t为时间，预估初始值为5
    double t = 5;
    double temp = 0;
    double err = 0;
    //tol为误差容忍范围
    double tol;
    //printf("f(5) = %.10f\n",f(5));
    tol = 1E-10;

    //迭代
    do{//如果超过了误差容忍范围继续迭代
        //牛顿-拉夫森迭代公式
        printf("%.12f\n",err);
        //printf("迭代计算：%.15f = %.15f-%f/%f\n",t - f(t)/f_d(t),t,f(t),f_d(t));
        temp = t - f(t)/f_d(t);
        err = fabs(temp - t);
        t = temp;
        //调试使用，观察生成项的值以及函数值
        //printf("f(%.10f) = %.10f\n",t,f(t));

    }while(err >= tol);
    //迭代结束，输出答案
    printf("\nans: f(%.10f) = %.10f\nr(t) = %.10f",t,f(t),r(t));
}

double f(double t)
{
    //返回y方向高度
    return ( 9600 * (1 - exp((-t) / 15)) - 480*t );
}

double f_d(double t)
{
    //返回y方向运动方程的导函数值
    return ( 640 * (exp((-t) / 15)) - 480 );
}

double r(double t)
{
    //返回x方向运动行程
    return ( 2400 * (1 - exp((-t) / 15) ) );
}
