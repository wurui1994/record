#include <stdio.h>
#include <stdlib.h>
//#pragma pack(4)
#define w 10
#define h 10
void WriteBMP(unsigned char*img,const char* filename)
{
	FILE *fpBmp;
	int line=(w*3+3)/4*4;
	//printf("%d\n",line);
	int bmf[]= {
		h*line+54,0,54
	};
	int bmi[]= {
		40,w,h,1|3*8<<16,0,h*line,0,0,100,0
	};
	fpBmp = fopen(filename,"wb");
	fprintf(fpBmp,"BM");
	fwrite(&bmf,12,1,fpBmp);
	fwrite(&bmi,40,1,fpBmp);
	fwrite(img,1,line*h,fpBmp);
	fclose(fpBmp);
	//printf("%d ",bmf.bfSize);
}

int main()
{
	unsigned char img[w*h*3];
	for(int i=0;i<w*h*3;i++)img[i]=rand()%256;
	WriteBMP(img,"test.bmp");
}

