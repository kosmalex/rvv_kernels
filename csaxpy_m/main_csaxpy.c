#include <stddef.h>
#include <stdio.h>

void *csaxpy(int n,void* mask, void* x,void* y,int a);
//  for (size_t i = 0; i < n; i++)
// 		if (cond[i])	y[i] += a * x[i];

int main()
{
	size_t n=16;
	int y[n], x[n], a=2;
	short int msk[n];

	for(size_t i=0;i<n;i++)
	{	x[i]=i; msk[i]=1;}

	csaxpy(n,msk,x,y,a);

	for(size_t i=0;i<n;i++)
		printf("\ny[%d]=%d",i,y[i]);

	printf("\n");

    return 0;
}
