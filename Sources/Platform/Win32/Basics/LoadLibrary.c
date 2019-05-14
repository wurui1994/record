#include <windows.h>
#include <stdio.h>

void TestLoadDLL(void)
{
	//加载动态连接库。
	HMODULE hDllLib = LoadLibraryA("kernel32.dll");
	if (hDllLib)
	{
		//获取动态连接库里的函数地址。
		FARPROC fpFun = GetProcAddress(hDllLib, "GetVersion");

		//调用函数运行。
		DWORD dwVersion = (*fpFun)();

		//获取WINDOWS的版本。
		DWORD dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
		DWORD dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

		//显示。
		TCHAR chBuf[BUFSIZ];
		ZeroMemory(chBuf, BUFSIZ);

		printf("显示版本：%d.%d\r\n",
			dwWindowsMajorVersion, dwWindowsMinorVersion);
		OutputDebugString(chBuf);

		//释放动态连接库。
		FreeLibrary(hDllLib);
	}
	else
	{
		puts("error");
	}

}
int main(int argc, char* argv[])
{
	TestLoadDLL();
	return 0;
}