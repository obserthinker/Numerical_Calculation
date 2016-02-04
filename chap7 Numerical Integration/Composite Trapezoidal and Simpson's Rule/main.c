#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

int main()
{
    freopen("tf5.txt","r",stdin);
    //freopen("tf5_out.txt","w",stdout);
    double left_end, right_end;
    double M;
//Initialize the parameters
    initialize_parameters(&left_end,&right_end,&M);
//To intergrate in the interval
    intergrate(left_end,right_end,M);
    return 0;
}
