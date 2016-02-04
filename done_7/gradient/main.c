#include <stdio.h>
#include <stdlib.h>
#include "ope_gradient.h"

int main()
{
    vtx **P;
    vtx *gd;
    vtx *S;
    double hmin;

    P = (vtx**)malloc(3 * sizeof(vtx*));
    gd = (vtx*)malloc(sizeof(vtx));
    S = (vtx*)malloc(sizeof(vtx));

    *(P + 0) = initialize_vertex(*(P + 0));
    *(P + 1) = initialize_vertex(*(P + 1));
    *(P + 2) = initialize_vertex(*(P + 2));
    gd = initialize_vertex(gd);
    S = initialize_vertex(S);

    (*(P + 0))->coord_x = -3;
    (*(P + 0))->coord_y = -2;

    do{
        gd = gradient(*(P + 0),gd);
        S = compute_S(gd, S);

        //show_vertex(gd);
        //show_vertex(S);
        hmin = compute_min(*(P + 0), S);
        printf("%.8lf\\\\\\hline\n",hmin);
        (*(P + 1))->coord_x = (*(P+0))->coord_x;
        (*(P + 1))->coord_y = (*(P+0))->coord_y;
        (*(P + 0))->coord_x = (*(P+0))->coord_x + hmin * S->coord_x;
        (*(P + 0))->coord_y = (*(P+0))->coord_y + hmin * S->coord_y;
    }while(distance(*(P + 0), *(P + 1)) > 1e-7);



    return 0;
}
