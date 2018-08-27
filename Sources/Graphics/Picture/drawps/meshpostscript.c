#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define Random rand() % 255
#define Length(x) (sizeof(x) / sizeof(x[0]) / 3)
const float PI = 3.1415926536;
typedef float vector3[3];
//三维点数组结构
typedef struct
{
	int length;
	float *x, *y, *z;
} PointArray;
//
//三维点初始化
PointArray Array3d(int n)
{
	PointArray r;
	r.length = n;
	r.x = (float *)malloc(n * sizeof(float));
	r.y = (float *)malloc(n * sizeof(float));
	r.z = (float *)malloc(n * sizeof(float));
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
	r.x = (float *)malloc(n * sizeof(float));
	r.y = (float *)malloc(n * sizeof(float));
	r.z = (float *)malloc(n * sizeof(float));
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
//
void fileprint(FILE *fp, PointArray r)
{
	for (int i = 0; i < r.length; i++)
	{
		fprintf(fp, "%f %f ", r.x[i], r.y[i], r.z[i]);
	}
	fprintf(fp, " quad\n");
}
//
//对三维点进行旋转
void Rotate(PointArray pa, vector3 vec, float t)
{
	float x, y, z, a, b, c;
	float base = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	a = vec[0] / base, b = vec[1] / base, c = vec[2] / base;
	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		//
		pa.x[i] = (cos(t) + (1 - cos(t)) * a * a) * x +
				  ((1 - cos(t)) * a * b - sin(t) * c) * y +
				  ((1 - cos(t)) * a * c + sin(t) * b) * z;
		//
		pa.y[i] = ((1 - cos(t)) * b * a + sin(t) * c) * x +
				  (cos(t) + (1 - cos(t)) * b * b) * y +
				  ((1 - cos(t)) * b * c - sin(t) * a) * z;
		//
		pa.z[i] = ((1 - cos(t)) * c * a - sin(t) * b) * x +
				  ((1 - cos(t)) * c * b + sin(t) * a) * y +
				  (cos(t) + (1 - cos(t)) * c * c) * z;
	}
}
//
void RotateX(PointArray pa, float t)
{
	float x, y, z;

	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];

		pa.x[i] = x;
		//
		pa.y[i] = y * cos(t) - z * sin(t);
		//
		pa.z[i] = y * sin(t) + z * cos(t);
	}
}
//
void RotateY(PointArray pa, float t)
{
	float x, y, z;
	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		//
		pa.x[i] = z * sin(t) + x * cos(t);
		pa.y[i] = y;
		pa.z[i] = z * cos(t) - x * sin(t);
	}
}
//
void RotateZ(PointArray pa, float t)
{
	float x, y, z;
	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		pa.x[i] = x * cos(t) - y * sin(t);
		pa.y[i] = x * sin(t) + y * cos(t);
		pa.z[i] = z;
	}
}
//透视投影
void Perspective(PointArray pa, float ez, float n, float f)
{
	float x, y, z;
	for (int i = 0; i < pa.length; i++)
	{
		x = pa.x[i], y = pa.y[i], z = pa.z[i];
		pa.x[i] = (ez - z) / (n - f) * x;
		pa.y[i] = (ez - z) / (n - f) * y;
		pa.z[i] = z;
	}
}
//
static float yrot = 45;
//
inline float fun(float x, float y)
{
	//Matlab Peaks Function
	float z = 3 * (1 - x) * (1 - x) * exp(-x * x - (y + 1) * (y + 1)) - 10 * (x / 5 - x * x * x - y * y * y * y * y) * exp(-x * x - y * y) - 1.0 / 3 * exp(-(x + 1) * (x + 1) - y * y);
	return z * 10;
}
//
void display()
{
	float a[12];
	PointArray ptsa, ptsb;
	float d = 0.1, factor = 50;
	float x, y, z1, z2, z3, z4;
	FILE *fp = fopen("main.ps", "wb");
	fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n%%%%BoundingBox: -250 -250 250 250\n/rgb {setrgbcolor} def\n/np {newpath} def\n/cp {closepath} def\n/mt {moveto} def\n/rmt {rmoveto} def\n/ll {lineto} def\n/rl {rlineto} def\n/st {stroke} def\n/lw {setlinewidth} def\n/line {np mt ll st} def\n/quad {np mt ll ll ll cp st} def\n0 0 1 rgb\n0.2 lw\n");
	for (x = -3; x < 3; x += d)
	{
		for (y = -3; y < 3; y += d)
		{
			z1 = fun(x, y);
			a[0] = x * factor, a[1] = z1, a[2] = y * factor;
			z2 = fun(x + d, y);
			a[3] = (x + d) * factor, a[4] = z2, a[5] = y * factor;
			z3 = fun(x + d, y + d);
			a[6] = (x + d) * factor, a[7] = z3, a[8] = (y + d) * factor;
			z4 = fun(x, y + d);
			a[9] = x * factor, a[10] = z4, a[11] = (y + d) * factor;
			//
			ptsa = eval(a, Length(a));
			RotateY(ptsa, yrot);
			RotateX(ptsa, 15 * 2 * PI / 360);
			//ptsb=RotateZ(ptsb,6);
			fileprint(fp, ptsa);
		}
	}
	fprintf(fp, "\nshowpage\n%%%%EOF\n");
	fclose(fp);
	yrot += 0.1;
}
int main()
{
	display();
}