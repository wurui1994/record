#include <iostream>
#include <string>
using namespace std;

//大数加法
string add(string a, string b)
{
	int i = a.length() - 1, j = b.length() - 1;
	int k = 0, flag = 0; //flag 进位的标志
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
	{
		t = ans[i];
		ans[i] = ans[j];
		ans[j] = t;
	}
	return ans;
}
//大数乘法
string chengfa(string a, string b)
{
	string ans = "0", c;
	int a_len = a.length() - 1, b_len = b.length() - 1, i, j, t, k;
	int flag; //标志进位
	char ch;
	for (i = a_len; i >= 0; i--)
	{
		flag = 0;
		c = "";
		for (j = i; j < a_len; j++)
			c += '0'; //扩充位数
		for (j = b_len; j >= 0; j--)
		{
			t = (b[j] - '0') * (a[i] - '0') + flag;
			flag = t / 10;
			c += (t % 10 + '0');
		}
		if (flag)
			c += (flag + '0');
		for (j = 0, k = c.size() - 1; j < k; j++, k--)
		{ //反转
			ch = c[j];
			c[j] = c[k];
			c[k] = ch;
		}
		ans = add(ans, c);
	}
	if (ans[0] == '0')
		return "0"; //排除0*x=00**0的情况
	return ans;
}
int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		cout << chengfa(a, b) << endl;
	}
	return 0;
}