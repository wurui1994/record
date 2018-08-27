#include <math.h>
#include <stdio.h>
void init(FILE* fp)
{
	int w=640,h=480;
	fputs("%!PS-Adobe-3.0 EPSF-3.0\n",fp);
	fprintf(fp,"%%%%BoundingBox: 0 0 %d %d\n",w,h);
	fputs("/rgb {setrgbcolor} def\n",fp);
	fputs("/np {newpath} def\n",fp);
	fputs("/cp {closepath} def\n",fp);
	fputs("/mt {moveto} def\n",fp);
	fputs("/ll {lineto} def\n",fp);
	fputs("/st {stroke} def\n",fp);
	fputs("/lw {setlinewidth} def\n",fp);
	fputs("/line {np mt ll st} def\n",fp);
}
void close(FILE* fp)
{
	fputs("showpage\n%%EOF",fp);
	fclose(fp);
}
void line(FILE* fp,float x[],float y[],int n)
{
	fprintf(fp,"0 0 1 rgb\nnp\n%.3f %.3f mt\n",x[0],y[0]);
	for(int i=1;i<n;i++){
		fprintf(fp,"%.3f %.3f ll\n",x[i],y[i]);
	}
	fprintf(fp,"st\n");
}
#define N 628
int main()
{

	FILE* fp=fopen("main.ps","wb");
	init(fp);
	//fputs("0 1 0 rgb\n0 0 640 480 line\n",fp);
	//
	float x[N],y[N],t;
	for(int i=0;i<N;i++){
		t=-3.14+i/100.0;
		x[i]=200*sin(3*t)*cos(t)+320;
		y[i]=200*sin(3*t)*sin(t)+240;
		//printf("%d ",y[i]);
	}
	line(fp,x,y,N);
	//
	close(fp);
	return 0;
}