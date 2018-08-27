#ifndef DRAWBMP_H
#define DRAWBMP_H
/*
Title:DrawBMP
Author:wurui
Date:2015-4-28-20:53
Version:0.0.5
Email:1341531859@qq.com
Address:whut-yu-H6-611
*/

//头文件
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// #include <Windows.h>
// #include <gl/glut.h>
//定义常量
#define PI 3.1415926536
const int w = 500, h = 500;
int ox = 0, oy = 0;
int red = 0, green = 255, blue = 0;
double xscale = 1.0, yscale = 1.0;
//定义位图bmp的头和信息，共54字节
struct bmpheader
{
	unsigned file_size;
	unsigned short creater1, creater2;
	unsigned offset;
} header;

struct bmpinfo
{
	unsigned header_size, width, height;
	unsigned short nplanes, bitspp;
	unsigned compress_type, image_size;
	unsigned hres, vres, ncolors, nimpcolors;
} info;

//定义位图bmp三维矩阵w*h*3
typedef struct matrix3
{
	int w, h;
	unsigned char *bitmap;
} mat3;

//为位图矩阵bitmap分配内存
unsigned char *bitmap;

//将位图数据bitmap写入位图test.bmp
void write_bmp_file()
{
	header.file_size = w * h * 3 + 54;
	header.creater1 = 0;
	header.creater2 = 0;
	header.offset = 54;
	//
	info.header_size = 40;
	info.width = w;
	info.height = h;
	info.nplanes = 1;
	info.bitspp = 3 * 8;
	info.compress_type = 0;
	info.image_size = w * h * 3;
	info.hres = 0;
	info.vres = 0;
	info.ncolors = 100;
	info.nimpcolors = 0;
	//
	FILE *fp = fopen("test.bmp", "wb");
	fwrite("BM", 2, 1, fp);
	fwrite(&header, 4, 3, fp);
	fwrite(&info, 4, 10, fp);
	//
	fwrite(bitmap, 1, info.image_size, fp);
	fclose(fp);
}
//初始化位图矩阵bitmap
void initbmp(int w, int h)
{
	bitmap = (unsigned char *)malloc(w * h * 3);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w * 3;)
		{
			bitmap[i * w * 3 + j++] = 0;
			bitmap[i * w * 3 + j++] = 0;
			bitmap[i * w * 3 + j++] = 0;
		}
	}
}
//设置背景色
void SetBgColor(int r, int g, int b)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w * 3;)
		{
			bitmap[i * w * 3 + j++] = b;
			bitmap[i * w * 3 + j++] = g;
			bitmap[i * w * 3 + j++] = r;
		}
	}
}
//设置坐标原点
void SetOrigin(int x, int y)
{
	ox = x, oy = y;
}
//设置缩放比例
void SetScale(double x, double y)
{
	xscale = x, yscale = y;
}
//设置像素点为指定的RGB值
void SetPixel(int x, int y)
{
	x = ox + x * xscale;
	y = oy + y * yscale;
	if ((x < 0 || x > w) || (y < 0 || y > h))
		return;
	bitmap[y * w * 3 + x * 3] = blue;
	bitmap[y * w * 3 + x * 3 + 1] = green;
	bitmap[y * w * 3 + x * 3 + 2] = red;
}
//设置将要使用的RGB颜色值
void SetColor(int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
}

