

//计算圆周率的C++程序(30000位)

#include <stdlib.h>
#include <math.h>
#include <memory.h>
#define N 10000
//using namespace std;
void mult(int *a, int b, int *s)
{
	for (int i = N, c = 0; i >= 0; i--)
	{
		int y = a[i] * b + c;
		c = y / 10;
		s[i] = y % 10;
	}
}

void divi(int *a, int b, int *s)
{
	for (int i = 0, c = 0; i <= N; i++)
	{
		int y = a[i] + c * 10;
		c = y % b;
		s[i] = y / b;
	}
}

void incr(int *a, int *b, int *s)
{
	for (int i = N, c = 0; i >= 0; i--)
	{
		int y = a[i] + b[i] + c;
		c = y / 10;
		s[i] = y % 10;
	}
}

int eqs(int *a, int *b)
{
	int i = 0;
	while (a[i] == b[i] && i <= N)
		i++;
	return i > N;
}

void print(int *pi)
{
	printf("%1d.\n", *pi);
	for (int i = 1; i <= N; i++)
	{
		printf("%d", pi[i]);
		if (i % 10 == 0)
			printf(" ");
		if (i % 70 == 0)
			printf("\n");
	}
};

//int main(int argc, char *argv[])
void test()
{
	int lpi[N + 1], lls[N + 1], lsl[N + 1], lp[N + 1];
	int *pi = lpi, *ls = lls, *sl = lsl, *p = lp;
	int i;
	memset(pi, 0, sizeof(lpi));
	memset(ls, 0, sizeof(lls));
	memset(sl, 0, sizeof(lsl));
	memset(p, 0, sizeof(lp));
	*pi = *ls = *sl = 1;
	for (i = 1; i < N; i++)
	{
		mult(ls, i, sl);
		divi(sl, 2 * i + 1, ls);
		incr(pi, ls, p);
		if (eqs(pi, p))
			break;
		int *t;
		t = p;
		p = pi;
		pi = t;
		//print(pi);
	}
	mult(p, 2, pi);
	print(pi);
	printf("\n\nSUCCESS!\n");
	//return EXIT_SUCCESS;
}

#include <time.h>
int calctime(void (*fun)(void))
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
