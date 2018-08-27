#include "drawbmp.hpp"
#include "cube3d.hpp"
int main(int argc, char *argv[])
{
	Image img = Image(500, 500);
	img.initgraph();
	img.SetOrigin(250, 250);
	img.SetColor(0, 255, 255);
	//
	vector3 v = {0, 1, 1};
	for (int i = 0; i < 3600; i++)
	{
		cube3d(img, v);
		//
		Sleep(100);
		img.ClearGraph();
	}
	getchar();
	return 0;
}
