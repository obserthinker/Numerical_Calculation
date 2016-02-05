/*xuanyu wang 9.28.14*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//f is the object function
double f(double x);
//f_d is the derivative of f
double f_d(double x);
//ac_nt_rps is acceleration of Newton-Raphson Iteration
void ac_nt_rps();

int main()
{
    //freopen("out.txt","w",stdout);
    ac_nt_rps();
    return 0;
}

void ac_nt_rps()
{
	//P is the root of the function and the M is the order of P
    double M;
    double P;
    //num_ite is the number of iteration
    int num_ite = 0;

    printf("order M = ");
    scanf("%lf",&M);
    
    printf("start with p0 = ");
    scanf("%lf",&P);

    printf("iteration start：\n");
    while(f(P) != 0 && num_ite < 200){//if P is not the root we want
        //debug
        //printf("f(%f) = %.10f\n",P,f(P));
        P = P - (f(P))/f_d(P);
        num_ite++;
        //printf("第%d次迭代\n",n);
        //getchar();
    }
    printf("iteration end\n");
    printf("number of iteration = %d\n",num_ite);
    printf("anser:p = %f",P);
}

double f(double x)
{
    //return ( pow((x - 2),5) );
    //return ( sin(pow(x,3)) );
    return ( (x-1)*log(x) );
}

double f_d(double x)
{
    //return (5 * pow(x - 2,4));
    //return (3 * pow(x,2) * cos(pow(x,3)));
    return (log(x) + (x - 1)/x);
}
