/*高精度除低精度求商模板*/
/*大数除法 ------除数为int范围*/
#include <iostream>
#define N 1000
using namespace std;
void division(char *src, int n)
{
	int len = strlen(src), i, k, t = 0, s = 0;
	char dest[N];
	bool flag = true; //商是否有了第一个有效位，防止商首部一直出现0
	for (i = 0, k = 0; i < len; i++)
	{
		t = s * 10 + (src[i] - 48); //新余数
		if (t / n > 0 || t == 0)
		{ //余数为0要修改商
			dest[k++] = t / n + 48, s = t % n, flag = false;
		}
		else
		{ //不够除，修改余数
			s = t;
			if (!flag) //商已经有有效位了，补零
				dest[k++] = '0';
		}
	}
	for (i = 0; i < k; i++)
		cout << dest[i];
	cout << endl;
}
int main()
{
	char num[N];
	int n;
	while (scanf("%s%d", num, &n) != EOF)
	{
		division(num, n);
	}
	return 0;
}