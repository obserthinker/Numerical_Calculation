/*王旋宇 9.28.14 改*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INIT 0
#define TOL 1E-12
#define P0 0.8

//g() is the function whose fixed-point need to be found
double g(double x);

int main()
{
	//output the data to file
    //freopen("out.txt","w",stdout);

	//p0 is the initial guess for the fixed point
	double p0;
    //p is the approximation to the fixed point.
	//p_next is the value after p in iteraing sequence.
    double p,p_next;
    //err is the error in the approximation，tol is the tolerance
    double err,tol;
    //count_iterating is the number of iteration
    int count_iterating;

	count_iterating = INIT;
	p0 = P0;
    tol = TOL;
	p = p0;

    do{
        printf("g(%.12f) = %.12f\n",p,g(p));
        p_next = g(p);
        count_iterating++;
        //printf("n=%d\n",n);
        err = p_next - p;
        //printf("error = %.15f-%.15f=%.15f\n",pnext,p,err);
        //printf("%.15f\n",err);
        //if(err==0.000000000001)printf("1");
        //else printf("0\n");
        p = p_next;
        //printf("p=%.15f\n",p);
        //getchar();
    }while(fabs(err)>=tol);//当不满足精度要求的时候再次循环
    //输出结果
    printf("number of iteration = %d\n",count_iterating);
    printf("fixed_point = %10.15f\tg(q) = %10.15f",p_next,g(p_next));
    return 0;
}

double g(double p)
{
    return (pow(p,p-cos(p)));
}
