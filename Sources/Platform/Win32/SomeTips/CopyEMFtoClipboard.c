#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define Random (rand() % 256)
void DrawEMF(HDC hdc)
{
	// MoveToEx(hdc, 0,0, NULL);
	// LineTo(hdc, 200, 100);
	RECT rect;
	static HFONT hFont;
	int h = 24;
	hFont = CreateFont(h, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, "Consolas");
	SelectObject(hdc, hFont);
	char string[] = "Hello World!\n你好,世界!Hello World!\n你好,世界!Hello World!\n你好,世界!Hello World!\n你好,世界!";
	for (int i = 0; i < 640 / h; i++)
	{
		SetTextColor(hdc, RGB(Random, Random, Random));
		TextOut(hdc, 0, i * h, string, strlen(string));
	}
}
int main()
{
	RECT rcImg = {0, 0, 22000, 15000};
	HDC hdc = CreateEnhMetaFile(NULL, NULL, &rcImg, (LPSTR)NULL);
	DrawEMF(hdc);
	HENHMETAFILE hemf = CloseEnhMetaFile(hdc);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_ENHMETAFILE, hemf);
	CloseClipboard();
	return 0;
}