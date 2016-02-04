/*王旋宇 9.28.14 改*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//函数f()来计算年金
double f(double rate);
//函数bisevtion()用来进入二分法
void bisection(double a0,double b0);

int main()
{
    //freopen("out.txt","w",stdout);
    //a,b分别为区间左右端点值
    double a,b;
    //初始区间赋值
    a = 0.14;
    b = 0.16;
    //进入二分法开始计算
    bisection(a,b);

    return 0;
}

void bisection(double a,double b)
{
    //err为误差
    double err;
    //tol为函数值的误差允许范围
    double tol = 1E-10;
    //c为区间中点
    double c;
    //记录迭代次数
    int n = 0;

    //使用do...while循环避免第一次循环需要判断
    do{
        //计算区间中点
        c = (a+b)/2;
        //调试使用，观察区间及其中点取值，检查区间是否构造正确
        //printf("a = %.10f\tb = %.10f\tc = %.10f\n",a,b,c);
        //printf("%.13f\n",b);
        //构造新区间
        if(f(c) != 0){//判断中点是不是零点，不是的话构造新的区间继续迭代
            //调试使用。输出c处的函数值看是否迭代收敛
            //printf("f(c) = %.10f\n",f(c));
            //判断零点在[a,c]或者[b,c]中，进而构造新的区间
            if(f(c) * f(a) > 0)a = c;
            else b = c;
            n++;
        }
        else break;//如果c是零点，跳出循环
        //计算误差
        err = fabs(b - a);
        printf("err = %.13f\n",err);
    }while(err >= tol);//误差大于允许范围的时候继续迭代
    //输出结果
    printf("迭代了%d次\n",n);
    printf("ans:rate = %.10f",c);
}

double f(double rate)
{
    //monthly、month、total分别是月金、月数、和年金
    double monthly;
    double nmonth;
    double total;
    //r12用来代替公式中的I/12，以便使公式更简洁不容易出错
    double r12;
    r12 = rate/12;
    //初始化赋值
    monthly = 300;
    nmonth = 240;
    total = 500000;
    //计算年金并返回
    return (12*monthly/(rate))*( pow(1+r12,nmonth) -1)-total;
}
