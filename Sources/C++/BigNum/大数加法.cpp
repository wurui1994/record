//大数加法--模版(string 实现)
#include <iostream>
#include <string>
using namespace std;

string add(string a, string b)
{
	int i = a.length() - 1, j = b.length() - 1; //倒序相加
	int k = 0, flag = 0;						//flag 进位的标志
	string ans = "";
	while (i >= 0 && j >= 0)
	{
		ans += a[i] + b[j] - '0' + flag;
		flag = 0;
		if (ans[k] > '9')
		{
			flag = 1;
			ans[k] = ans[k] - 10;
		}
		i--, j--, k++;
	}
	while (i >= 0)
	{
		ans += a[i] + flag;
		flag = 0;
		if (ans[k] > '9')
		{
			flag = 1;
			ans[k] = ans[k] - 10;
		}
		i--, k++;
	}
	while (j >= 0)
	{
		ans += b[j] + flag;
		flag = 0;
		if (ans[k] > '9')
		{
			flag = 1;
			ans[k] = ans[k] - 10;
		}
		j--, k++;
	}
	if (flag)
	{ //连续进位的情况
		ans += (flag + '0');
		k++;
	}
	char t;
	for (i = 0, j = k - 1; i < j; i++, j--)
	{ //反转
		t = ans[i];
		ans[i] = ans[j];
		ans[j] = t;
	}
	return ans;
}
int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		cout << add(a, b) << endl;
	}
	return 0;
}