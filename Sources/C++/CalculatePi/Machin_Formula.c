// 马青公式
/*一个计算π的c程序
======================================

由于大多数计算机内置算法有一定精度限制，你想计算那么多位就会产生问题。
这里有一个c程序，允许计算要多少有多少。但马青公式在试图计算亿位时不理想。
下面就是这个程序。超过万位时此程序就不能胜任了。而Jason Chen的程序可算到10万位！
目前最快的方法是Chudnovsky、Ramanujan和金田康正的高斯-勒让德算法。
*/
///////////////////////////////////////////////////////////////////////////

/****************************************/
/* Compute pi to arbitrary precision    */
/* Author Roy Williams February 1994    */
/* Uses Machin's formula...             */
/* pi/4 = 4 arctan(1/5) - arctan(1/239) */
/****************************************/
/* compile with cc -O -o pi pi.c        */
/* run as "pi 1000"                     */
/****************************************/
/* The last few digits may be wrong.......... */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASE 10000
int nblock;
int *tot;
int *t1;
int *t2;
int *t3;

void copy(int *result, int *from)
{
	int i;
	for (i = 0; i < nblock; i++)
		result[i] = from[i];
}

int zero(int *result)
{
	int i;
	for (i = 0; i < nblock; i++)
		if (result[i])
			return 0;
	return 1;
}

void add(int *result, int *increm)
{
	int i;
	for (i = nblock - 1; i >= 0; i--)
	{
		result[i] += increm[i];
		if (result[i] >= BASE)
		{
			result[i] -= BASE;
			result[i - 1]++;
		}
	}
}

void sub(int *result, int *decrem)
{
	int i;
	for (i = nblock - 1; i >= 0; i--)
	{
		result[i] -= decrem[i];

		if (result[i] < 0)
		{
			result[i] += BASE;
			result[i - 1]--;
		}
	}
}

void mult(int *result, int factor)
{
	int i, carry = 0;
	for (i = nblock - 1; i >= 0; i--)
	{
		result[i] *= factor;
		result[i] += carry;
		carry = result[i] / BASE;
		result[i] %= BASE;
	}
}

void divide(int *result, int denom)
{
	int i, carry = 0;

	for (i = 0; i < nblock; i++)
	{
		result[i] += carry * BASE;
		carry = result[i] % denom;
		result[i] /= denom;
	}
}

void set(int *result, int rhs)
{
	int i;
	for (i = 0; i < nblock; i++)
		result[i] = 0;
	result[0] = rhs;
}

void print(int *result)
{
	int i, k;
	char s[10];
	printf("%1d.\n", result[0]);
	for (i = 1; i < nblock; i++)
	{
		sprintf(s, "%4d ", result[i]);
		for (k = 0; k < 5; k++)
			if (s[k] == ' ')
				s[k] = '0';
		printf("%c%c%c%c", s[0], s[1], s[2], s[3]);
		if (i % 15 == 0)
			printf("\n");
	}
	printf("\n");
}

void arctan(int *result, int *w1, int *w2, int denom, int onestep)
{
	int denom2 = denom * denom;
	int k = 1;

	set(result, 1);
	divide(result, denom);
	copy(w1, result);

	do
	{
		if (onestep)
			divide(w1, denom2);
		else
		{
			divide(w1, denom);
			divide(w1, denom);
		}
		copy(w2, w1);
		divide(w2, 2 * k + 1);
		if (k % 2)
			sub(result, w2);
		else
			add(result, w2);
		k++;
	} while (!zero(w2));
}

void test()
{
	int ndigit = 10000; /*位数可以自己试改，如：1000....*/
	//10000位1秒,40000位16秒.
	/*
	 if(argc == 2)
	               ndigit = atoi(argv[1]);
	       else {
	               fprintf(stderr, "Usage: %s ndigit/n", argv[0]);
	               fprintf(stderr, "(Assuming 10000 digits)/n");
	       }
	*/
	if (ndigit < 20)
		ndigit = 20;
	nblock = ndigit / 4;
	tot = (int *)malloc(nblock * sizeof(int));
	t1 = (int *)malloc(nblock * sizeof(int));
	t2 = (int *)malloc(nblock * sizeof(int));
	t3 = (int *)malloc(nblock * sizeof(int));
	if (!tot || !t1 || !t2 || !t3)
	{
		fprintf(stderr, "Not enough memory/n");
		exit(1);
	}

	arctan(tot, t1, t2, 5, 1);
	mult(tot, 4);
	arctan(t3, t1, t2, 239, 2);
	sub(tot, t3);
	mult(tot, 4);
	print(tot);
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