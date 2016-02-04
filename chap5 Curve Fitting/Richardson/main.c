#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double D(double x,double k, double h);
double f(double x);

int main()
{
    //freopen("out.txt","w",stdout);
    int k,count;
    double result,result_next,error,error_next,tol;
    double h,h_next,x;
    double fen=10;
    double truev = 1.015206105900236;


    k = 7;
    h = h_next = 0.000001;
    //x = 1 / sqrt(3);
    //x = (1 + sqrt(5)) / 3;//function 2
    //x = 1 / sqrt(2);//function 3
    //x = (1 - sqrt(5)) / 2;//function 4
    x = 0.0001;//function 5
    count = 0;
    tol = 1e-13;

    result_next = D(x,k,h);
    h = h/fen;

    do{
            result = D(x,k,h);
            error = fabs(result - truev);
            printf("%.10lf  &  %.13lf  &  %.13lf\\\\\\hline\n",h,result,fabs(result-truev));
            h_next = h/fen;
            result_next = D(x,k,h_next);
            error_next = fabs(result_next - truev);
            h = h_next/fen;
            printf("%.10lf  &  %.13lf  &  %.13lf\\\\\\hline\n",h,result_next,fabs(result-truev));
            count++;
    }while(error > tol && count < 50 && error_next < error);

    printf("result = %.14lf\n",result);
    return 0;
}

double D(double x,double k, double h)
{
    if(k == 0){
        return (f(x + h) - f(x - h)) / (2 * h);
    }
    if(k != 0){
        return (pow(4,k) * D(x,k-1,h) - D(x,k-1,2*h)) / (pow(4,k) - 1);
    }
}

double f(double x)
{
    //return (60 * pow(x,45) - 32 * pow(x,33) + 233 * pow(x,5) - 47 * pow(x,2) - 77);//function 1
    //return (tan( cos( (sqrt(5) + sin(x)) / (1 + pow(x,2))  ) ) );//function 2
    //return (sin(cos(1 / x)));//function 3
    //return sin(pow(x,3) - 7 * pow(x,2) + 6 * x + 8);//function 4
    return pow(x,pow(x,x));//function 5
}
