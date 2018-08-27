#include <stdio.h>

extern void add_(float* a,float* b,float* c);

int main()
{
	float a,b,c;
	a=5.0;
	b=7.0;
	add_(&a,&b,&c);
	return 0;
}