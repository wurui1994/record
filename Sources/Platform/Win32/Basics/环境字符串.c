#include <windows.h>
#include <stdio.h>
int main()
{
	LPTSTR lpszVariable;
	LPTCH lpvEnv;
	//获得环境变量内存块的指针
	lpvEnv = GetEnvironmentStrings();
	if(lpvEnv == NULL) {
		printf("GetEnvironmentStrins failed(%d)\n", GetLastError());
		return 0;
	}
	//环境变量字符串是以NULL分隔的，内存块以NULL结尾
	lpszVariable = (LPTSTR)lpvEnv;
	while(*lpszVariable) {
		printf("%s\n", lpszVariable);
		lpszVariable += lstrlen(lpszVariable) + 1;   //移动指针
	}
	FreeEnvironmentStrings(lpvEnv);
	system("pause");
	return 1;
}