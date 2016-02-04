#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define rational (*(Fibonacci +count - k - 1) / *(Fibonacci +count - k))

double generate_Fb(double *Fibonacci, int n);
double f(double x);

int main()
{
    double *Fibonacci, F_try, f_b, f_bb;
    double tol, e;
    double a, b;
    int count;
/*****initialize the coefficients****************/
    /*printf("left end and right end are:\n");
    scanf("%lf%lf",&a, &b);
    printf("the tolerance is:\n");
    scanf("%lf",*tol);*/
    a = 1;
    b = 5;
    tol = 1e-7;
    e = 0.01;

    f_b = 1;
    f_bb = 0;
    count = 2;
/**************iterate to find length of sequence*********************/
    do{
        F_try = f_bb + f_b;
        printf("%.0lf = %.0lf + %.0lf\n",F_try, f_bb, f_b);
        f_bb = f_b;
        f_b = F_try;
        if(F_try > (b - a) / tol){
            break;
        }
        else{
            count++;
        }
    }while(1);
    printf("the n & F(n) are:%d,\t%lf\n",count, F_try);
/*******build a fibonacci suquence********/
    Fibonacci = malloc(count * sizeof(double));
    generate_Fb(Fibonacci, count);
/**************show Fibonacci sequence*********************
    printf("\n");
    for(;count >= 0; count--){
        printf("F(%d) = %.0lf\n", count, *(Fibonacci + count));
    }
    printf("\n");
************************************************************/

/**************************search***************************/
    int k;
    double d, c, rational;
    rational = *(Fibonacci +count - 1) / *(Fibonacci +count);
    c = a + (1 - rational) * (b-a);
    d = a + rational * (b-a);
    for(k = 1; k < count-1; k++){
        //printf("a=%.8lf\tc=%.8lf\td=%.8lf\tb=%.8lf\t",a,c,d,b);
        printf("%d & %.7lf & %.7lf & %.7lf & %.7lf & ",k-1,a,c,d,b);
        printf("%.7lf & %.7lf\\\\\\hline\n",f(c),f(d));
        //if F(n-1)/F(n)=1/2
        if(rational == 1/2){
            rational = 1/2 - e;
        }
        //get a new interval
        if(f(c) > f(d)){
            a = c;
            c = d;
            d = a + (*(Fibonacci +count - k - 1) / *(Fibonacci +count - k)) * (b-a);
        }
        if(f(c) < f(d)){
            b = d;
            d = c;
            c = a + (1 - (*(Fibonacci +count - k - 1) / *(Fibonacci +count - k))) * (b-a);
        }
    }
    printf("result = %.8lf\n",f(c));
    return 0;
}
/********************************
function name : generate_Fb
description:generate the sequence of Fibonacci.
Input: the length of the sequence and the point of sequence.
Output: the number of F(n)
/********************************/
double generate_Fb(double *Fibonacci, int n)
{
    //iterate to find F(n)
    if(n > 1){
        *(Fibonacci + n) = generate_Fb(Fibonacci, n-1) + generate_Fb(Fibonacci, n-2);
        return *(Fibonacci + n);
    }
    //set F(0) and F(1)
    else if(n == 1){
        *(Fibonacci + n) = 1;
        return 1;
    }
    else if(n == 0){
        *(Fibonacci + n) = 0;
        return 0;
    }
}
/********************************
function name : f
description:
Input: the variable x
Output:f(x)
/********************************/
double f(double x)
{
    //return pow(x,2) - sin(x);
    //return exp(x) + 2*x + pow(x,2)/2;
    //return -sin(x) -x+pow(x,2)/2;
    //return pow(x,2)-4*x-x*cos(x);
    return pow(x,3)-5*pow(x,2)+23;
}
