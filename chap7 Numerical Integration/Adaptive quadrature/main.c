#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operation.h"



int main()
{
    //freopen("out.txt","w",stdout);
    double tolerance, error, result;
    double left_end, right_end, mid;
    //initialize the variables
    tolerance = 0.00001;
    initialize_parameters(&left_end,&right_end);

    result = adapting(left_end, right_end, tolerance);
    printf("result=%.11lf\n",result);
    return 0;
}
