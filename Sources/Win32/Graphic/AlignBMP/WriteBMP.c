#include <stdio.h>
#include <stdlib.h>
#define w 200
#define h 200
void WriteBMP(char*img,const char* filename)
{
	int l=(w*3+3)/4*4;
	int bmi[]= {l*h+54,0,54,40,w,h,1|3*8<<16,0,l*h,0,0,100,0};
	FILE *fp = fopen(filename,"wb");
	fprintf(fp,"BM");
	fwrite(&bmi,52,1,fp);
	fwrite(img,1,l*h,fp);
	fclose(fp);
}
int main()
{
	char img[w*h*3];
	for(int i=0; i<w*h*3; i++)img[i]=rand()%256;
	WriteBMP(img,"test.bmp");
	system("test.bmp");
	return 0;
}

