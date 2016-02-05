#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);

int main()
{
    double left_end, right_end;//the endpoint of interval
    double c, d;//the interior points
    double R;//the ration
    double tol = 1e-6;
    int k=0;
/*********initialize the coefficients*********/
    left_end = 1;
    right_end = 5;
    R = (sqrt(5) - 1) / 2;
/*********golden ratio********************/
    do{
        //find interior points
        c = left_end + (1 - R) * (right_end - left_end);
        d = right_end - (1 - R) * (right_end - left_end);

        //printf("a=%.7lf\tc=%.7lf\td=%.7lf\tb=%.7lf\tf(c)=%.7lf\tf(d)=%.7lf\n",
        printf("%d & %.7lf & %.7lf & %.7lf & %.7lf & %.7lf & %.7lf\\\\\\hline\n",
               k, left_end,c,d,right_end,f(c),f(d)
               );
        k++;//record the number of cycle
        //if find the minimization, exit the recycle
        if(fabs(f(d) - f(c)) < (tol)){
            break;
        }
        //find a new interval
        if(f(c) < f(d)){
            right_end = d;
        }
        else{
            left_end = c;
        }
    }while(1);

    printf("result = %.9lf\n",f(c));
    return 0;
}
/********************************
function name : f
description:
Input: the variable x
Output:f(x)
/********************************/
double f(double x)
{
    //return pow(x, 2) - sin(x);
    //return exp(x) + 2*x + pow(x,2)/2;
    //return -sin(x) - x +pow(x,2)/2;
    //return pow(x,2)/2 -4*x - x*cos(x);
    return pow(x,3)-5*pow(x,2)+23;
}
