/*王旋宇 9.28.14 改*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//nt_rps is for Newton-Raphson
void nt_rps();
//f is for height of object. f_d is the derivative of f. r is the length of object
double f(double t);
double f_d(double t);
double r(double t);

int main()
{
    freopen("out.txt","w",stdout);
    nt_rps();
    return 0;
}

void nt_rps()
{
    double t = 5;
    double temp = 0;
    double err = 0;
    double tol;

    tol = 1E-10;

    //迭代
    do{
        printf("%.12f\n",err);
        //printf("Debug iteration computing：%.15f = %.15f-%f/%f\n",t - f(t)/f_d(t),t,f(t),f_d(t));
        temp = t - f(t)/f_d(t);
        err = fabs(temp - t);
        t = temp;
        //Debug
        //printf("f(%.10f) = %.10f\n",t,f(t));

    }while(err >= tol);

    printf("\nans: f(%.10f) = %.10f\nr(t) = %.10f",t,f(t),r(t));
}

double f(double t)
{
    //height of object
    return ( 9600 * (1 - exp((-t) / 15)) - 480*t );
}

double f_d(double t)
{
    //the derivative of f
    return ( 640 * (exp((-t) / 15)) - 480 );
}

double r(double t)
{
    //the length in x direction of object
    return ( 2400 * (1 - exp((-t) / 15) ) );
}
