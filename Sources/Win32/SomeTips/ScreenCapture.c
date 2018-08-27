#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef unsigned char byte;
typedef struct tagImage {
	int Width,Height;
	byte *Data;
}Image;
void WriteBMP(Image img,const char* filename)
{
	FILE *fpBmp;
	int line=(img.Width*3%4==0)?(img.Width*3):(img.Width*3/4+1)*4;
	printf("%d\n",line);
	BITMAPFILEHEADER bmf= {
		0x4d42,img.Height*line+54,0,0,54
	};
	BITMAPINFOHEADER bmi= {40,img.Width,img.Height,1,3*8,0,
	                 img.Height*line,0,0,100,0
	                };
	fpBmp = fopen(filename,"wb");
	fwrite(&bmf,14,1,fpBmp);
	fwrite(&bmi,40,1,fpBmp);
	fwrite(img.Data,1,bmf.bfSize,fpBmp);
	fclose(fpBmp);
}
void Save(HWND hWnd)
{
	if (hWnd == NULL) return;

	RECT rectClient;
	GetClientRect(hWnd, &rectClient);
	int width = rectClient.right - rectClient.left;
	int height = rectClient.bottom - rectClient.top;

	// 通过内存DC复制客户区到DDB位图
	HDC hdcWnd = GetDC(hWnd);
	HBITMAP hbmWnd = CreateCompatibleBitmap(hdcWnd, width, height);
	HDC hdcMem = CreateCompatibleDC(hdcWnd);
	SelectObject(hdcMem, hbmWnd);
	BitBlt(hdcMem, 0, 0, width, height, hdcWnd, 0, 0, SRCCOPY);

	// 把窗口DDB转为DIB
	BITMAP bmpWnd;
	GetObject(hbmWnd, sizeof(BITMAP), &bmpWnd);
	BITMAPINFOHEADER bi; // 信息头
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpWnd.bmWidth;
	bi.biHeight = bmpWnd.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24; // 按照每个像素用32bits表示转换
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((bmpWnd.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpWnd.bmHeight; // 每一行像素位32对齐
	char *lpbitmap = (char*)malloc(dwBmpSize); // 像素位指针
	GetDIBits(hdcMem, hbmWnd, 0, (UINT)bmpWnd.bmHeight,lpbitmap,(BITMAPINFO*)&bi,DIB_RGB_COLORS);

	DeleteDC(hdcMem);
	DeleteObject(hbmWnd);
	ReleaseDC(hWnd, hdcWnd);
	Image img;
	img.Data=lpbitmap;
	img.Width=bi.biWidth;
	img.Height=bi.biHeight;
	WriteBMP(img,"test.bmp");
}

int main()
{
	Save(GetDesktopWindow());
}