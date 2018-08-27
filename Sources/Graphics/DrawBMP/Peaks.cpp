#include "drawbmp.hpp"
//
static float yrot = 0;
//
inline float fun(float x, float y)
{
	//Matlab Peaks Function
	float z = 3 * (1 - x) * (1 - x) * exp(-x * x - (y + 1) * (y + 1)) - 10 * (x / 5 - x * x * x - y * y * y * y * y) * exp(-x * x - y * y) - 1.0 / 3 * exp(-(x + 1) * (x + 1) - y * y);
	return z * 10;
}
//
void display(Image img)
{
	float a[12];
	PointArray ptsa, ptsb;
	float d = 0.1, factor = 50;
	float x, y, z1, z2, z3, z4;
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
			ptsa = eval(a, 12);
			ptsb = RotateY(ptsa, yrot);
			ptsb = RotateX(ptsb, 15 * 2 * PI / 360);
			//ptsb=RotateZ(ptsb,6);
			img.Rect3d(ptsb);
		}
	}
	yrot += 0.1;
}
int main(int argc, char *argv[])
{
	Image img = Image(500, 500);
	img.SetOrigin(250, 250);
	img.SetColor(0, 255, 255);
	img.initgraph();
	//Mainloop
	char filename[64];
	//
	for (int i = 0; i < 36; i++)
	{
		display(img);
		sprintf(filename, "img-%03d.bmp", i);
		WriteBMP(img, filename);
		//Sleep(200);
		img.ClearGraph();
	}
	return 0;
}
