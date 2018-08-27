#include "include/parser.h"

/*测试命令
line,-200,-200,200,-200
color,255,255,0
filltriangle,-100,-86,100,-86,0,86
color,255,0,255
fillcircle,150,150,50
color,0,255,255
fillrect,-100,100,-200,200
cls
*/

int main(void)
{
	initbmp(w, h);
	SetOrigin(250, 250);
	write_bmp_file();
	system("test.bmp");
	while (1)
	{
		printf(">>");
		SplitedStrings drawds = split();
		if (drawds.s[0][0] == 'e')
			break;
		drawbmp(drawds);
		write_bmp_file();
	}
	return 0;
}
