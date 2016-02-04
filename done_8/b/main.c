#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);
double value_of_f(double x, double h);

int main()
{
    freopen("out.txt","w",stdout);
    double Dk,Dk_next;
    double error,error_next;
    double h,h_next;
    double x;
    double tol;
    int i;
    double fen=2;
    double truev = 75.173494695173620;

    x = 1 / sqrt(3);//function 1
    //x = (1 + sqrt(5)) / 3;//function 2
    //x = 1 / sqrt(2);//function 3
    //x = (1 - sqrt(5)) / 2;//function 4
    //x = 0.0001;//function 5
    tol = 1e-13;
    h = h_next = 0.9;
    //h = h_next = 0.00005;

    Dk_next = (f(x + h) - f(x - h)) / (2 * h);
    printf("%.10lf  &  %.13lf  &  %.13lf\\\\\\hline\n",h,Dk_next,fabs(Dk_next-truev));
    h = h/fen;


    //printf("f(0.00005) = %.14lf\tf(0.00015) = %.14lf\n",f(0.00005),f(0.00015));

    do{
        Dk = value_of_f(x,h);
        //error = fabs(Dk - Dk_next);
        error = fabs(Dk - truev);

        printf("%.10lf  &  %.13lf  &  %.13lf\\\\\\hline\n",h,Dk,fabs(Dk-truev));
        //Dk = (f(x + h) - f(x - h)) / (2 * h);
        //Dk = (-f(x + 2*h) + 8*f(x + h) - 8*f(x-h)+f(x-2*h)) / (12 * h);

        h_next = h / fen;
        Dk_next = value_of_f(x,h_next);
        //error_next = fabs(Dk_next - Dk);
        error_next = fabs(Dk_next - truev);
        //printf("%.10lf  &  %.13lf  &  %.13lf\\\\\n",h,Dk_next,error);

        printf("%.10lf  &  %.13lf  &  %.13lf\\\\\\hline\n",h,Dk_next,fabs(Dk_next-truev));
        //Dk_next = (f(x + h_next) - f(x - h_next)) / (2 * h_next);
        //Dk_next = (-f(x + 2*h_next) + 8*f(x + h_next) - 8*f(x-h_next)+f(x-2*h_next)) / (12 * h_next);

        h = h_next/fen;
        //printf("error = %.14lf\terror_next = %.14lf\n",error,error_next);
        if(error < tol)printf("\ncondition:error < tolerance\n");
        if(error_next >= error)printf("\ncondition:error_next >= error\n");
    }while(error > tol && error_next < error);

    printf("the h is: %.13lf\nthe result is: %.14lf\n", h_next, Dk_next);
    return 0;
}

double f(double x)
{
    return (60 * pow(x,45) - 32 * pow(x,33) + 233 * pow(x,5) - 47 * pow(x,2) - 77);//function 1
    //return (tan( cos( (sqrt(5) + sin(x)) / (1 + pow(x,2))  ) ) );//function 2
    //return (sin(cos(1 / x)));//function 3
    //return sin(pow(x,3) - 7 * pow(x,2) + 6 * x + 8);//function 4
    //return pow(x,pow(x,x));//function 5
}

double value_of_f(double x, double h)
{
    return (f(x + h) - f(x - h)) / (2 * h);
    //return (-f(x + 2*h) + 8*f(x + h) - 8*f(x-h)+f(x-2*h)) / (12 * h);;
}
