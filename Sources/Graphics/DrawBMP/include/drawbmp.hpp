#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define Random rand() % 255
#define Length(x) (sizeof(x) / sizeof(x[0]) / 3)
const float PI = 3.1415926536;
typedef unsigned char byte;
int iWidth, iHeight;
BYTE *PImage;
BITMAPINFO bmi;
//
typedef float vector3[3];
//三维点数组结构
struct PointArray
{
	int length;
	float *x, *y, *z;
};
//
inline void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}
//
DWORD WINAPI ImageShow(LPVOID)
{
	static TCHAR szAppName[] = TEXT(" ");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	int iCmdShow = 1;
	HINSTANCE hInstance = NULL; //GetModuleHandle(NULL);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = DefWindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		//return;
	}
	int nScreenWidth, nScreenHeight;
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int PosX, PosY, WndW, WndH;
	if (iWidth > nScreenWidth)
	{
		PosX = 0;
		WndW = nScreenWidth;
	}
	else
	{
		PosX = (nScreenWidth - iWidth - 6) / 2;
		WndW = iWidth + 6;
	}
	if (iHeight > nScreenHeight)
	{
		PosY = 0;
		WndH = nScreenHeight;
	}
	else
	{
		PosY = (nScreenHeight - iHeight - 28) / 2;
		WndH = iHeight + 28;
	}

	hwnd = CreateWindow(szAppName, TEXT(""), WS_SYSMENU,
						PosX, PosY, WndW, WndH,
						NULL, NULL, hInstance, NULL);
	HDC hdc = GetDC(hwnd);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	//
	while (TRUE)
	{
		Sleep(40); //降低CPU占用率
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SetDIBitsToDevice(hdc, 0, 0, iWidth, iHeight,
							  0, 0, 0, iHeight, PImage, &bmi, DIB_RGB_COLORS);
		}
	}
	return msg.wParam;
}

