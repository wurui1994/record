#include <windows.h>

int main(int argc, char* argv[])
{
	HWND hwnd = FindWindow("Notepad++", 0);
	DWORD lpdw;
	GetWindowThreadProcessId(hwnd, &lpdw);
	printf("PID=%d\n", lpdw);
	return 0;
}