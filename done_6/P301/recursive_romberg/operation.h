#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

/*----------------Includes---------------*/
//the head files that were included
#include <math.h>

/*----------------define------------------*/
#define PI 3.141592653589793

double function(double x);
double trapozidal(double (*f)(),double J, double left_end, double right_end);

/********************************************************
 Function Name: initialize_parameters
 Function Description: Initialize some parameters for integration.
Inputs: the left end and right end of the interval integrated.
 Outputs: No output
************************************************************/
void initialize_parameters(double *left_end,double *right_end,double *J,double *K)
{
    /*printf("the left end and right end of interval:\n");
    scanf("%lf%lf",left_end,right_end);
    printf("The J & K:\n");
    scanf("%lf%lf",J,K);*/
    *left_end = 0;
    *right_end = 2;
    *J = 3;
    *K = 3;
}

/**************************************************************
Function Name: romberg
Description:using romberg rule to integrate.
Input:
Output:
***************************************************************/
double romberg(double **ma, double J, double K, double left_end, double right_end)
{
    //printf("calculating R(%.0lf,%.0lf)\n",J, K);
    int i,j;
    double (*f)();
    f = function;
    if(K == 0){
        if(*(*(ma + (int)J)+(int)K) == 0){
                *(*(ma + (int)J)+(int)K) = trapozidal(f, J, left_end, right_end);
                //printf("(%d,%d) = %lf\n",(int)J,(int)K,*(*(ma+(int)J)+(int)K));
        }
        return *(*(ma+(int)J)+(int)K);
        //return trapozidal(f, J, left_end, right_end);
    }
    else{
            //printf("Need R(%.0lf,%.0lf) & R(%.0lf,%.0lf)\n",J,K-1,J-1,K-1);
            if(*(*(ma+(int)J)+(int)(K-1)) == 0){
                *(*(ma+(int)J)+(int)(K-1)) = romberg(ma,J,K-1,left_end,right_end);
            }
            if(*(*(ma+(int)J-1)+(int)(K-1)) == 0){
                *(*(ma+(int)(J-1))+(int)(K-1)) = romberg(ma,J-1, K-1,left_end,right_end);
            }
/********************************************************
    for(i = 0; i<4;i++){
        for(j = 0; j < 4; j++){
            printf("(%d,%d) = %lf   ",i,j,*(*(ma+i)+j));
        }
        printf("\n");
    }
********************************************************/
            *(*(ma+(int)J)+(int)K) = (pow(4,K) * (*(*(ma+(int)J)+(int)(K-1)))- *(*(ma+(int)(J-1))+(int)K-1)) / (pow(4,K) - 1);
            return *(*(ma+(int)J)+(int)K);
    }
}

double trapozidal(double (*f)(),double J, double left_end, double right_end)
{
    int i;
    double M;
    double h;
    double sec_part = 0;
    h = (right_end - left_end) / pow(2,J);

    if(J == 0){
        return h * (f(left_end) + f(right_end)) / 2;
    }
    else{
        M = pow(2, J - 1);
        sec_part = 0;
        for(i = 1; i <= M; i++){
            sec_part += f(left_end + (2 * i -1) * h);
        }
        sec_part *= h;
        return trapozidal(f,J - 1,left_end,right_end) / 2 + sec_part;
    }

}

double function(double x)
{
    //return (pow(x,2) + x + 1) * cos(x);//test
    return sqrt(4 * x - pow(x,2));
    //return 4/(1 + pow(x,2));
}
#endif // OPERATION_H_INCLUDED