//
//
class Image
{
  public:
	int Width, Height, Size;
	byte *Data;
	int ox, oy;
	int red, green, blue;
	float xscale, yscale;
	//初始化位图矩阵bitmap
	Image(int w, int h)
	{
		//
		this->ox = 0, this->oy = 0;
		this->red = 0, this->green = 255, this->blue = 0;
		this->xscale = 1.0, this->yscale = 1.0;
		//
		this->Width = w, this->Height = h;
		//
		this->Data = new byte[w * h * 3];
		for (int i = 0; i < w * h * 3; i++)
		{
			this->Data[i] = 0;
		}
	}
	Image &operator=(const Image &image)
	{
		this->Width = image.Width;
		this->Height = image.Height;
		this->Size = image.Width * image.Height * 3;
		for (int i = 0; i < this->Size; i++)
		{
			this->Data[i] = image.Data[i];
		}
		return *this;
	}
	void Rand()
	{
		for (int i = 0; i < this->Size; i++)
		{
			this->Data[i] = rand() % 255;
		}
	}
	//设置背景色
	void SetBgColor(int r, int g, int b)
	{
		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width * 3;)
			{
				this->Data[i * this->Width * 3 + j++] = b;
				this->Data[i * this->Width * 3 + j++] = g;
				this->Data[i * this->Width * 3 + j++] = r;
			}
		}
	}
	void ClearGraph()
	{
		memset(PImage, 0, this->Width * this->Height * 3);
	}
	//设置坐标原点
	void SetOrigin(int x, int y)
	{
		ox = x, oy = y;
	}
	//设置缩放比例
	void SetScale(float x, float y)
	{
		xscale = x, yscale = y;
	}
	//设置像素点为指定的RGB值
	void SetPixel(int x, int y)
	{
		x = ox + x * xscale;
		y = oy + y * yscale;
		if ((x < 0 || x > this->Width) || (y < 0 || y > this->Height))
			return;
		this->Data[y * this->Width * 3 + x * 3] = blue;
		this->Data[y * this->Width * 3 + x * 3 + 1] = green;
		this->Data[y * this->Width * 3 + x * 3 + 2] = red;
	}
	//设置将要使用的RGB颜色值
	void SetColor(int r, int g, int b)
	{
		red = r;
		green = g;
		blue = b;
	}

	/*二维绘图部分：主要是基本图元的算法*/
	//Bresenham line

	void BresenhamLine(int x1, int y1, int x2, int y2)
	{
		int dx = x2 - x1, dy = y2 - y1, inc, pi;
		inc = ((dx * dy) >= 0) ? 1 : -1;
		if (abs(dx) > abs(dy))
		{
			if (dx < 0)
			{
				swap(x1, x2), swap(y1, y2);
				dx = -dx, dy = -dy;
			}
			dy = (dy > 0) ? dy : -dy;
			pi = 2 * dy - dx;
			while (x1++ <= x2)
			{
				SetPixel(x1 - 1, y1);
				if (pi < 0)
					pi += 2 * dy;
				else
				{
					y1 += inc;
					pi += 2 * (dy - dx);
				}
			}
		}
		else
		{
			if (dy < 0)
			{
				swap(x1, x2), swap(y1, y2);
				dx = -dx, dy = -dy;
			}
			dx = (dx > 0) ? dx : -dx;
			pi = 2 * dx - dy;
			while (y1++ < y2)
			{
				SetPixel(x1, y1 - 1);
				if (pi < 0)
					pi += 2 * dx;
				else
				{
					x1 += inc;
					pi += 2 * (dx - dy);
				}
			}
		}
	}
	//中点画圆法
	void MidCircle(int x1, int y1, int r)
	{
		int x, y;
		float d;
		x = 0;
		y = r;
		d = 5.0 / 4 - r;
		while (x <= y)
		{
			SetPixel(x1 + x, y1 + y);
			SetPixel(x1 + x, y1 - y);
			SetPixel(x1 - x, y1 + y);
			SetPixel(x1 - x, y1 - y);
			SetPixel(x1 + y, y1 + x);
			SetPixel(x1 + y, y1 - x);
			SetPixel(x1 - y, y1 + x);
			SetPixel(x1 - y, y1 - x);
			if (d < 0)
				d += x * 2.0 + 3;
			else
			{
				d += 2.0 * (x - y) + 5;
				y--;
			}
			x++;
		}
	}
	//中点画圆[填充]
	void FillCircle(int x1, int y1, int r)
	{
		int x, y;
		float d;
		x = 0;
		y = r;
		d = 5.0 / 4 - r;
		while (x <= y)
		{
			BresenhamLine(x1 + x, y1 + y, x1 + x, y1 - y);
			BresenhamLine(x1 - x, y1 + y, x1 - x, y1 - y);
			BresenhamLine(x1 + y, y1 + x, x1 + y, y1 - x);
			BresenhamLine(x1 - y, y1 + x, x1 - y, y1 - x);
			if (d < 0)
				d += x * 2.0 + 3;
			else
			{
				d += 2.0 * (x - y) + 5;
				y--;
			}
			x++;
		}
	}
	//Bresenham画圆算法
	void BresenhamCircle(int x1, int y1, int r)
	{
		float x, y, d, d1, d2;
		x = 0;
		y = r;
		d = 2 * (1 - r);
		while (y >= 0)
		{
			SetPixel(x + x1, y + y1);  //顺时针第一四分圆部分
			SetPixel(-x + x1, y + y1); //其余的3个四分圆
			SetPixel(-x + x1, -y + y1);
			SetPixel(x + x1, -y + y1);
			if (d < 0)
			{ //从H、D、V三个点中做选择
				d1 = 2 * (d + y) - 1;
				if (d1 <= 0)
				{
					x++;
					d = d + 2 * x + 1;
				}
				else
				{
					x++;
					y--;
					d = d + 2 * (x - y + 1);
				}
			}
			else if (d > 0)
			{
				d2 = 2 * (d - x) - 1;
				if (d2 <= 0)
				{
					x++;
					y--;
					d = d + 2 * (x - y + 1);
				}
				else
				{
					y--;
					d = d - 2 * y + 1;
				}
			}
			else
			{
				y--;
				d = d - 2 * y + 1;
			}
		}
	}
	//
	// 基于 Bresenham 算法画填充圆
	void FillCircle_Bresenham(int x, int y, int r)
	{
		int tx = 0, ty = r, d = 3 - 2 * r, i;

		while (tx < ty)
		{
			// 画水平两点连线(<45度)
			for (i = x - ty; i <= x + ty; i++)
			{
				SetPixel(i, y - tx);
				if (tx != 0) // 防止水平线重复绘制
					SetPixel(i, y + tx);
			}

			if (d < 0) // 取上面的点
				d += 4 * tx + 6;
			else
			{ // 取下面的点
				// 画水平两点连线(>45度)
				for (i = x - tx; i <= x + tx; i++)
				{
					SetPixel(i, y - ty);
					SetPixel(i, y + ty);
				}
				d += 4 * (tx - ty) + 10, ty--;
			}

			tx++;
		}

		if (tx == ty) // 画水平两点连线(=45度)
			for (i = x - ty; i <= x + ty; i++)
			{
				SetPixel(i, y - tx);
				SetPixel(i, y + tx);
			}
		//Sleep(10);
	}
	//线框三角
	void Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		BresenhamLine(x1, y1, x2, y2);
		BresenhamLine(x2, y2, x3, y3);
		BresenhamLine(x3, y3, x1, y1);
	}

	/*填充三角形*/
	//绘制填充平顶三角形
	void TopTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
	{
		//先判断下输入的三角形
		if (y0 == y1)
		{
		}
		else if (y0 == y2)
		{
			swap(x2, x1), swap(y2, y1);
		}
		else if (y1 == y2)
		{
			swap(x0, x2), swap(y0, y2);
		}
		else
		{
			return; //error \brief 不是平顶三角形
		}

		if (x1 < x0)
		{
			swap(x1, x0), swap(y1, y0);
		}
		else if (x1 == x0)
		{
			return; // error \brief不是三角形
		}
		//计算左右误差
		float dxy_left = (x2 - x0) * 1.0 / (y2 - y0);
		float dxy_right = (x1 - x2) * 1.0 / (y1 - y2);
		//开始进行填充
		float xs = x0, xe = x1;
		for (int y = y0; y <= y2; y++)
		{
			BresenhamLine(xs, y, xe, y);
			xs += dxy_left;
			xe += dxy_right;
		}
	} //
	  //绘制平底三角形
	void BottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
	{
		//先判断下输入的三角形
		if (y2 == y1)
		{
		}
		else if (y2 == y0)
		{
			swap(x0, x1), swap(y0, y1);
		}
		else if (y0 == y1)
		{
			swap(x0, x2), swap(y0, y2);
		}
		else
		{
			return; //error \brief 不是平顶三角形
		}
		if (x1 < x2)
		{
			swap(x1, x2);
		}
		else if (x1 == x2)
		{
			return; // error \brief不是三角形
		}
		//计算左右误差
		float dxy_left = (x2 - x0) * 1.0 / (y2 - y0);
		float dxy_right = (x1 - x0) * 1.0 / (y1 - y0);
		//开始进行填充
		float xs = x0, xe = x0;
		for (int y = y0; y <= y2; y++)
		{
			BresenhamLine(xs, y, xe, y);
			xs += dxy_left;
			xe += dxy_right;
		}
	}
	//绘制任意三角形
	int FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
	{
		if ((x0 == x1 && x1 == x2) || (y0 == y1 && y1 == y2))
		{
			return 1; //error \brief传进来的点无法构成三角形
		}
		//将三个顶点按照从上到下排序
		if (y0 > y1)
			swap(x0, x1), swap(y0, y1);
		if (y0 > y2)
			swap(x0, x2), swap(y0, y2);
		if (y1 > y2)
			swap(y1, y2), swap(x1, x2);
		//进行绘制
		if (y0 == y1)
		{ //平顶三角形
			TopTriangle(x0, y0, x1, y1, x2, y2);
		}
		else if (y1 == y2)
		{
			BottomTriangle(x0, y0, x1, y1, x2, y2);
		}
		else
		{
			float k = 1.0 * (x2 - x0) / (y2 - y0);
			int new_x = x0 + k * (y1 - y0);
			BottomTriangle(x0, y0, new_x, y1, x1, y1);
			TopTriangle(new_x, y1, x1, y1, x2, y2);
		}
		return 0;
	}
	//线框矩形
	void Rect(int x1, int y1, int x2, int y2)
	{
		BresenhamLine(x1, y1, x2, y1);
		BresenhamLine(x2, y1, x2, y2);
		BresenhamLine(x2, y2, x1, y2);
		BresenhamLine(x1, y2, x1, y1);
	}
	//填充矩形
	void FillRect(int x1, int y1, int x2, int y2)
	{
		if (y1 > y2)
			swap(y1, y2);
		for (int y = y1; y < y2; y++)
		{
			BresenhamLine(x1, y, x2, y);
		}
	}
	//多边形线[折线]
	void PolyLine(int *x, int *y, int n)
	{
		for (int i = 0; i < n - 1; i++)
		{
			BresenhamLine(x[i], y[i], x[i + 1], y[i + 1]);
		}
	}
	//封闭多边形
	void Polygon(int *x, int *y, int n)
	{
		for (int i = 0; i < n - 1; i++)
		{
			BresenhamLine(x[i], y[i], x[i + 1], y[i + 1]);
		}
		BresenhamLine(x[n - 1], y[n - 1], x[0], y[0]);
	}
	//填充多边形[未考虑凹凸性]
	void FillPoly(int *x, int *y, int n)
	{
		if (n < 3)
			return;
		for (int i = 0; i < n - 2; i++)
		{
			FillTriangle(x[i], y[i], x[i + 1], y[i + 1], x[i + 2], y[i + 2]);
		}
		if (n > 3)
			FillTriangle(x[n - 1], y[n - 1], x[0], y[0], x[1], y[1]);
	}
	//四分点
	void CirclePlot(int xc, int yc, int x, int y)
	{
		SetPixel(xc + x, yc + y);
		SetPixel(xc + x, yc - y);
		SetPixel(xc - x, yc + y);
		SetPixel(xc - x, yc - y);
	}
	//四分填充线
	void FillPlot(int xc, int yc, int x, int y)
	{
		BresenhamLine(xc + x, yc + y, xc + x, yc - y);
		BresenhamLine(xc - x, yc + y, xc - x, yc - y);
	}
	//中点法画椭圆
	void MidEllipse(int xc, int yc, int a, int b)
	{
		float sqa = a * a;
		float sqb = b * b;
		float d = sqb + sqa * (-b + 0.25);
		int x = 0;
		int y = b;
		CirclePlot(xc, yc, x, y);
		while (sqb * (x + 1) < sqa * (y - 0.5))
		{
			if (d < 0)
			{
				d += sqb * (2 * x + 3);
			}
			else
			{
				d += (sqb * (2 * x + 3) + sqa * (-2 * y + 2));
				y--;
			}
			x++;
			CirclePlot(xc, yc, x, y);
		}
		d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
		while (y > 0)
		{
			if (d < 0)
			{
				d += sqb * (2 * x + 2) + sqa * (-2 * y + 3);
				x++;
			}
			else
			{
				d += sqa * (-2 * y + 3);
			}
			y--;
			CirclePlot(xc, yc, x, y);
		}
	}
	//填充椭圆[中点法]
	void FillEllipse(int xc, int yc, int a, int b)
	{
		float sqa = a * a;
		float sqb = b * b;
		float d = sqb + sqa * (-b + 0.25);
		int x = 0;
		int y = b;
		FillPlot(xc, yc, x, y);
		while (sqb * (x + 1) < sqa * (y - 0.5))
		{
			if (d < 0)
			{
				d += sqb * (2 * x + 3);
			}
			else
			{
				d += (sqb * (2 * x + 3) + sqa * (-2 * y + 2));
				y--;
			}
			x++;
			FillPlot(xc, yc, x, y);
		}
		d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
		while (y > 0)
		{
			if (d < 0)
			{
				d += sqb * (2 * x + 2) + sqa * (-2 * y + 3);
				x++;
			}
			else
			{
				d += sqa * (-2 * y + 3);
			}
			y--;
			FillPlot(xc, yc, x, y);
		}
	}
	//Bresenham画椭圆
	void BresenhamEllipse(int xc, int yc, int a, int b)
	{
		int sqa = a * a;
		int sqb = b * b;
		int x = 0;
		int y = b;
		int d = 2 * sqb - 2 * b * sqa + sqa;
		CirclePlot(xc, yc, x, y);
		int P_x = int((float)sqa / sqrt((float)(sqa + sqb)) + 0.5);
		while (x <= P_x)
		{
			if (d < 0)
			{
				d += 2 * sqb * (2 * x + 3);
			}
			else
			{
				d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
				y--;
			}
			x++;
			CirclePlot(xc, yc, x, y);
		}
		d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
		while (y >= 0)
		{
			CirclePlot(xc, yc, x, y);
			y--;
			if (d < 0)
			{
				x++;
				d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
			}
			else
			{
				d = d - 2 * sqa * y - sqa;
			}
		}
	}
	//画椭圆弧
	inline void Arc(int xc, int yc, int a, int b, float theta1, float theta2)
	{
		int n = sqrt(float(a * a + b * b)) * PI * abs(theta2 - theta1) / 90 * 2; //2倍余量
		int x, y;																 //printf("%lf\n", sqrt(float(a*a + b*b)));
		for (int i = 0; i < n; i++)
		{
			x = xc + a * cos(2 * PI / 360 * (theta1 + (theta2 - theta1) * i / n));
			y = yc + b * sin(2 * PI / 360 * (theta1 + (theta2 - theta1) * i / n));
			SetPixel(x, y);
		}
		//printf("%d\n", n);
	}
	//画椭圆弧[填充，效率不高]
	void FillArc(int xc, int yc, int a, int b, float theta1, float theta2)
	{
		int r = sqrt(float(a * a + b * b));
		for (int i = 0; i < r; i++)
		{
			Arc(xc, yc, i * a / r, i * b / r, theta1, theta2);
		}
		//printf("%d\n", n);
	}
	/*三维部分：主要是旋转[暂时只考虑平行投影]*/

	//绘制三维点在二维xOy平面的封闭多边形
	void DrawArray(PointArray r)
	{
		for (int i = 0; i < r.length - 1; i++)
		{
			BresenhamLine(r.x[i], r.y[i], r.x[i + 1], r.y[i + 1]);
		}
		BresenhamLine(r.x[r.length - 1], r.y[r.length - 1], r.x[0], r.y[0]);
	}
	//绘制两组三维点对应连线在二维xOy平面的投影
	void Line3d(PointArray a, PointArray b)
	{
		int n = a.length;
		for (int i = 0; i < n; i++)
		{
			BresenhamLine(a.x[i], a.y[i], b.x[i], b.y[i]);
		}
	}
	//
	void FillTriangle3d(PointArray a)
	{
		FillTriangle(a.x[0], a.y[0], a.x[1], a.y[1], a.x[2], a.y[2]);
	}
	//
	void Triangle3d(PointArray a)
	{
		Triangle(a.x[0], a.y[0], a.x[1], a.y[1], a.x[2], a.y[2]);
	}
	//
	void FillRect3d(PointArray a)
	{
		FillTriangle(a.x[0], a.y[0], a.x[1], a.y[1], a.x[2], a.y[2]);
		FillTriangle(a.x[0], a.y[0], a.x[3], a.y[3], a.x[2], a.y[2]);
	}
	//
	//封闭多边形
	void Rect3d(PointArray a)
	{
		for (int i = 0; i < 3; i++)
		{
			BresenhamLine(a.x[i], a.y[i], a.x[i + 1], a.y[i + 1]);
		}
		BresenhamLine(a.x[3], a.y[3], a.x[0], a.y[0]);
	}
	//
	void initgraph()
	{
		iWidth = this->Width;
		iHeight = this->Height;
		int size = iWidth * iHeight * 3;
		PImage = new BYTE[size];
		this->Data = PImage;
		//
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = iWidth;
		bmi.bmiHeader.biHeight = iHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		//
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ImageShow, (void *)1, 0, 0);
	}
};

