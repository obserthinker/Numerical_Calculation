#include <stdlib.h>
#include <stdio.h>

int main()
{
	double *x;
	int n_node, i;
	printf("Please input the number of nodes you have:");
	scanf("%d", &n_node);
	x = malloc(n_node*sizeof(double));
	for (i = 0; i < n_node; i++){
		printf("the NO.%d node is:",i);
		scanf("%lf", (x + i));
	}
	for (i = 0; i < n_node; i++){
		printf("the NO.%d node is %lf:\n", i, *(x + i));
	}
	return 0; 
}