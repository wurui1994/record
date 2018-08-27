/*
 1.比较减数与被减数的长度,确定正负号
 2.模拟笔算
      (1)a[i]==b[j]
      (2)a[i]<b[j] //退位
      (3)a[i]>b[j]
*/
#include <iostream>
#include <string>
using namespace std;
string jianfa(string a, string b)
{
	string c = "", ans = "", t;
	int flag = 0, k = 0; //flag退位的标志
	bool flag2 = false;  //结果正负的标志
	if (a.length() < b.length() || (a.length() == b.length() && a.compare(b) < 0))
	{
		t = a;
		a = b;
		b = t;
		flag2 = true;
	}
	int i = a.length() - 1, j = b.length() - 1;
	while (i >= 0 && j >= 0)
	{
		if (a[i] + flag > b[j])
		{
			c += a[i] + flag - b[j] + '0';
			flag = 0;
		}
		else if (a[i] + flag == b[j])
		{
			c += '0';
			flag = 0;
		}
		else
		{
			c += (a[i] - '0') + flag + 10 - (b[j] - '0') + '0';
			flag = -1;
		}
		i--;
		j--;
		k++;
	}
	while (i >= 0)
	{
		if (a[i] + flag < '0')
		{
			c += a[i] + flag + 10 + '0';
			flag = -1;
		}
		else
		{
			c += a[i] + flag;
			flag = 0;
		}
		i--, k++;
	}
	int len = k - 1;
	while (c[len] == '0' && len > 0)
		len--; //检索高位
	for (j = 0; j <= len; j++)
		ans += c[j];
	if (flag2)
	{
		ans += '-'; //结果正负判断
	}
	char tt;
	for (i = 0, j = ans.length() - 1; i < j; i++, j--)
	{ //倒置
		tt = ans[i];
		ans[i] = ans[j];
		ans[j] = tt;
	}
	return ans;
}
int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		cout << jianfa(a, b) << endl;
	}
	return 0;
}