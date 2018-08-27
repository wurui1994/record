#include <stdio.h>
void add_(float*a,float*b,float*c)
{
	*c=*a+*b;
	printf("%f+%f\n",*a,*b,*c);
}