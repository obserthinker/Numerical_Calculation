#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);
int main()
{
    //4 double a = -2.4,b = -1.6;
    //5 double a = 0.8,b = 1.6;
    //6 double a = 3.2,b = 4.0;
    //7 double a = 6.0,b = 6.8;
    double c;
    int i;
    for(i = 0;i < 4;i++){
        c = b - (f(b)*(b-a))/(f(b)-f(a));
        printf("f(a) = %f f(b) = %f f(c) = %f\n",f(a),f(b),f(c));
        if(f(a)*f(c) <= 0){
            b = c;
            printf("b = c\n");
        }
        else {a = c;printf("a = c");}
        printf("c%d = %f,\ta%d = %f,\tb%d = %f\n",i,c,i,a,i,b);
    }
    printf("f(c) = %f",f(c));
    return 0;
}

double f(double x){
    /*4*/ //return (exp2(x) - 2 - x);
    //5 return cos(x) + 1 - x;
    //6 return log(x) - 5 + x;
    //7 return pow(x,2)-10*x+23;
}
