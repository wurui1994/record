#include "drawbmp.hpp"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	//img.SetScale(100,100);
	double a[]= {
		//正面
		-100,-100,100,
		100,-100,100,
		100,100,100,
		-100,100,100,
		//后面
		-100,-100,-100,
		100,-100,-100,
		100,100,-100,
		-100,100,-100,
		//平行线
		-100,-100,100,
		-100,100,100,
		100,-100,100,
		100,100,100
	};
	double b[]= {
		//
		100,-100,100,
		100,100,100,
		-100,100,100,
		-100,-100,100,
		//
		100,-100,-100,
		100,100,-100,
		-100,100,-100,
		-100,-100,-100,
		//
		-100,-100,-100,
		-100,100,-100,
		100,-100,-100,
		100,100,-100
	};
	PointArray ptsa = eval(a, Length(a));
	PointArray ptsb = eval(b, Length(b));
	PointArray pta, ptb;
	//print(pts);
	Image img = Image(500, 500);
	img.initgraph();
	img.SetOrigin(250, 250);
	img.SetColor(0, 255, 255);
	vector3 vv = {1, 0, 0};
	ptsa = Rotate(ptsa, vv, 0.5);
	ptsb = Rotate(ptsb, vv, 0.5);
	//
	vector3 v = {0, 1, 0};
	for (int i = 0; i < 3600; i++)
	{
		ptsa = Rotate(ptsa, v, 0.1);
		ptsb = Rotate(ptsb, v, 0.1);
		img.DrawArray2(ptsa, ptsb);
		//getchar();

		Sleep(100);
		img.ClearGraph();
	}
	//getchar();
	return 0;
}
