// Wallis公式精度控制
#include <stdio.h>
#include <math.h>
#define N 30 //精度控制
int a = 10000, k, n = N * 10 / 3, d, e, f[N * 10 / 3 + 1];
//
int main()
{
	for (int i = 0; i < n; i++)
		f[i] = 2 * a / 10;
	for (int i = 0; i < N / 4; i++)
	{
		for (d = 0, k = n; k > 1; k--)
		{
			printf("%d ", f[k]);
			d += f[k] * a;
			f[k] = d % (2 * k - 1);
			d = d / (2 * k - 1) * (k - 1); //n/(2n+1);
		}
		printf(" %.4d\n", e + d / a);
		e = d % a;
	}
}