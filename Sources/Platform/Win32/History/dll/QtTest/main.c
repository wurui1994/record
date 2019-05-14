#include <stdio.h>
#include <windows.h>
//extern int add(int,int);
int main()
{
	HMODULE hm = LoadLibrary("Qt5Core.dll");
	printf("%d\n", hm);
	FARPROC add = GetProcAddress(hm, "_ZN7QString15fromUtf8_helperEPKci");
	printf("%s\n", add("hello",6));
	return 0;
}