/*二维绘图部分：主要是基本图元的算法*/
//基于直线斜率，自己写的
void Line(int xstart, int xend, int ystart, int yend)
{
	int x, y;
	int dx = xend - xstart, dy = yend - ystart;
	double k = 1.0 * dy / dx;
	int n = sqrt(dx * dx + dy * dy);
	//printf("%d\n", n);
	for (int i = 0; i < n; i++)
	{
		x = xstart + dx * i / n;
		y = (int)(ystart + k * dx * i / n);
		SetPixel(x, y);
	}
}
//数值微分DDA画线法
void DDALine(int x0, int y0, int xEnd, int yEnd)
{
	//if (x0 == xEnd || y0 == yEnd)return;//DDA无法画重合点，郁闷
	float x, y, dx, dy;
	int i, step;
	x = x0 + 0.5;
	y = y0 + 0.5; //保证计算精度
	step = abs(xEnd - x0) > abs(yEnd - y0) ? abs(xEnd - x0) : abs(yEnd - y0);
	dx = ((float)(xEnd - x0)) / step; //1
	dy = ((float)(yEnd - y0)) / step; //m
	for (i = 0; i <= step; i++)
	{
		x += dx;
		y += dy;
		SetPixel(x, y); //画坐标点
	}
}
//Bresenham line
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void BresenhamLine(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1, inc, pi;
	inc = ((dx * dy) >= 0) ? 1 : -1;
	if (abs(dx) > abs(dy))
	{
		if (dx < 0)
		{
			swap(&x1, &x2);
			swap(&y1, &y2);
			dx = -dx;
			dy = -dy;
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
			swap(&x1, &x2);
			swap(&y1, &y2);
			dx = -dx;
			dy = -dy;
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
void MidLine(int x1, int y1, int x2, int y2)
{
	//交换两点的坐标
	if ((x1 - x2) > 0 && (y1 - y2) > 0)
	{
		int c = x1;
		x1 = x2;
		x2 = c;
		c = y1;
		y1 = y2;
		y2 = c;
	}
	if ((x1 - x2) < 0 && (y1 - y2) > 0)
	{
		int c = x1;
		x1 = x2;
		x2 = c;
		c = y1;
		y1 = y2;
		y2 = c;
	}
	float a = y1 - y2, b = x2 - x1;
	float m = -(a / b); //斜率，用于判断直线不同的情况

	//当斜率大于0，小于1的情况
	if (0 <= m && m <= 1)
	{
		float d = 2 * a + b, deta1 = 2 * a, deta2 = 2 * (a + b), x = x1, y = y1;
		while (x < x2)
		{
			SetPixel(x, y); //画坐标点
			if (d < 0)
			{
				x++, y++, d += deta2;
			}
			else
			{
				x++, d += deta1;
			}
		}
	}
	//当斜率大于1的情况
	if (m > 1)
	{
		int d = a + 2 * b, deta1 = 2 * b, deta2 = 2 * (a + b), x = x1, y = y1;
		while (y < y2)
		{
			SetPixel(x, y); //画坐标点
			if (d > 0)
			{
				y++, x++, d += deta2;
			}
			else
			{
				y++, d += deta1;
			}
		}
	}
	//当斜率小于-1的情况
	if (m <= -1)
	{
		int d = -a + 2 * b, deta1 = 2 * b, deta2 = 2 * (b - a), x = x1, y = y1;
		while (y < y2)
		{
			SetPixel(x, y); //画坐标点
			if (d < 0)
			{
				x--, y++, d += deta2;
			}
			else
			{
				y++, d += deta1;
			}
		}
	}
	//当斜率小于0大于-1的情况
	if (m > -1 && m < 0)
	{
		int a = y1 - y2, b = x2 - x1;
		int d = -2 * a + b, deta1 = -2 * a, deta2 = 2 * (b - a), x = x1, y = y1;
		while (x > x2)
		{
			SetPixel(x, y); //画坐标点
			if (d > 0)
			{
				x--, y++, d += deta2;
			}
			else
			{
				x--, d += deta1;
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
		//SetPixel(x1 + x, y1 + y);
		//SetPixel(x1 + x, y1 - y);
		BresenhamLine(x1 + x, y1 + y, x1 + x, y1 - y);
		//SetPixel(x1 - x, y1 + y);
		//SetPixel(x1 - x, y1 - y);
		BresenhamLine(x1 - x, y1 + y, x1 - x, y1 - y);
		//SetPixel(x1 + y, y1 + x);
		//SetPixel(x1 + y, y1 - x);
		BresenhamLine(x1 + y, y1 + x, x1 + y, y1 - x);
		//SetPixel(x1 - y, y1 + x);
		//SetPixel(x1 - y, y1 - x);
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
//线框三角
void Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	MidLine(x1, y1, x2, y2);
	MidLine(x2, y2, x3, y3);
	MidLine(x3, y3, x1, y1);
}
/*填充三角形*/
//绘制填充平顶三角形
void Draw_Top_Triangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	//先判断下输入的三角形
	if (y0 == y1)
	{
	}
	else if (y0 == y2)
	{
		swap(&x2, &x1);
		swap(&y2, &y1);
	}
	else if (y1 == y2)
	{
		swap(&x0, &x2);
		swap(&y0, &y2);
	}
	else
	{
		return; //error \brief 不是平顶三角形
	}

	if (x1 < x0)
	{
		swap(&x1, &x0);
		swap(&y1, &y0);
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
		Line(xs + 0.5, xe + 0.5, y, y);
		xs += dxy_left;
		xe += dxy_right;
	}
} //
//绘制平底三角形
void Draw_Bottom_Triangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	//先判断下输入的三角形
	if (y2 == y1)
	{
	}
	else if (y2 == y0)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	else if (y0 == y1)
	{
		swap(&x0, &x2);
		swap(&y0, &y2);
	}
	else
	{
		return; //error \brief 不是平顶三角形
	}
	if (x1 < x2)
	{
		swap(&x1, &x2);
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
		Line(xs + 0.5, xe + 0.5, y, y);
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
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	if (y0 > y2)
	{
		swap(&x0, &x2);
		swap(&y0, &y2);
	}
	if (y1 > y2)
	{
		swap(&y1, &y2);
		swap(&x1, &x2);
	}
	//查找最大的x坐标，和最小的y坐标
	int min = (x0 < x1 ? x0 : x1);
	min = (min < x2 ? min : x2);
	int max = (x0 > x1 ? x0 : x1);
	max = (max > x2 ? max : x2);
	//进行绘制
	if (y0 == y1)
	{ //平顶三角形
		Draw_Top_Triangle(x0, y0, x1, y1, x2, y2);
	}
	else if (y1 == y2)
	{
		Draw_Bottom_Triangle(x0, y0, x1, y1, x2, y2);
	}
	else
	{
		int new_x = x0 + 0.5 + (float)1.0 * (y1 - y0) * (x2 - x0) / (y2 - y0);
		Draw_Bottom_Triangle(x0, y0, new_x, y1, x1, y1);
		Draw_Top_Triangle(new_x, y1, x1, y1, x2, y2);
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
	{
		int c;
		c = y1;
		y1 = y2;
		y2 = c;
	}
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
	//SetPixel(xc + x, yc + y);
	//SetPixel(xc + x, yc - y);
	BresenhamLine(xc + x, yc + y, xc + x, yc - y);
	//SetPixel(xc - x, yc + y);
	//SetPixel(xc - x, yc - y);
	BresenhamLine(xc - x, yc + y, xc - x, yc - y);
}
//中点法画椭圆
void MidEllipse(int xc, int yc, int a, int b)
{
	double sqa = a * a;
	double sqb = b * b;
	double d = sqb + sqa * (-b + 0.25);
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
	double sqa = a * a;
	double sqb = b * b;
	double d = sqb + sqa * (-b + 0.25);
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
	int P_x = sqa / sqrt((sqa + sqb)) + 0.5;
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
inline void Arc(int xc, int yc, int a, int b, double theta1, double theta2)
{
	int n = sqrt(a * a + b * b) * PI * abs(theta2 - theta1) / 90 * 2; //2倍余量
	int x, y;														  //printf("%lf\n", sqrt(double(a*a + b*b)));
	for (int i = 0; i < n; i++)
	{
		x = xc + a * cos(2 * PI / 360 * (theta1 + (theta2 - theta1) * i / n));
		y = yc + b * sin(2 * PI / 360 * (theta1 + (theta2 - theta1) * i / n));
		SetPixel(x, y);
	}
	//printf("%d\n", n);
}
//画椭圆弧[填充，效率不高]
void FillArc(int xc, int yc, int a, int b, double theta1, double theta2)
{
	int r = sqrt(a * a + b * b);
	for (int i = 0; i < r; i++)
	{
		Arc(xc, yc, i * a / r, i * b / r, theta1, theta2);
	}
	//printf("%d\n", n);
}
/*三维部分：主要是旋转[暂时只考虑平行投影]*/
//三维点数组结构
typedef struct tagPointArray
{
	int length;
	double *x, *y, *z;
} PointArray;
//三维点初始化
PointArray Array3d(int n)
{
	PointArray r;
	r.length = n;
	r.x = (double *)malloc(sizeof(double) * n);
	r.y = (double *)malloc(sizeof(double) * n);
	r.z = (double *)malloc(sizeof(double) * n);
	for (int i = 0; i < n; i++)
	{
		r.x[i] = r.y[i] = r.z[i] = 0.0;
	}
	return r;
}
//三维点通过数组赋值
PointArray eval(double *a, int n)
{
	PointArray r;
	r.length = n;
	r.x = (double *)malloc(sizeof(double) * n);
	r.y = (double *)malloc(sizeof(double) * n);
	r.z = (double *)malloc(sizeof(double) * n);
	for (int i = 0; i < n; i++)
	{
		r.x[i] = a[i];
		r.y[i] = a[i + n];
		r.z[i] = a[i + 2 * n];
	}
	return r;
}
//输出三维点数组的数据
void printPA(PointArray r)
{
	for (int i = 0; i < r.length; i++)
	{
		printf("%f %f %f\n", r.x[i], r.y[i], r.z[i]);
	}
}
//对三维点进行旋转
PointArray Rotate(PointArray pa, double x, double y, double z)
{
	PointArray r = Array3d(pa.length);
	for (int i = 0; i < pa.length; i++)
	{
		r.x[i] = pa.x[i] * cos(y) * cos(z) + pa.y[i] * sin(-z) + pa.z[i] * sin(-y);
		r.y[i] = pa.y[i] * cos(x) * cos(z) + pa.x[i] * sin(z) + pa.z[i] * sin(-x);
		r.z[i] = pa.z[i] * cos(x) * cos(y) + pa.x[i] * sin(y) + pa.y[i] * sin(x);
	}
	return r;
}
//绘制三维点在二维xOy平面的封闭多边形
void DrawArray(PointArray r)
{
	for (int i = 0; i < r.length - 1; i++)
	{
		DDALine(r.x[i], r.y[i], r.x[i + 1], r.y[i + 1]);
	}
	DDALine(r.x[r.length - 1], r.y[r.length - 1], r.x[0], r.y[0]);
}
//绘制两组三维点对应连线在二维xOy平面的投影
void DrawArray2(PointArray a, PointArray b)
{
	int n = a.length;
	for (int i = 0; i < n; i++)
	{
		DDALine(a.x[i], a.y[i], b.x[i], b.y[i]);
	}
}

/*字体部分*/
//小写字母
void littleletter(char x)
{
	if (x == 'a')
		MidCircle(0, 0, 100), Arc(200, 0, 100, 100, -120, -180);
	if (x == 'b')
		MidCircle(0, 0, 100), MidLine(-100, 0, -100, 200);
	if (x == 'c')
		Arc(0, 0, 100, 100, 45, 315);
	if (x == 'd')
		MidCircle(0, 0, 100), MidLine(100, 0, 100, 200), Arc(200, 0, 100, 100, -120, -180);
	if (x == 'e')
		MidLine(-100, 0, 100, 0), Arc(0, 0, 100, 100, 0, 315);
	if (x == 'f')
		MidLine(-50, 0, 50, 0), MidLine(0, -100, 0, 100),
			Arc(50, 100, 50, 50, 90, 180), Arc(-50, -100, 50, 50, 0, -90);
	if (x == 'g')
		MidCircle(0, 100, 100), Arc(0, -50, 100, 100, 0, -180), MidLine(100, -50, 100, 100);
	if (x == 'h')
		MidLine(-50, -100, -50, 100), Arc(0, 0, 50, 50, 0, 180), DDALine(50, 0, 50, -100);
	if (x == 'i')
		MidLine(10, -100, -10, 100), MidLine(-50, 80, -10, 100), MidLine(10, -100, 50, -80), FillCircle(-10, 150, 25);
	if (x == 'j')
		MidLine(50, -100, 50, 100), MidLine(0, 80, 50, 100), Arc(0, -100, 50, 50, 0, -180), FillCircle(35, 150, 25);
	if (x == 'k')
		MidLine(-50, -100, -50, 100), MidLine(-50, 0, 50, 50), MidLine(-50, 0, 50, -100);
	if (x == 'l')
		DDALine(0, 100, 0, -100), Arc(50, -100, 50, 50, -60, -180);
	if (x == 'm')
		MidLine(-100, -100, -100, 50), MidLine(0, -100, 0, 50), MidLine(100, -100, 100, 50),
			Arc(-50, 50, 50, 50, 0, 180), Arc(50, 50, 50, 50, 0, 180), Arc(-150, 50, 50, 50, 0, 80);
	if (x == 'n')
		MidLine(-100, -100, -100, 50), MidLine(100, -100, 100, 50),
			Arc(0, 50, 100, 100, 0, 180), Arc(-200, 50, 100, 100, 0, 60);
	if (x == 'o')
		MidCircle(0, 0, 100);
	if (x == 'p')
		MidCircle(0, 100, 100), DDALine(-100, 100, -100, -100), Arc(-150, 100, 50, 50, 0, 90);
	if (x == 'q')
		MidCircle(0, 100, 100), DDALine(100, 100, 100, -100), Arc(150, -100, 50, 50, -90, -180);
	if (x == 'r')
		DDALine(-50, 40, -50, -100), Arc(0, 0, 50, 50, 30, 180);
	if (x == 's')
		Arc(0, 50, 50, 50, 30, 270), Arc(0, -50, 50, 50, 210, 450);
	if (x == 't')
		MidLine(-70, 0, 80, 0), DDALine(0, 50, 0, -100), Arc(50, -100, 50, 50, -60, -180);
	if (x == 'u')
		DDALine(-50, 50, -50, -50), DDALine(50, 50, 50, -50),
			Arc(0, -50, 50, 50, 0, -180), Arc(100, -50, 50, 50, -120, -180);
	if (x == 'v')
		MidLine(-50, 50, 0, -100), MidLine(0, -100, 50, 50);
	if (x == 'w')
		MidLine(-100, 100, -50, -100), MidLine(-50, -100, 0, 50),
			MidLine(0, 50, 50, -100), MidLine(50, -100, 100, 100);
	if (x == 'x')
		MidLine(-50, 50, 50, -50), MidLine(-50, -50, 50, 50);
	if (x == 'y')
		MidLine(-30, 50, 0, 0), MidLine(-30, -50, 30, 50);
	if (x == 'z')
		MidLine(-50, 50, 50, 50), MidLine(50, 50, -50, -50), MidLine(-50, -50, 50, -50);
}

#endif //DRAWBMP_H