//
//三维点初始化
PointArray Array3d(int n)
{
	PointArray r;
	r.length = n;
	r.x = new float[n];
	r.y = new float[n];
	r.z = new float[n];
	for (int i = 0; i < n; i++)
	{
		r.x[i] = r.y[i] = r.z[i] = 0.0;
	}
	return r;
}
//三维点通过数组赋值
PointArray eval(float *a, int n)
{
	PointArray r;
	r.length = n;
	r.x = new float[n];
	r.y = new float[n];
	r.z = new float[n];
	for (int i = 0; i < n; i++)
	{
		r.x[i] = a[3 * i];
		r.y[i] = a[3 * i + 1];
		r.z[i] = a[3 * i + 2];
	}
	return r;
}
//输出三维点数组的数据
void print(PointArray r)
{
	for (int i = 0; i < r.length; i++)
	{
		printf("%f %f %f\n", r.x[i], r.y[i], r.z[i]);
	}
}
//对三维点进行旋转
PointArray Rotate(PointArray pa, vector3 vec, float t)
{
	PointArray r = Array3d(pa.length);
	float x, y, z, a, b, c;
	float base = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	a = vec[0] / base, b = vec[1] / base, c = vec[2] / base;
	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		//
		r.x[i] = (cos(t) + (1 - cos(t)) * a * a) * x +
				 ((1 - cos(t)) * a * b - sin(t) * c) * y +
				 ((1 - cos(t)) * a * c + sin(t) * b) * z;
		//
		r.y[i] = ((1 - cos(t)) * b * a + sin(t) * c) * x +
				 (cos(t) + (1 - cos(t)) * b * b) * y +
				 ((1 - cos(t)) * b * c - sin(t) * a) * z;
		//
		r.z[i] = ((1 - cos(t)) * c * a - sin(t) * b) * x +
				 ((1 - cos(t)) * c * b + sin(t) * a) * y +
				 (cos(t) + (1 - cos(t)) * c * c) * z;
		//
	}
	return r;
}
//
PointArray RotateX(PointArray pa, float t)
{
	PointArray r = Array3d(pa.length);
	float x, y, z;

	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		//
		r.x[i] = x;
		//
		r.y[i] = y * cos(t) - z * sin(t);
		//
		r.z[i] = y * sin(t) + z * cos(t);
		//
	}
	return r;
}
//
//
PointArray RotateY(PointArray pa, float t)
{
	PointArray r = Array3d(pa.length);
	float x, y, z;

	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		//
		r.x[i] = z * sin(t) + x * cos(t);
		//
		r.y[i] = y;
		//
		r.z[i] = z * cos(t) - x * sin(t);
		//
	}
	return r;
}
//
PointArray RotateZ(PointArray pa, float t)
{
	PointArray r = Array3d(pa.length);
	float x, y, z;

	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		//
		r.x[i] = x * cos(t) - y * sin(t);
		//
		r.y[i] = x * sin(t) + y * cos(t);
		//
		r.z[i] = z;
		//
	}
	return r;
}
//透视投影
PointArray Perspective(PointArray pa, float ez, float n, float f)
{
	PointArray rr = Array3d(pa.length);
	float x, y, z;
	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		rr.x[i] = (ez - z) / (n - f) * x;
		rr.y[i] = (ez - z) / (n - f) * y;
		rr.z[i] = z;
	}
	return rr;
}

