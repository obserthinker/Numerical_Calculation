#include <stdio.h>
#include <stdlib.h>
#define C 0
struct Vec
{
    int order;
    double *v;
};
typedef struct Vec Vector;

void ShowPoly(Vector *coe);
double CalInte(Vector *in, Vector *coe, double x);

int main()
{
    freopen("newton_in.txt","r",stdin);
    //freopen("newton_out.txt","w",stdout);
    int i;
    double upper_bound, lower_bound;
    double upper_bound_r, lower_bound_r;
    Vector *coe, *in;
    coe = malloc(sizeof(Vector*));
    in = malloc(sizeof(Vector*));

    printf("Input the order of the polynomial:");
    scanf("%d",&(coe->order));
    coe->v = malloc(((coe->order)+1)*sizeof(double));
    in->order = (coe->order) + 1;
    in->v = malloc(((in->order)+1)*sizeof(double));

    for(i = 0; i <= coe->order; i++){
        printf("Input the coefficient of the order %d:\t",i);
        scanf("%lf",(coe->v)+i);
    }
    ShowPoly(coe);

    printf("Input the upper bound:");
    scanf("%lf",&upper_bound);
    printf("the upper bound is %lf\n",upper_bound);
    printf("Input the lower bound:");
    scanf("%lf",&lower_bound);
    printf("the lower bound is %lf\n",lower_bound);

    upper_bound_r = CalInte(in,coe,upper_bound);
    lower_bound_r = CalInte(in,coe,lower_bound);

    printf("the result is : %lf-%lf = %lf\n",upper_bound_r, lower_bound_r,upper_bound_r-lower_bound_r);
    printf("the average is %lf = %lf/(%lf-%lf)",(upper_bound_r-lower_bound_r)/(upper_bound-lower_bound),(upper_bound_r-lower_bound_r),upper_bound,lower_bound);
    return 0;
}

double CalInte(Vector *in, Vector *coe, double x)
{
    int i;
    *((in->v)+(in->order)) = *((coe->v)+(coe->order)) / ((coe->order)+1);
    printf("I_%d = %lf\n",in->order,*((in->v)+(in->order)));
    for(i = (in->order)-1; i > 0 ; i--){
        *((in->v)+i) = (*((coe->v)+i-1) / i) + *((in->v)+i+1) * x;
        printf("I_%d =a_%d/%d + i_%d*x=%lf + (%lf)*%lf = %lf\n", i, i-1,i,i+1,(*((coe->v)+i-1) / i),*((in->v)+i+1),x,*((in->v)+i));
    }
    *((in->v)+0) = C + (*((in->v)+1)) * x;
    printf("I_0 = C + I_1 * x = %d + %lf*%lf = %lf\n",C,(*((in->v)+1)),x,*((in->v)+0));
    printf("result of integration %lf is %lf\n",x, *((in->v)+0));
    return *((in->v)+0);
}

void ShowPoly(Vector *coe)
{
    printf("\nThe integrate polynomial is:");
    int i;
    for(i = coe->order; i >= 0; i--){
        if(*((coe->v)+i) != 0){
            printf("%lf",*((coe->v)+i));
        }
        if(i != 0){
            printf("*x^%d+",i);
        }
    }
    printf("\n");
}
