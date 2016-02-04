#include <stdio.h>
#include <stdlib.h>

int main()
{
    freopen("in.txt","w",stdout);
    printf("50 50\n");
    int i = 0;
    printf("12 -2 1\n");
    printf("-2 12 -2 1\n");
    for(i = 0;i < 46;i++){
        printf("1 -2 12 -2 1\n");
    }
    printf("1 -2 12 -2\n");
    printf("1 -2 12\n");
    for(i = 0;i< 50;i++){
            printf("%d ",5);
    }
    return 0;
}
