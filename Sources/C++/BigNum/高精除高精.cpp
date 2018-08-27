/*大数除法---高精度除高精度*/
/*
   1.a.size<b.size 返回-1
   2.a.size=b.size && a-b<0 返回-1
   3.a.size=b.size && a-b=0 返回0
*/
#include <iostream>
#include <cstring>
#include <string>
#define N 2000
using namespace std;
//判断a.size 与b.size 的关系 以及做减法
int judge(char a[], int a1, char b[], int b1)
{
	int i;
	if (a1 < b1)
		return -1; //a.size<b.size
	bool flag = false;
	if (a1 == b1)
	{ //a.size==b.size && a<b
		for (i = a1 - 1; i >= 0; i--)
			if (a[i] > b[i])
				flag = true;
			else if (a[i] < b[i])
			{
				if (!flag)
					return -1;
			}
	}
	for (i = 0; i < a1; i++)
	{							 //前提b中b1---a1部分必须为'0'
		a[i] = a[i] - b[i] + 48; //'0'的ASCII为48
		if ((a[i] - '0') < 0)
		{
			a[i] = a[i] + 10;
			a[i + 1] = a[i + 1] - 1;
		}
	}
	for (i = a1 - 1; i >= 0; i--) //返回被除数的长度
		if (a[i] != '0')
			return (i + 1);
	return 0; //a.size==b.size&&a=b的情况
}
string division(string a, string b)
{
	char x1[N], x2[N];
	int ans[N];
	int a_len, b_len, i, j;
	a_len = a.length();
	b_len = b.length();
	/*初始化部分*/
	/*********************************************/
	memset(x1, '0', sizeof(x1));
	memset(x2, '0', sizeof(x2));
	memset(ans, 0, sizeof(ans));
	for (i = a_len - 1, j = 0; i >= 0; i--)
		x1[j++] = a[i];
	for (i = b_len - 1, j = 0; i >= 0; i--)
		x2[j++] = b[i];
	/*********************************************/
	/*分析部分*/
	/*********************************************/
	if (a_len < b_len)
		return "0";
	int temp_len = judge(x1, a_len, x2, b_len);
	if (temp_len < 0)
		return "0";
	if (temp_len == 0)
		return "1";
	ans[0]++; //减掉一次，商加1
	int ntimes = temp_len - b_len;
	if (ntimes < 0)
		return "1";
	else if (ntimes > 0)
	//扩充数位，加快减法。
	{
		for (i = temp_len - 1; i >= 0; i--)
			if (i >= ntimes)
				x2[i] = x2[i - ntimes];
			else
				x2[i] = '0';
	}
	b_len = temp_len;
	/*********************************************/
	/*加快除法的部分*/
	/********************************************/
	for (j = 0; j <= ntimes; j++)
	{
		int ntemp;
		while ((ntemp = judge(x1, temp_len, x2 + j, b_len - j)) >= 0)
		{
			temp_len = ntemp;
			ans[ntimes - j]++;
		}
	}
	/*********************************************/
	/*处理最后结果进位部分*/
	/*********************************************/
	for (i = 0; i < N; i++)
		if (ans[i] >= 10)
		{
			ans[i + 1] += ans[i] / 10;
			ans[i] %= 10;
		}
	/*********************************************/
	/*返回string类型*/
	/*********************************************/
	int k = N - 1;
	string c = "";
	while (ans[k] == 0 && k > 0)
		k--;
	for (i = k; i >= 0; i--)
		c += (ans[i] + '0');
	/*********************************************/
	return c;
}
int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		cout << division(a, b) << endl;
	}
	return 0;
}