#ifndef OPE_GRADIENT_H_INCLUDED
#define OPE_GRADIENT_H_INCLUDED

#include <math.h>


struct vertex{
    double coord_x;
    double coord_y;
};
typedef struct vertex vtx;

#include "operation.h"

double cond(vtx* v);
double pdx(vtx *v);
double pdy(vtx *v);

vtx* initialize_vertex(vtx* B)
{
    B = (vtx*)malloc(sizeof(vtx));
    B->coord_x = 0;
    B->coord_y = 0;
    //show_vertex(B);
    return B;
}

void show_vertex(vtx *B)
{
    printf("(%.7lf,%.7lf) & ",B->coord_x,B->coord_y);
}

vtx* gradient(vtx* P, vtx* gd)
{
    gd->coord_x = pdx(P);
    gd->coord_y = pdy(P);

    return gd;
}

vtx* compute_S(vtx *gd,vtx* S)
{
    S->coord_x = -gd->coord_x / cond(gd);
    S->coord_y = -gd->coord_y / cond(gd);

    return S;
}

double cond(vtx* v)
{
    return sqrt(pow(v->coord_x,2) + pow(v->coord_y,2));
}

double f(vtx *v)
{
    double x = v->coord_x;
    double y = v->coord_y;
    return pow(x,4)+2*pow(x,2)*pow(y,2)-pow(x,2)-4*x+pow(y,4)-pow(y,2)-6*y+14;
}

double pdx(vtx *v)
{
    double x = v->coord_x;
    double y = v->coord_y;

    return 4*pow(x,3)+4*x*y*y-2*x-4;
}

double pdy(vtx *v)
{
    double x = v->coord_x;
    double y = v->coord_y;

    return 4*pow(y,3)+4*y*x*x-2*y-4;
}



double compute_min(vtx* P0, vtx* S)
{
    //printf("P0:");
    show_vertex(P0);
    //printf("S:");
    show_vertex(S);

    double P[3]={0};
    double left_end, right_end, h;
    double tol;

    //scanf("%lf",&left_end);
    left_end = 0;
    //scanf("%lf",&right_end);
    right_end = 10;
    h = (right_end - left_end) / 2;
    tol = 1e-6;
    //printf("h_start = %lf\n",h);
    P[0] = left_end;

    //show_P(P);
    do{
        h = search_P(P, h, &left_end, &right_end, P0, S);
        reset_P(P, h, &left_end, &right_end, P0, S);
        //show_P(P);
        //printf("P[0] = %lf\n\n",P[0]);
    }while(fabs(df_coe(P[0], P0, S)) > tol && P[0] < 10);

    return P[0];
}

double distance(vtx* A, vtx* B)
{
    double delta_x = pow(A->coord_x - B->coord_x, 2);
    double delta_y = pow(A->coord_y - B->coord_y, 2);
    return sqrt(delta_x + delta_y);
}
#endif // OPE_GRADIENT_H_INCLUDED
