#include <windows.h>

int main(int argc, char* argv[])
{
	HWND hwnd = FindWindow("Notepad",0);
	RECT rc;
	GetWindowRect(hwnd, &rc);
	printf("%d %d\n",rc.left,rc.right);
	return 0;
}