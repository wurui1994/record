#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//
typedef unsigned char byte;
typedef struct
{
	int Width, Height;
	byte *Data;
} Image;
void swap(byte *a, byte *b)
{
	byte tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void readppmp6(const char filename[], Image *img)
{
	//Init Variables
	//char header[20];
	int w, h, c;

	//Read the file
	FILE *fp = fopen(filename, "rb");
	if (!fp)
		return;
	fscanf(fp, "P6\n%d %d\n%d\n", &w, &h, &c);
	img->Data = (byte *)malloc(w * h * 3);
	byte *pimg = img->Data;
	fread(pimg, w * h * 3, 1, fp);
	fclose(fp);
	//
	img->Width = w, img->Height = h;
	///Two Steps,From ppm-order to bmp-order.
	//RGB2BGR,swap B and R.
	int base;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			base = w * i * 3 + j * 3;
			swap(pimg + base + 0, pimg + base + 2);
		}
	}
	//Flip,swap Top and Bottom.
	int size = w * 3;
	byte *buffer = (byte *)malloc(size);
	for (int k = 0; k < h / 2; k++)
	{
		memcpy(buffer, pimg + size * k, size);
		memcpy(pimg + size * k, pimg + size * (h - 1 - k), size);
		memcpy(pimg + size * (h - 1 - k), buffer, size);
	}
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	default:
		return DefWindowProc(hwnd, msg, w, l);
	}
	return 0;
}
DWORD WINAPI ShowImage(Image img)
{
	//Init bmpinfo.
	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = img.Width;
	bmi.bmiHeader.biHeight = img.Height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	//Create the window
	static TCHAR szAppName[] = TEXT(" ");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	int iCmdShow = 1;
	HINSTANCE hInstance = NULL; //GetModuleHandle(NULL);
	//
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		//return;
	}
	hwnd = CreateWindow(szAppName, TEXT(""), WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
						NULL, NULL, hInstance, NULL);
	HDC hdc = GetDC(hwnd);
	//The message loop.
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		SetDIBitsToDevice(hdc, 0, 0, img.Width, img.Height,
						  0, 0, 0, img.Height, img.Data, &bmi, DIB_RGB_COLORS);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
void ImageShow(Image img)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ShowImage(img), 0, 0, 0);
}

int main(int argc, char *argv[])
{
	Image img;
	readppmp6("test.ppm", &img);
	ImageShow(img);
	return 0;
}