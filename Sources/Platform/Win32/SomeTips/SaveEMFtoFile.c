//请复制到MSPaint或Word查看。
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define Random (rand()%256)
void DrawEMF(HDC hdc)
{
	// MoveToEx(hdc, 0,0, NULL);
	// LineTo(hdc, 200, 100);
	RECT rect;
	static HFONT hFont;
	int h=24;
	hFont=CreateFont(h,0,0,0,0,0,0,0,1,0,0,0,0,"Consolas");
	SelectObject(hdc,hFont);
	char string[]="Hello World!\n你好,世界!Hello World!\n你好,世界!Hello World!\n你好,世界!Hello World!\n你好,世界!";
	for(int i=0; i<640/h; i++) {
		SetTextColor(hdc,RGB(Random,Random,Random));
		TextOut(hdc,0,i*h,string,strlen(string));
	}
}
int main()
{
	int cxMms, cyMms, cxPix, cyPix;
	int width = 1000;
	int height = 640;
	
	HWND hwndClient=GetDesktopWindow();
	HDC hdc = GetDC(hwndClient);
	cxMms = GetDeviceCaps (hdc, HORZSIZE);
	cyMms = GetDeviceCaps (hdc, VERTSIZE);
	cxPix = GetDeviceCaps (hdc, HORZRES);
	cyPix = GetDeviceCaps (hdc, VERTRES);
	ReleaseDC(hwndClient, hdc);
	printf("%d %d %d %d\n",cxMms,cyMms,width*cxMms * 100 / cxPix,cyPix);
	RECT rcImg= {0,0,(width-1)*cxMms * 100 / cxPix,(height-1)*cyMms * 100 / cyPix};
	HDC dc = CreateEnhMetaFile(NULL, NULL, &rcImg, (LPSTR)NULL);
	DrawEMF(dc);
	HENHMETAFILE hemf= CloseEnhMetaFile(dc);
	// OpenClipboard(0);
	// EmptyClipboard();
	// SetClipboardData(CF_ENHMETAFILE, hemf);
	// CloseClipboard();
	return 0;
}