#include <windows.h>
#include <gdiplus.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma comment(lib, "gdiplus")
using namespace std;
using namespace Gdiplus;

vector<string> vec;
int num = 0;
BITMAPINFO bmi;
int w;
int h;
int size;
UINT *pixels;
BitmapData *bitmapData = new BitmapData;
Bitmap *bitmap;
Rect *rect;
//
void DrawScene(const char *file)
{
	size_t len = strlen(file) + 1;
	size_t converted = 0;
	wchar_t *wstr = new wchar_t[len];
	mbstowcs_s(&converted, wstr, len, file, _TRUNCATE);
	bitmap = new Bitmap(wstr);

	w = bitmap->GetWidth(), h = bitmap->GetHeight();
	rect = new Rect(0, 0, w, h);

	// Lock a 5x3 rectangular portion of the bitmap for reading.
	bitmap->LockBits(rect, ImageLockModeRead, PixelFormat24bppRGB, bitmapData);
	//printf("The stride is %d.\n\n", bitmapData->Stride);
	// Display the hexadecimal value of each pixel in the 5x3 rectangle.
	pixels = (UINT *)bitmapData->Scan0;
	bitmap->UnlockBits(bitmapData);

	//cout<<w<<" "<<h<<endl;
	size = w * h * 3;
	//
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
}
//================================
void initiate()
{
	//
	ifstream ifs("test.txt");
	string temp;
	int tempr, tempt;
	while (!ifs.eof())
	{
		getline(ifs, temp);
		if (temp.length() > 4)
			vec.push_back(temp);
		//cout<<temp<<endl;
	}
	ifs.close();
	//cout<<vec.size()<<endl;
}
int main()
{
	static TCHAR szAppName[] = TEXT(" ");
	HWND hwnd;
	HDC hdc;
	MSG msg;
	WNDCLASS wndclass;
	int iCmdShow = 1;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = DefWindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = 0;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		//return;
	}

	hwnd = CreateWindow(szAppName, TEXT(""), WS_OVERLAPPEDWINDOW,
						350, 120, 500, 500,
						NULL, NULL, hInstance, NULL);
	hdc = GetDC(hwnd);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	//
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	initiate();
	//
	while (TRUE)
	{
		// Sleep(40);//
		// if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
		// if (msg.message == WM_QUIT)break ;
		// TranslateMessage (&msg) ;
		// DispatchMessage (&msg) ;

		// } else {
		if (num == vec.size())
			return 0;
		DrawScene(vec[num].c_str());
		//SetDIBitsToDevice(hdc, 0, 0, w, h,
		//0, 0, 0, h, pixels, &bmi, DIB_RGB_COLORS);
		StretchDIBits(hdc, 0, 0, 500, 500, 0, 0, w, h, pixels, &bmi, DIB_RGB_COLORS, SRCCOPY);
		delete bitmap, rect;
		num++;
		//}
	}
	//delete bitmapData;
	GdiplusShutdown(gdiplusToken);
	return 0;
}