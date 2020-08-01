// 级数求和
#include <stdio.h>
#include <math.h>
#define N 100 //精度控制
//e num=1;den=k;
//pi/2 num=k;den=2*k+1;
#define num(k) (1)
#define den(k) (k)
int a = 10, k, n = N * 10 / 3, d, e, f[N * 10 / 3];
//
int main()
{
	for (int i = 0; i < n; i++)
		f[i] = a / 10;
	for (int i = 0; i < N / 4; i++)
	{
		for (d = 0, k = n; k >= 1; k--)
		{
			//printf("(%d %d %d) ",f[k],2*k-1,d);
			d += f[k - 1] * a;
			f[k - 1] = d % den(k);
			d = d / den(k) * num(k); //n/(2n+1);
		}
		if (i != 0)
			printf("%.1d", e + d / a);
		e = d % a;
	}
}