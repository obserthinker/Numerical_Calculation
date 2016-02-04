#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

/*----------------Includes---------------*/
//the head files that were included
#include <math.h>
/*----------------Define---------------*/
#define ebase 2.718281828459

double function(double x);

/********************************************************
 Function Name: initialize_parameters
 Function Description: Initialize some parameters for integration.
Inputs: the left end and right end of the interval integrated.
 Outputs: No output
************************************************************/
void initialize_parameters(double *left_end,double *right_end,double *M)
{
    printf("the left end and right end of interval:");
    scanf("%lf%lf",left_end,right_end);
    printf("The interval would be subdivided into M subintervals:");
    scanf("%lf",M);
}

/*********************************************************
Function Name:integrate
Description:integrate the function over interval assigned.
        One way is Composite Trapezoidal, another is Composite
        Simpson's.
Input:'Xnode',nodes of x, interval's ends and number of subinterval.
    and 'mode' to choose which way will be used to integrate.
Output:none.
*********************************************************/
void intergrate(double left_end, double right_end, double M)
{
    char mode;
    printf("the mode you'll use (T or S):\n");
    scanf("%c",&mode);
    printf("mode = %c\n",mode);

    if(mode == 'T'){
        printf("T mode\n");
        composite_trapezoidal(left_end,right_end,M);
    }
    if(mode == 'S'){
        printf("S mode\n");
        composite_simpson(left_end,right_end,M);
    }
}

/************************************************************
Function Name:composite_trapezoidal
Description:use composite trapezoidal rule to integrate.
Input:'Xnode',nodes of x, interval's ends and number of subinterval.
Output:None
************************************************************/
void composite_trapezoidal(double left_end, double right_end, double M)
{
    int i;
    double h;
    double integration_2, integration_1;

    integration_1 = 0;
    integration_2 = 0;
    h = (right_end - left_end) / M;

    //calculate the second part
    integration_1 += h * (function(left_end) + function(right_end)) / 2;
    //calculate the first part of result
    for(i = 1; i < M; i++){
        integration_2 += function(left_end + i * h);
    }
    integration_2 *= h;

    printf("the parameters is:\nleft end = %lf\nright end = %lf\nM = %lf\n"
                                                                    ,left_end,right_end,M);
    printf("the result is: %.10lf\n",integration_1 + integration_2);
}
/************************************************************
Function Name:composite_trapezoidal
Description:use composite trapezoidal rule to integrate.
Input:'Xnode',nodes of x, interval's ends and number of subinterval.
Output:None
************************************************************/
void composite_simpson(double left_end, double right_end, double M)
{
    int i;
    double h;
    double integration_1,integration_2,integration_3;

    integration_1 = 0;
    integration_2 = 0;
    integration_3 = 0;
    h = (right_end - left_end) / M / 2;

    //calculate the first part of result
    integration_1 += h * (function(left_end) + function(right_end)) / 3;
    //calculate the second part of result
    for(i = 1; i < M; i++){
        integration_2 += function(left_end + (2 * i) * h);
    }
    integration_2 *= (2 * h) / 3;
    //calculate the third part
    for(i = 1; i <= M; i++){
        integration_3 += function(left_end + (2 * i - 1) * h);
    }
    integration_3 *= (4 * h) / 3;

    printf("the parameters is:\nleft end = %lf\nright end = %lf\nM = %lf\n"
                                                                    ,left_end,right_end,M);
    printf("the result is: %.10lf\n",integration_1 + integration_2 + integration_3);
}

/**********************************************************
Function Name:function
Description:return a mathematical function's value by the
                     given number.
Input:a number x
Output:the value of f(x)
***********************************************************/
double function(double x)
{
    //return 1/(1+pow(x,2));//-1~1,M>=18258
    //return (2 + sin(2 * sqrt(x)));//0~1,M>=unknown
    //return 1/sqrt(x);//0.25~4,M>=324760
    //return pow(x,2) * pow(ebase,-x);//0~4,M>=103280
    return 2 * x * cos(x);//0~2,M>=36264
    //return sin(2 * x) * pow(ebase,-x);//0~pi,M>=101664
}
#endif // OPERATION_H_INCLUDED
