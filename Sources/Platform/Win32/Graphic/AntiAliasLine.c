#include "drawbmp.hpp"
#define round(x) int(x+0.5)
#define blend(bg,fg,alpha) int(round(alpha * fg + (1-alpha) * bg))
inline float fpart(float x)
{
	return x-int(x);
}
inline float rfpart(float x)
{
	return 1-fpart(x);
}
void putpixel(Image img,int x,int y,RGB fg,float alpha=1)
{
	//printf("%f ",alpha);
	RGB bg,c;
	bg=img.GetPixel(x,y);
	c.r=blend(bg.r,fg.r,alpha);
	c.g=blend(bg.g,fg.g,alpha);
	c.b=blend(bg.b,fg.b,alpha);
	img.SetColor(c.r,c.g,c.b);
	img.SetPixel(x,y);
}
void drawline(Image img,int x1,int y1,int x2,int y2,RGB color= {255,255,255})
{
	int dx=x2-x1,dy=y2-y1;
	int flag=abs(dx)<abs(dy);
	if(flag)swap(x1,y1),swap(x2,y2),swap(dx,dy);
	if(x2<x1)swap(x1,x2),swap(y1,y2);
	float grad=1.0*dy/dx;
	float intery = y1 + rfpart(x1) * grad;
	//
	int xstart,xend,yend,xgap,px,py;
	//first
	xend = round(x1);
	yend = y1 + grad * (xend - x1);
	xgap = rfpart(x1 + 0.5);
	px= int(xend), py=int(yend);
	putpixel(img, px, py, color, rfpart(yend) * xgap);
	putpixel(img, px, py+1, color, fpart(yend) * xgap);
	xstart=px+1;
	//second
	xend = round(x2);
	yend = y2 + grad * (xend - x2);
	xgap = rfpart(x2 + 0.5);
	px= int(xend), py=int(yend);
	putpixel(img, px, py, color, rfpart(yend) * xgap);
	putpixel(img, px, py+1, color, fpart(yend) * xgap);
	xend=px;
	//
	int x,y;
	//
	//printf("(%d %d) ",xstart,xend);
	for(x=xstart; x<xend; x++) {
		y=int(intery);
		if(flag){
			px=y,py=x;
			putpixel(img, px, py, color, rfpart(intery));
			putpixel(img, px+1, py, color, fpart(intery));
		}
		else{
			px=x,py=y;
			putpixel(img, px, py, color, rfpart(intery));
			putpixel(img, px, py+1, color, fpart(intery));
		} 
		
		intery += grad;
	}
}
#define randi rand()%500
int main()
{
	Image img(500,500);
	RGB color;
	for(int i=0; i<100; i++){
		color.r=Random,color.g=Random,color.b=Random;
		drawline(img,randi,randi,randi,randi,color);
	}
	WriteBMP(img,"test.bmp");
}