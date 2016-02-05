#include <stdio.h>
#include <stdlib.h>

int main()
{
    int b[6] = {0},a[6] = {0};
    int x;
    int n;
    n = 6;
    x = 3;
    a[0] = -40;
    a[1] = 4;
    a[2] = 8;
    a[3] = 8;
    a[4] = -6;
    a[5] = 1;
    printf("for the x = 3,the answer is %d",horner(a,b,n));
    return 0;
}

int horner(int a[],int b[],int n)
{
    b[5] = a[5];
    int i;
    i = n-1;
    for(i--;i >= 0;i--){
        b[i] = 3*b[i+1] + a[i];
    }
    return b[0];
}
