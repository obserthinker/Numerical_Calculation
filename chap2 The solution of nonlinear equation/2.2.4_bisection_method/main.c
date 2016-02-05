/*xuanyu wang 9.28.14*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//
double f(double rate);
//
void bisection(double a0,double b0);

int main()
{
    //freopen("out.txt","w",stdout);
    //a and b are the left and right end points
    double a,b;

    a = 0.14;
    b = 0.16;
    bisection(a,b);

    return 0;
}

void bisection(double a,double b)
{
    //err is error estimate for c
    double err;
    //tol is the tolerance for the vaalue of f at the zero
    double tol = 1E-10;
    //c is the zero
    double c;
    int num_iteration = 0;

    //使用do...while循环避免第一次循环需要判断
    do{
        c = (a+b)/2;
        //debug
        //printf("a = %.10f\tb = %.10f\tc = %.10f\n",a,b,c);
        //printf("%.13f\n",b);
        
        if(f(c) != 0){
            //debug
            //printf("f(c) = %.10f\n",f(c));
            //contruc a new interval
            if(f(c) * f(a) > 0)a = c;
            else b = c;
            num_iteration++;
        }
        else break;

        err = fabs(b - a);
        printf("err = %.13f\n",err);
    }while(err >= tol);
    
    printf("number of iteration = %d\n",num_iteration);
    printf("ans:rate = %.10f",c);
}

double f(double rate)
{
    double monthly;
    double num_month;
    double total;
	double res;
    double r12;

    r12 = rate/12;
    monthly = 300;
    num_month = 240;
    total = 500000;
	res = (12 * monthly / (rate))*(pow(1 + r12, num_month) - 1) - total;
    return res;
}
