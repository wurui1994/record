#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "jpeg")
#define true 1
#define false 0
typedef int bool;
//
typedef unsigned char byte;
typedef struct
{				  //32 bit color
	byte b, g, r; // A is alpha
} RGB;
typedef struct
{
	int Width, Height;
	byte *Data;
} Image;

typedef struct
{
	int length;
	char **strs;
} vecstr;
//
int num = 0;
Image src;
Image mid;
Image img;
vecstr vs;
//
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
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
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
#ifdef _WIN32
	//Flip,swap Top and Bottom.
	int size = width * 3;
	byte *line = (byte *)malloc(size);
	for (int k = 0; k < height / 2; k++)
	{
		memcpy(line, pimg + size * k, size);
		memcpy(pimg + size * k, pimg + size * (height - 1 - k), size);
		memcpy(pimg + size * (height - 1 - k), line, size);
	}
#endif
}
//那么访问一个点的函数可以写为：

void PicZoom0(Image Dst, Image Src)
{
	if ((0 == Dst.Width) || (0 == Dst.Height) || (0 == Src.Width) || (0 == Src.Height))
		return;
	for (long x = 0; x < Dst.Width; x++)
	{
		for (long y = 0; y < Dst.Height; y++)
		{
			long srcx = (x * Src.Width / Dst.Width);
			long srcy = (y * Src.Height / Dst.Height);
			Dst.Data[3 * x + 3 * Dst.Width * y + 0] = Src.Data[3 * srcx + 3 * Src.Width * srcy + 0];
			Dst.Data[3 * x + 3 * Dst.Width * y + 1] = Src.Data[3 * srcx + 3 * Src.Width * srcy + 1];
			Dst.Data[3 * x + 3 * Dst.Width * y + 2] = Src.Data[3 * srcx + 3 * Src.Width * srcy + 2];
		}
	}
}
RGB Pixels(Image img, int x, int y)
{
	RGB result;
	result.b = img.Data[3 * x + 3 * img.Width * y + 0];
	result.g = img.Data[3 * x + 3 * img.Width * y + 1];
	result.r = img.Data[3 * x + 3 * img.Width * y + 2];
	return result;
}
//访问一个点的函数，(x,y)坐标可能超出图片边界； //边界处理模式:边界饱和
RGB Pixels_Bound(Image pic, long x, long y)
{
	//assert((pic.width>0)&&(pic.height>0));
	bool IsInPic = true;
	if (x < 0)
	{
		x = 0;
		IsInPic = false;
	}
	else if (x >= pic.Width)
	{
		x = pic.Width - 1;
		IsInPic = false;
	}
	if (y < 0)
	{
		y = 0;
		IsInPic = false;
	}
	else if (y >= pic.Height)
	{
		y = pic.Height - 1;
		IsInPic = false;
	}
	RGB result = Pixels(pic, x, y);
	//if (!IsInPic) result.a=0;
	return result;
}
//
void Bilinear0(Image pic, float fx, float fy, RGB *result)
{
	long x = (long)fx;
	if (x > fx)
		--x; //x=floor(fx);
	long y = (long)fy;
	if (y > fy)
		--y; //y=floor(fy);

	RGB Color0 = Pixels_Bound(pic, x, y);
	RGB Color2 = Pixels_Bound(pic, x + 1, y);
	RGB Color1 = Pixels_Bound(pic, x, y + 1);
	RGB Color3 = Pixels_Bound(pic, x + 1, y + 1);

	float u = fx - x;
	float v = fy - y;
	float pm3 = u * v;
	float pm2 = u * (1 - v);
	float pm1 = v * (1 - u);
	float pm0 = (1 - u) * (1 - v);

	//result->a=(pm0*Color0.a+pm1*Color1.a+pm2*Color2.a+pm3*Color3.a);
	result->r = (pm0 * Color0.r + pm1 * Color1.r + pm2 * Color2.r + pm3 * Color3.r);
	result->g = (pm0 * Color0.g + pm1 * Color1.g + pm2 * Color2.g + pm3 * Color3.g);
	result->b = (pm0 * Color0.b + pm1 * Color1.b + pm2 * Color2.b + pm3 * Color3.b);
	//printf("%d %d  %d\n",result->b,result->b,result->b);
}

