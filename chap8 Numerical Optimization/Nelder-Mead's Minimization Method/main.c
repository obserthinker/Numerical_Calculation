#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include <math.h>

int main()
{
    vtx *B, *G, *W;
    vtx *M, *R, *C;
    double tol = 1e-11;
    int count = 0;

    B = initialize_vertex(B);
    G = initialize_vertex(G);
    W = initialize_vertex(W);
    M = initialize_vertex(M);
    R = initialize_vertex(R);

    start_BGW(B,G,W);
    sort(B,G,W);
    midof(M,B,G);
    expansion(R,M,W);

    printf("\nbest point\t\tGood point\t\tWorst point\n");

    do{
        //getchar();
        if(f(R) < f(G)){
            situation_1(B,R,W,M);
        }
        else{
            situation_2(B,R,W,M,G);
        }
        sort(B,G,W);
        printf("%d & ",count++);
        show_triangle(B,G,W);
        midof(M,B,G);
        expansion(R,M,W);
        //printf("B:");show_vertex(B);
        //printf("W:");show_vertex(W);
        //printf("error=%lf - %lf = %lf\n",f(B), f(W), fabs(f(B) - f(W)));
    }while(fabs(f(B) - f(W)) > tol);


    return 0;
}
