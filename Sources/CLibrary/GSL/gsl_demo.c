#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
#pragma comment(lib,"gsl")
int main()
{
	printf("%g\n",gsl_sf_bessel_J0(5.0));
	return 0;
}