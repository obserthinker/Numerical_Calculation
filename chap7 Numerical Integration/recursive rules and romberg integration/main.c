#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operation.h"
#define PI 3.141592653589793
int main()
{
    double left_end, right_end;
    double J,K;
    double precise,error,tol,result;
    double **ma;
    int i,j;
    ma = malloc(25*sizeof(double*));printf("OK\n");
    for(i = 0; i<25;i++){
        for(j = 0; j < 25; j++){
            *(ma+i) = malloc(25*sizeof(double));
            *(*(ma+i)+j) = 0;
        }
    }

    initialize_parameters(&left_end, &right_end, &J, &K);
    printf("after initialization\nJ = %lf\nK = %lf\nleft_end=%lf\nright_end=%lf\n",
            J,K,left_end,right_end);
    tol = 1e-10;
    error = 0;
    precise = (double)PI;
    do{
        result = romberg(ma,J,K,left_end,right_end);
        //error = fabs(result - precise);
        error = fabs( *(*(ma+(int)J)+(int)K) - *(*(ma+(int)J-1)+(int)K-1));
            printf("R(%.1lf,%.1lf) result = %.11lf\n",J,K,result);

        J++;
        K++;
    }while(error > tol);
    //freopen("matrix1.txt","w",stdout);
    printf("&");
    for(i = 0; i< 8;i++){
        printf("%d&",i);
    }
    printf("\\\\\\hline");
    for(i = 0; i<8;i++){
        printf("%d&",i);
        for(j = 0; j < 8; j++){
            if(*(*(ma+i)+j) != 0){
                printf("%.10lf&",*(*(ma+i)+j));
            }
            else{
                printf("&");
            }
        }
        printf("\\\\\\hline\n");
    }
    printf("R(%.1lf,%.1lf) result = %.11lf\n",J,K,result);
    printf("error=%.12lf\n",result,error);
    return 0;
}
