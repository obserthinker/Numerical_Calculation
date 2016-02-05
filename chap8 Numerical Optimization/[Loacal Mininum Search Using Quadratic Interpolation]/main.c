#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operation.h"

int main()
{
    double P[3]={0};
    double left_end, right_end, h;
    double tol;

    //scanf("%lf",&left_end);
    left_end = 1;
    //scanf("%lf",&right_end);
    right_end = 5;
    h = ((right_end - left_end)) / 2;
    tol = 1e-6;
    printf("h = %lf\n",h);
    P[0] = left_end;

    show_P(P);
    do{
        h = search_P(P, h, &left_end, &right_end);
                show_P(P);
        if(P[1] == P[0] && P[2] == P[0]){
            printf("out\n");
            break;
        }
        reset_P(P, h, &left_end, &right_end);
        //show_P(P);
        //printf("P[0] = %lf\n\n",P[0]);
    }while(fabs(df(P[0])) > tol && P[0] < 10);

    return 0;
}







