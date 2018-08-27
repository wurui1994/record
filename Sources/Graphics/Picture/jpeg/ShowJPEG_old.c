#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <jpeglib.h>
//
typedef unsigned char byte;
typedef struct
{
	int Width, Height;
	byte *Data;
} Image;
Image img;
int num = 0;
typedef struct
{
	int length;
	char **strs;
} vecstr;
vecstr vs;
void initiate()
{
	char filename[FILENAME_MAX] = "test.txt";
	vs.length = 0;
	vs.strs = NULL;
	FILE *fp = fopen(filename, "rt");
	while (!feof(fp))
	{
		char *line = (char *)malloc(BUFSIZ);
		memset(line, 0, BUFSIZ);
		fgets(line, BUFSIZ, fp);
		line[strlen(line) - 1] = '\0'; //去除\n
		//puts(line);
		vs.strs = (char **)realloc(vs.strs, ++(vs.length) * sizeof(char *));
		vs.strs[vs.length - 1] = line;
	}
	fclose(fp);
	//printf("%d\n",vs.length);
}
void swap(byte *a, byte *b)
{
	byte tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void readjpeg(const char filename[], Image *img)
{
	//Read the file
	FILE *fp = fopen(filename, "rb");
	if (!fp)
		return;
	//
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPARRAY buffer;
	//unsigned char *src_buff;
	unsigned char *point;

	cinfo.err = jpeg_std_error(&jerr); //一下为libjpeg函数，具体参看相关文档
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	unsigned long width = cinfo.output_width;
	unsigned long height = cinfo.output_height;
	unsigned short depth = cinfo.output_components;

	img->Data = (byte *)malloc(width * height * depth);
	img->Width = width, img->Height = height;
	byte *src_buff = img->Data;
	//src_buff=new unsigned char[width*height*depth];
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);

	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width * depth, 1);

	point = src_buff;
	while (cinfo.output_scanline < height)
	{
		jpeg_read_scanlines(&cinfo, buffer, 1); //读取一行jpg图像数据到buffer
		memcpy(point, *buffer, width * depth);  //将buffer中的数据逐行给src_buff
		point += width * depth;					//一次改变一行
	}
	//write_bmp_header(&cinfo);            //写bmp文件头
	//write_bmp_data(&cinfo,src_buff);    //写bmp像素数据
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	//delete[] src_buff;
	//
	//fread(pimg, w*h* 3, 1, fp);
	fclose(fp);
	//
	///Two Steps,From ppm-order to bmp-order.
	//RGB2BGR,swap B and R.
	byte *pimg = img->Data;
	int base;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			base = width * i * 3 + j * 3;
			swap(pimg + base + 0, pimg + base + 2);
		}
	}
	//Flip,swap Top and Bottom.
	int size = width * 3;
	byte *line = (byte *)malloc(size);
	for (int k = 0; k < height / 2; k++)
	{
		memcpy(line, pimg + size * k, size);
		memcpy(pimg + size * k, pimg + size * (height - 1 - k), size);
		memcpy(pimg + size * (height - 1 - k), line, size);
	}
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	HDC hdc = GetDC(hwnd);
	PAINTSTRUCT ps;
	RECT rect;
	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	case WM_PAINT:
	{
		//hdc=BeginPaint(hwnd,&ps);
		GetClientRect(hwnd, &rect);
		//printf("%d %d",rect.right-rect.left,rect.bottom-rect.top);
		//RedrawWindow(hwnd,&rect,0,0);
		if (num == vs.length - 1)
			exit(0);
		readjpeg(vs.strs[num++], &img);
		bmi.bmiHeader.biWidth = img.Width;
		bmi.bmiHeader.biHeight = img.Height;
		//SetDIBitsToDevice(hdc, 0, 0, img.Width, img.Height,0, 0, 0, img.Height, img.Data, &bmi, DIB_RGB_COLORS);
		SetStretchBltMode(hdc, STRETCH_DELETESCANS);
		StretchDIBits(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0, 0, img.Width, img.Height, img.Data, &bmi, DIB_RGB_COLORS, SRCCOPY);
		free(img.Data);
		//EndPaint(hwnd,&ps);
	}
	break;
	default:
		return DefWindowProc(hwnd, msg, w, l);
	}
	return 0;
}
DWORD WINAPI ShowImage(LPVOID lp)
{
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
						300, 120, 640, 480,
						NULL, NULL, hInstance, NULL);
	//The message loop.
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
void ImageShow()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ShowImage(0), 0, 0, 0);
}

int main(int argc, char *argv[])
{
	initiate();
	//readjpeg("016.jpg", &img);
	ImageShow();
	return 0;
}