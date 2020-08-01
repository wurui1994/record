// BBP公式
// 圆周率pi的计算（精确到小数点后1000位）

#include <math.h>
#include <stdio.h>
#include <time.h>

double bbp(int n, int k, int l)
{
	int i;
	long b = 1;
	double c = 1;
	if (n > k)
	{
		for (i = n - k; i != 0; i--)
			b = (b * 16 + 0) % (8 * k + l);
		return (((double)b) / ((double)(8 * k + l)));
	}
	else if (n == k)
		return (((double)1) / ((double)(8 * k + l)));
	else
	{
		for (i = 0; i < (k - n); i++)
			c = c / 16;
		return (c / (8 * k + l));
	}
};

void pi(int m, int n, int p[])
{
	double a = 0;
	int k = 0;
	while (k < (n + 8))
	{
		a += 4 + 4 * bbp(n, k, 1) - 2 * bbp(n, k, 4) - bbp(n, k, 5) - bbp(n, k, 6);
		a = a - (int)a;
		k++;
	}
	for (k = 0; k < m; k++)
	{
		a *= 16;
		p[k] = (int)a;
		a = a - (int)a;
	}
}

void div(int p[])
{
	int i, j = 0;
	for (i = 0; i < 300; i++)
	{
		p[i] = j * 10000 + p[i];
		j = p[i] % 2;
		p[i] = p[i] / 2;
	}
}

void add(int a[], int b[])
{
	int i, j = 0;
	for (i = 299; i >= 0; i--)
	{
		a[i] = a[i] + b[i] + j;
		if (a[i] >= 10000)
		{
			a[i] -= 10000;
			j = 1;
		}
		else
			j = 0;
	}
}

void test()
{
	int i, j, p[1100] = {0}, r[300] = {0};
	short q[4000];
	for (i = 0; i < 125; i++)
		pi(8, i * 8, p + i * 8);
	for (i = 0; i < 1000; i++)
	{
		j = p[i];
		q[i * 4 + 3] = j % 2;
		j = j / 2;
		q[i * 4 + 2] = j % 2;
		j = j / 2;
		q[i * 4 + 1] = j % 2;
		j = j / 2;
		q[i * 4 + 0] = j % 2;
		p[i] = 0;
	}
	p[0] = 10000;
	for (i = 0; i < 4000; i++)
	{
		div(p);
		if (q[i])
			add(r, p);
	}
	printf("3.");
	for (i = 0; i < 250; i++)
	{
		if (r[i] < 10)
			printf("000");
		else if (r[i] < 100)
			printf("00");
		else if (r[i] < 1000)
			printf("0");
		printf("%d", r[i]);
	}
	printf("\n");
}

void calctime(void (*fun)(void))
{
	clock_t st, et;
	st = clock();
	fun();
	et = clock();
	printf("%f\n", (double)(et - st) / CLOCKS_PER_SEC);
}
/////////////////////////////////////////////////////////////
void main(int argc, char *argv[])
{
	calctime(test);
}