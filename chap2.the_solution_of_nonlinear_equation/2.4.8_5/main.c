/*王旋宇 9.28.14改*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//f()为待求解函数。此为求其值
double f(double x);
//函数f_d()为待求解函数的导数。此为求导数值
double f_d(double x);
//函数ac_nt_rps()为加速牛顿-拉夫森算法程序
void ac_nt_rps();

int main()
{
    //freopen("out.txt","w",stdout);
    //进入加速牛顿-拉夫森算法程序
    ac_nt_rps();
    return 0;
}

void ac_nt_rps()
{
    //M与P分别为函数根的阶与对应的根
    double M;
    double p;
    //n统计迭代次数
    int n = 0;
    //输入待求根的阶
    printf("order M = ");
    scanf("%lf",&M);
    //输入待求函数的初始值
    printf("start with p0 = ");
    scanf("%lf",&p);

    //迭代
    printf("开始迭代：\n");
    while(f(p) != 0 && n<200){//当所得序列值不是所求根的时候
        //调试使用，输出当前序列值以及函数值
        printf("f(%f) = %.10f\n",p,f(p));
        //加速牛顿-拉夫森迭代公式计算新序列值
        //与牛顿迭代法比较使用
        //printf("迭代计算：%.25f = %.15f-%f/%f\n",p - (f(p))/f_d(p),p,f(p),f_d(p));
        p = p - (f(p))/f_d(p);
        //与牛顿迭代法比较使用
        //printf("迭代之后f(%f) = %.10f\n",p,f(p));
        n++;//每次迭代之后n+1
        //printf("第%d次迭代\n",n);
        //调试使用，检验每次生成项的函数值
        //getchar();
    }
    printf("迭代结束\n");
    //输出答案
    printf("迭代次数n=%d\n",n);
    printf("anser:p = %f",p);
}

double f(double x)
{
    //分别为计算第一题、第二题、第三题的函数值
    //return ( pow((x - 2),5) );
    //return ( sin(pow(x,3)) );
    return ( (x-1)*log(x) );
}

double f_d(double x)
{
    //分别为计算第一题、第二题、第三题的导函数值
    //return (5 * pow(x - 2,4));
    //return (3 * pow(x,2) * cos(pow(x,3)));
    return (log(x) + (x - 1)/x);
}
