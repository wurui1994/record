#include <stdio.h>
#include <windows.h>
//extern int add(int,int);
int main()
{
	HMODULE hm = LoadLibrary("add.dll");
	printf("%d\n", hm);
	FARPROC add = GetProcAddress(hm, "_ZN4test3addEii");
	printf("%d\n", add(2, 3));
	return 0;
}