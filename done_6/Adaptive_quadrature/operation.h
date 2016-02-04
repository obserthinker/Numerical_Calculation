#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
/*----------------Includes---------------*/
//the head files that were included
#include <math.h>
/*-----------------Define-----------------*/
#define ebase 2.718281828459045
#define PI 3.1415926

/*---------------------------------------functions-----------------------*/
double simpson(double left_end, double right_end);
double f(double x);

/********************************************************
 Function Name: initialize_parameters
 Function Description: Initialize some parameters for integration.
Inputs: the left end and right end of the interval integrated.
 Outputs: No output
************************************************************/
void initialize_parameters(double *left_end,double *right_end)
{
    printf("the left end and right end of interval:\n");
    //scanf("%lf%lf",left_end,right_end);
    *left_end = -PI/2;
    *right_end = PI/2;

}
/**************************************************************
Function Name: f
Description:The function be integrated.
Input:x for calculating f(x)
Output:The value f(x)
***************************************************************/
double f(double x)
{
    return sqrt(1+pow(sin(x), 2));
}

/**************************************************************
Function Name: f
Description:The function be integrated.
Input:x for calculating f(x)
Output:The value f(x)
***************************************************************/

double adapting(double left_end, double right_end, double tolerance)
{
    double error;
    double mid;
    double result=0;

    mid = (left_end + right_end) / 2;
    error = fabs(simpson(left_end,mid) + simpson(mid,right_end) - simpson(left_end, right_end));
    error /= 10;
    if(error < tolerance){
        //printf("%.5lf & %.5lf & %.11lf & %.11lf & %.9lf\\\\\\hline\n"
           //,left_end,right_end,simpson(left_end,mid) + simpson(mid,right_end),error,tolerance);
        result += simpson(left_end,mid) + simpson(mid,right_end);
    }
    else{
        result += adapting(left_end, mid, tolerance/2);
        result += adapting(mid, right_end, tolerance/2);
    }
    return result;
}

double simpson(double left_end, double right_end)
{
    double h;
    double mid;

    h = (right_end - left_end) / 2;
    mid = (left_end + right_end) / 2;

    return h * (f(left_end) + 4 * f(mid) + f(right_end)) / 3;
}

#endif // OPERATION_H_INCLUDED
