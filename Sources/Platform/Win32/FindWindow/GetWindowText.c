#include <windows.h>

int main(int argc, char* argv[])
{
	HWND hwnd = FindWindow("Notepad++",0);
	TCHAR lpString[128];
	GetWindowText(hwnd,lpString,128);
	printf("%s\n",lpString);
	printf("%d\n", GetWindowTextLength(hwnd));
	return 0;
}