void PicZoom_Bilinear0(Image Dst, Image Src)
{
	if ((0 == Dst.Width) || (0 == Dst.Height) || (0 == Src.Width) || (0 == Src.Height))
		return;

	//	unsigned long dst_width=Dst.width;
	RGB rgb;
	for (unsigned long y = 0; y < Dst.Height; ++y)
	{
		float srcy = (y + 0.4999999) * Src.Height / Dst.Height - 0.5;
		for (unsigned long x = 0; x < Dst.Width; ++x)
		{
			float srcx = (x + 0.4999999) * Src.Width / Dst.Width - 0.5;
			Bilinear0(Src, srcx, srcy, &rgb);
			Dst.Data[3 * x + 3 * Dst.Width * y + 0] = rgb.b;
			Dst.Data[3 * x + 3 * Dst.Width * y + 1] = rgb.g;
			Dst.Data[3 * x + 3 * Dst.Width * y + 2] = rgb.r;
		}
		//((TUInt8*&)pDstLine)+=Dst.byte_width;
	}
}
#ifdef _WIN32
#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	//注意:GetDC会每次都刷新,而BeginPaint和EndPaint不会。
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
	case WM_CREATE:
	{

		//readjpeg(vs.strs[45], &src);
		img.Width = 400;
		img.Height = 400;
		img.Data = (byte *)malloc(400 * 400 * 3);
		//mid.Width=200;
		//mid.Height=200;
		//mid.Data=(byte*)malloc(200*200*3);
		//PicZoom0(mid,src);
		//PicZoom0(img,mid);
		//PicZoom_Bilinear0(img,src);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	case WM_PAINT:
		//hdc=BeginPaint(hwnd,&ps);
		//GetWindowRect(hwnd,&rect);
		//RedrawWindow(hwnd,&rect,0,0);
		//if(num==vs.length-1)exit(0);
		// readjpeg(vs.strs[num++], &src);
		readjpeg("test.jpg", &src);
		//PicZoom0(img,src);
		PicZoom_Bilinear0(img, src);
		bmi.bmiHeader.biWidth = img.Width;
		bmi.bmiHeader.biHeight = img.Height;
		SetDIBitsToDevice(hdc, 0, 0, img.Width, img.Height,
						  0, 0, 0, img.Height, img.Data, &bmi, DIB_RGB_COLORS);
		free(src.Data);
		//EndPaint(hwnd,&ps);
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
#endif
#ifdef __linux
//#else
#include <X11/Xlib.h>
#include <X11/Xutil.h>
char *addalpha(char *data, int w, int h)
{
	char *buffer = (char *)malloc(w * h * 4 * sizeof(char));
	for (int i = 0; i < w * h; i++)
	{
		buffer[4 * i + 0] = data[3 * i + 0];
		buffer[4 * i + 1] = data[3 * i + 1];
		buffer[4 * i + 2] = data[3 * i + 2];
	}
	//free(data);
	return buffer;
}

int main(int argc, char **argv)
{
	int win_b_color;
	int win_w_color;
	XEvent xev;
	Window window;
	GC gc;
	Display *display = XOpenDisplay(NULL);
	Visual *visual;
	XImage *ximage;
	win_b_color = BlackPixel(display, DefaultScreen(display));
	win_w_color = BlackPixel(display, DefaultScreen(display));
	window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 640, 480, 0, win_b_color, win_w_color);
	visual = DefaultVisual(display, 0);
	//XSelectInput(display, window, ExposureMask | KeyPressMask);
	XMapWindow(display, window);
	XFlush(display);
	gc = XCreateGC(display, window, 0, NULL);
	//XEvent event;
	initiate();
	img.Width = 400;
	img.Height = 400;
	img.Data = (byte *)malloc(400 * 400 * 3);
	while (1)
	{
		if (num == vs.length - 1)
			exit(0);
		readjpeg(vs.strs[num++], &src);
		PicZoom_Bilinear0(img, src);
		free(src.Data);
		char *image32 = (char *)img.Data;
		int width = img.Width;
		int height = img.Height;
		image32 = addalpha(image32, width, height);
		ximage = XCreateImage(display, visual, 24, ZPixmap, 0, image32, width, height, 32, 0);
		XPutImage(display, window, gc, ximage, 0, 0, 0, 0, width, height);
		free(image32);
	}
	free(img.Data);
	return 0;
}
#endif