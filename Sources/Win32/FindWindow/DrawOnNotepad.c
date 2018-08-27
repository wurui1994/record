

#include <windows.h>

#define NUM 100
int main()
{
	//MessageBox(0, "Hello", "test", 0);
	system("start notepad");
	Sleep(40);
	HWND hwnd = FindWindow("notepad",0);
	HDC hdc = GetDC(hwnd);
	POINT       apt[NUM];
	for (int i = 0; i < NUM; i++)
	{
		apt[i].x = i * 500 / NUM;
		apt[i].y = (int)(500 / 2 * (1 - sin(6.28 * i / NUM)));
	}
	while (1) {
		MoveToEx(hdc, 0, 500, NULL);
		LineTo(hdc, 500, 250);
		Polyline(hdc, apt, NUM);
		Sleep(40);
	}
	system("taskkill /im notepad.exe");
	return 0;
}

