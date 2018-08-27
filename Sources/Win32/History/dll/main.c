#include <stdio.h>
#include <windows.h>
extern int add(int,int);
int main()
{
	HMODULE hm = LoadLibrary("add.dll");
	FARPROC add = GetProcAddress(hm, "º¯Êý");
	printf("%d\n", add(2,3));
	return 0;
}