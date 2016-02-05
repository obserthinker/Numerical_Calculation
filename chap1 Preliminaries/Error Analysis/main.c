//王旋宇 2014,9,15 误差序列分析
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void iterate_x(double* ,int );//none-error sequence as a benchmark
void iterate_r(double* ,double* ,int );//for the 1st question
void iterate_p(double* ,double* ,int );//for the 2nd question
void iterate_q(double* ,double* ,int );//for the 3rd question

int main()
{
    //freopen("out.txt","w",stdout);
    double x[10] = {0},r[10] = {0},p[10] = {0},q[10] = {0};
    int n;//number of computation

    n = 10;
    x[0] = 2;
    r[0] = 0.994;
    p[0] = 1;p[1] = 0.497;
    q[0] = 1;q[1] = 0.497;
    
    //computing for every question
    iterate_x(x,n);
    iterate_r(x,r,n);
    iterate_p(x,p,n);
    iterate_q(x,q,n);

    return 0;
}


void iterate_x(double x[],int n)
{
    int i;
    for(i = 1;i < n;i++){
        x[i] = x[i-1]/2;
    }
    printf("x\n");
    for(i = 0;i < n;i++){
	//output to window
        //printf("x %d = %.10f \n",i,x[i]);
	//output to file
        printf("%.10f,",x[i]);
    }
    printf("\n");
}


void iterate_r(double x[],double r[],int n)
{
    int i;
    //Debug
    //printf("Check out the x\[\]\n:");
    //for(i = 0;i < n;i++){
    //    printf("x %d = %f \n",i,x[i]);
    //}
    for(i = 1;i < n;i++){\
        r[i] = r[i-1]/2;
    }
    for(i = 0;i < n;i++){
	//output to window
        printf("r %d = %.10f \t |x%d - r%d| = %.10f\n",i,r[i],i,i,fabs(x[i] - r[i]));
	//output to file
        //printf("%.10f,",fabs(x[i] - r[i]));
    }
    printf("\n");
}


void iterate_p(double x[],double p[],int n)
{
    int i;

    for(i = 2;i < n;i++){
        p[i] = (3*p[i-1])/2-p[i-2]/2;
    }
    printf("p\n");
    for(i = 0;i < n;i++){
	//output to window
        printf("p %d = %.10f \t |x%d - p%d| = %.10f\n",i,p[i],i,i,fabs(x[i] - p[i]));
	//output to file
        //printf("%.10f,",fabs(x[i] - p[i]));
    }
    printf("\n");
}


void iterate_q(double x[],double q[],int n)
{
    int i;

    for(i = 2;i < n;i++){
        q[i] = (5*q[i-1])/2-q[i-2];
    }
    printf("q\n");
    for(i = 0;i < n;i++){
	//output to window
        printf("q %d = %.10f \t |x%d - q%d| = %.10f\n",i,q[i],i,i,fabs(x[i] - q[i]));
	//output to file
        //printf("%.10f,",fabs(x[i] - q[i]));
    }
}
