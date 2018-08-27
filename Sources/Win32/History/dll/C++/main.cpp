#include <stdio.h>
#include <windows.h>
typedef int (*addproc)(int,int);
int main()
{
	HMODULE hm = LoadLibrary("add.dll");
	printf("%d\n", hm);
	addproc add = (addproc)GetProcAddress(hm, "_ZN4test3addEii");
	printf("%d\n", add(2, 3));
	return 0;
}