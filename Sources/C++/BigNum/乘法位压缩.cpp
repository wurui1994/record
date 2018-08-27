#include <iostream>
#include <cstring>
#include <cstdio>
#define LL __int64
#define N 15000
#define M 50005
#define MOD 1000000000 //模
#define wei 9		   //压的位数
using namespace std;

LL a[N], b[N], ans[N];
char c[M], d[M];
/*************存储处理部分******************/
int StrToNum(char t[], LL tt[]) //返回存储长度
{
	int len = 0, t_len = strlen(t);
	int i, cnt = 1;
	LL d = 1, temp = 0;
	for (i = t_len - 1; i >= 0; i--)
	{
		temp += (t[i] - '0') * d;
		if (cnt == wei)
		{
			tt[len++] = temp;
			temp = 0;
			cnt = d = 1;
		}
		else
		{
			cnt++;
			d = d * 10;
		}
	}
	tt[len++] = temp;
	//for(i=0; i<len; i++)
	//   printf("%I64d ", tt[i]);
	//cout<<endl;
	return len;
}
/************************************/
/************乘法部分*************/
void mult(char c[], char d[])
{
	int a_len, b_len, i, j;
	LL flag, temp;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(ans, 0, sizeof(ans));
	a_len = StrToNum(c, a);
	b_len = StrToNum(d, b);
	for (i = 0; i < a_len; i++)
	{
		flag = 0;
		for (j = 0; j < b_len; j++)
		{

			temp = ans[i + j] + a[i] * b[j] + flag;
			//    printf("%I64d\n ", temp);
			ans[i + j] = temp % MOD;
			flag = temp / MOD;
		}
		while (flag)
		{
			temp = ans[i + j] + flag;
			ans[i + j] = temp % MOD;
			flag = temp / MOD;
		}
	}
	/***********************************/
	/***********输出部分**************/
	a_len = a_len + b_len + 2;
	while (!ans[a_len] && a_len > 0)
		a_len--;
	if (a_len >= 0)
		printf("%I64d", ans[a_len--]);
	while (a_len >= 0)
		printf("%09I64d", ans[a_len--]);
	printf("\n");
	/*********注意输出格式的控制***************/
}
/**************************************/
/************主函数部分***************/
int main()
{
	while (scanf("%s%s", c, d) != EOF)
	{
		mult(c, d);
	}
	return 0;
}
/**************************************/