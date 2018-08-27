#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	float r, g, b;
} RGB;

void init(FILE *fp, int w, int h)
{

	fputs("%!PS-Adobe-3.0 EPSF-3.0\n", fp);
	fprintf(fp, "%%%%BoundingBox: 0 0 %d %d\n", w, h);
	fputs("/rgb {setrgbcolor} def\n", fp);
	fputs("/np {newpath} def\n", fp);
	fputs("/cp {closepath} def\n", fp);
	fputs("/mt {moveto} def\n", fp);
	fputs("/rmt {rmoveto} def\n", fp);
	fputs("/ll {lineto} def\n", fp);
	fputs("/rl {rlineto} def\n", fp);
	fputs("/st {stroke} def\n", fp);
	fputs("/lw {setlinewidth} def\n", fp);
	fputs("/line {np mt ll st} def\n", fp);
}

void close(FILE *fp)
{
	fputs("showpage\n%%EOF", fp);
	fclose(fp);
}

void line(FILE *fp, float x[], float y[], int n)
{
	fprintf(fp, "0 0 1 rgb\nnp\n%.3f %.3f mt\n", x[0], y[0]);
	for (int i = 1; i < n; i++)
	{
		fprintf(fp, "%.3f %.3f ll\n", x[i], y[i]);
	}
	fprintf(fp, "st\n");
}

void fillcircle(FILE *fp, float x, float y, RGB rgb)
{
	fprintf(fp, "%.2f %.2f %.2f rgb\n", rgb.r, rgb.g, rgb.b);
	// fprintf(fp,"np\n%.3f %.3f mt\n",x,y);
	// float xx,yy,t;
	// for(int i=0;i<62;i++){
	// t=i/10.0;
	// xx=sin(t);
	// yy=cos(t);
	// fprintf(fp,"%.3f %.3f rl\n",xx,yy);
	// }
	// fprintf(fp,"cp fill\n");
	fprintf(fp, "%.3f %.3f fc\n", x, y);
}

void randimage(FILE *fp, int w, int h)
{
	fprintf(fp, "%d %d 8 [1 0 0 -1 0 %d]", w, h, h);
	fprintf(fp, "{<\n");
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			fprintf(fp, "%02X%02X%02X", rand() % 256, rand() % 256, rand() % 256);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, ">}\nfalse 3 colorimage\n");
}

#define N 628
#define randi (rand() / (RAND_MAX + 1.0))

int main()
{

	FILE *fp = fopen("main.ps", "wb");
	int w = 10, h = 10;
	init(fp, w, h);
	//fputs("0 1 0 rgb\n0 0 640 480 line\n",fp);
	//
	randimage(fp, w, h);
	//
	close(fp);
	return 0;
}