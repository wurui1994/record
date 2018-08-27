#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib,"gsl")
int main(int argc, char** argv)
{
    gsl_complex a,b;
    GSL_SET_COMPLEX(&a,3,4);//a=3+4i
    GSL_SET_COMPLEX(&b,6,8);//b=6+8i
    gsl_complex c = gsl_complex_add(a,b);
    printf("a+b\treal : %f image : %f\n",c.dat[0],c.dat[1]);
    c = gsl_complex_sub(a,b);
    printf("a-b\treal : %f image : %f\n",c.dat[0],c.dat[1]);
    c = gsl_complex_mul(a,b);
    printf("a*b\treal : %f image : %f\n",c.dat[0],c.dat[1]);
    c = gsl_complex_div(a,b);
    printf("a/b\treal : %f image : %f\n",c.dat[0],c.dat[1]);
    // system("PAUSE");
    return 0;
}