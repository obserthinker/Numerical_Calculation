#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include "ope_gradient.h"

double f_coe(double x, vtx* P,vtx* S);
double df_coe(double x, vtx* P,vtx* S);


double search_P(double* P, double h, double* left_end, double* right_end, vtx* P0, vtx* S)
{
    /*if(fabs(df_coe(P[0], P0, S)) < 1e-6){
        printf("direct out\n");
        P[1] = P[0];
        P[2] = P[0];
        return h;
    }*/

    if(df_coe(P[0], P0, S) > 0){
        //printf("change to minus\n");
        if(h > (double)((P[0] - *left_end)) / 2){
            h = (double)((P[0] - *left_end)) / 2;
        }
        h = -fabs(h);
    }

    P[1] = P[0] + h;
    P[2] = P[0] + 2 * h;

    if(f_coe(P[0], P0, S) > f_coe(P[1], P0, S) && f_coe(P[2], P0, S) > f_coe(P[1], P0, S)){
        //printf("h_then = %lf\n",h);
        return h;
    }
    if(f_coe(P[0], P0, S) <= f_coe(P[1], P0, S)){
        h /= 2;
        h = search_P(P,h,left_end,right_end, P0, S);
        return h;
    }
    if(f_coe(P[0], P0, S) > f_coe(P[1], P0, S) && f_coe(P[1], P0, S) > f_coe(P[2], P0, S)){
        h *= 2;
        h = search_P(P,h,left_end,right_end, P0, S);
        return h;
    }
}

void reset_P(double* P, double h, double* left_end, double *right_end, vtx* P0,vtx* S)
{
    double h_min = 0;

    *right_end = P[2];

    h_min = h * (4 * f_coe(P[1], P0, S) - 3 * f_coe(P[0], P0, S) - f_coe(P[2], P0, S)) /
                    (4 * f_coe(P[1], P0, S) - 2 * f_coe(P[0], P0, S) - 2 * f_coe(P[2], P0, S));
    //printf("h_min_search = %lf\n",h_min);
    P[0] += h_min;
    if(df_coe(P[0], P0, S) <= 0){
        *left_end = P[0];
    }
    if(df_coe(P[0], P0, S) > 0){
        *right_end = P[0];
    }
}

double f_coe(double x, vtx* P,vtx* S)
{
    double xc,yc;
    xc = P->coord_x + x * S->coord_x;
    yc = P->coord_y + x * S->coord_y;

    return pow(xc,4)+2*pow(xc,2)*pow(yc,2)-pow(xc,2)-4*xc+pow(yc,4)-pow(yc,2)-6*yc+14;
}

double df_coe(double x, vtx* P,vtx* S)
{
    double xc,yc;
    xc = P->coord_x + x * S->coord_x;
    yc = P->coord_y + x * S->coord_y;

    double part1 = 4*pow(xc,3)-4-2*xc+4*xc*pow(yc,2);
    double part2 = -6+4*pow(yc,3)-2*yc+4*pow(xc,2)*yc;
    return S->coord_x*part1+S->coord_y*part2;
}

void show_P(double *P)
{
    printf("P[0] = %.7lf\n",P[0]);
    printf("P[1] = %.7lf\n",P[1]);
    printf("P[2] = %.7lf\n",P[2]);
}


#endif // OPERATION_H_INCLUDED
