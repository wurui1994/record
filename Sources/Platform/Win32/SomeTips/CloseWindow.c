#include <windows.h>

int main(int argc, char* argv[])
{
	HWND hwnd = FindWindow("Notepad", 0);
	CloseWindow(hwnd);//最小化
	//OpenIcon(hwnd);//恢复状态
	return 0;
}