#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

double f(double x);
double df(double x);

/********************************
function name : search_P
description:search the test points's step length.
Input: endpoints of interval, step length, point of test points
Output:the step length
/********************************/
double search_P(double* P, double h, double* left_end, double* right_end)
{
    if(fabs(df(P[0])) < 1e-6){
        printf("direct out\n");
        P[1] = P[0];
        P[2] = P[0];
        return h;
    }
    //getchar();
/*******************pre************************************/
    if(df(P[0]) > 0){
        //printf("change to minus\n");
        if(h > (double)((P[0] - *left_end)) / 2){
            h = (double)((P[0] - *left_end)) / 2;
        }
        h = -fabs(h);
    }

    P[1] = P[0] + h;
    P[2] = P[0] + 2 * h;
/************************************************************/
    if(f(P[0]) > f(P[1]) && f(P[2]) > f(P[1])){
        //printf("h = %lf\n",h);
        //printf("here out\n");
        return h;
    }
    if(f(P[0]) <= f(P[1])){
        //printf("h = %lf\n",h);
        show_P(P);
        printf("%lf & %lf\n",f(P[0]),df(P[0]));
        //printf("case1\n");
        h /= 2;
        h = search_P(P,h,left_end,right_end);
        return h;
    }
    if(f(P[0]) > f(P[1]) && f(P[1]) > f(P[2])){
        //printf("h = %lf\n",h);
        show_P(P);
        printf("%lf & %lf\n",f(P[0]),df(P[0]));
        //printf("case2\n");
        h *= 2;
        h = search_P(P,h,left_end,right_end);
        return h;
    }
}
/********************************
function name : reset_P
description: set the new research interval
Input: old interval's endpoint and step length h, and P.
Output:
/********************************/
void reset_P(double* P, double h, double* left_end, double *right_end)
{
    double h_min = 0;

    *right_end = P[2];

    h_min = h * (4 * f(P[1]) - 3 * f(P[0]) - f(P[2])) / (4 * f(P[1]) - 2 * f(P[0]) - 2 * f(P[2]));
    printf("h_min = %lf\n",h_min);
    P[0] += h_min;
    if(df(P[0]) <= 0){
        *left_end = P[0];
    }
    if(df(P[0]) > 0){
        *right_end = P[0];
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
    //return pow(x, 2) - sin(x);
    //return exp(x)+2*x+pow(x,2)/2;
    //return -sin(x)-x+pow(x,2)/2;
    //return pow(x,2)/2-4*x-x*cos(x);
    return pow(x,3)-5*pow(x,2)+23;
}
/********************************
function name : df
description:
Input: the variable x
Output:df(x)/dx
/********************************/
double df(double x)
{
    //return 2 * x - cos(x);
    //double fenzi1 = ((2*x - 1.0464334)*(1.3318241*x + 1.0));
    //double fenmu = (pow((0.4280863*x + 3.0),2) + pow((0.9037378*x - 2.0),2) + 2.0);
    //return fenzi1/pow(fenmu,2) - 1.3318241/fenmu;

    //return exp(x)+2+x;
    //return -cos(x) - 1 +x;
    //return x-4-cos(x)+x*sin(x);
    return 3*pow(x,2)-10*x;
}

void show_P(double *P)
{
    printf("%lf & ",P[0]);
    printf("%lf & " ,P[1]);
    printf("%lf & ",P[2]);
}


#endif // OPERATION_H_INCLUDED