//
Image ReadBMP(const char *filename)
{
	FILE *fpBmp;
	BITMAPFILEHEADER bmf;
	BITMAPINFO bmi;
	fpBmp = fopen(filename, "rb");
	fread(&bmf, 14, 1, fpBmp);
	fread(&bmi.bmiHeader, 40, 1, fpBmp);
	Image img = Image(bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight);
	//img.Data = new byte[img.Width*img.Height * 3];
	fread(img.Data, 1, bmf.bfSize, fpBmp);
	fclose(fpBmp);
	return img;
}

void WriteBMP(Image img, const char *filename)
{
	FILE *fpBmp;
	int line = (img.Width * 3 % 4 == 0) ? (img.Width * 3) : (img.Width * 3 / 4 + 1) * 4;
	printf("%d\n", line);
	BITMAPFILEHEADER bmf = {
		0x4d42, img.Height * line + 54, 0, 0, 54};
	BITMAPINFO bmi = {
		40, img.Width, img.Height, 1, 3 * 8, 0, img.Width * line, 0, 0, 100, 0};
	fpBmp = fopen(filename, "wb");
	fwrite(&bmf, 14, 1, fpBmp);
	fwrite(&bmi.bmiHeader, 40, 1, fpBmp);
	fwrite(img.Data, 1, bmf.bfSize, fpBmp);
	fclose(fpBmp);
}
