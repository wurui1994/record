#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef unsigned char byte;
struct Image
{
	int Width, Height;
	byte *Data;
};
void WriteBMP(Image img, const char *filename)
{
	FILE *fpBmp;
	int line = (img.Width * 3 % 4 == 0) ? (img.Width * 3) : (img.Width * 3 / 4 + 1) * 4;
	printf("%d\n", line);
	BITMAPFILEHEADER bmf = {
		0x4d42, img.Height * line + 54, 0, 0, 54};
	BITMAPINFO bmi = {40, img.Width, img.Height, 1, 3 * 8, 0,
					  img.Height * line, 0, 0, 100, 0};
	fpBmp = fopen(filename, "wb");
	fwrite(&bmf, 14, 1, fpBmp);
	fwrite(&bmi.bmiHeader, 40, 1, fpBmp);
	fwrite(img.Data, 1, bmf.bfSize, fpBmp);
	fclose(fpBmp);
}
int main()
{
	FILE *fp;
	long lSize, cur;
	unsigned char *buffer;
	size_t result;
	int w, h, c;
	/* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
	fp = fopen("image.ppm", "rb");

	fscanf(fp, "P6\n%d %d\n%d\n", &w, &h, &c);
	printf("%d %d\n", w, h);
	/* 获取文件大小 */
	fpos_t filepos;
	fgetpos(fp, &filepos);
	cur = ftell(fp);
	fseek(fp, 0, SEEK_END);
	lSize = ftell(fp) - cur;
	printf("%d \n", lSize);
	fsetpos(fp, &filepos);
	/* 分配内存存储整个文件 */
	buffer = (unsigned char *)malloc(sizeof(unsigned char) * lSize);
	/* 将文件拷贝到buffer中 */
	result = fread(buffer, 1, lSize, fp);
	/* 结束演示，关闭文件并释放内存 */
	fclose(fp);
	free(buffer);
	//for(int i=0;i<w*h*3;i++){
	//printf("%d ",buffer[i]);
	//}
	Image img;
	img.Width = w;
	img.Height = h;
	img.Data = buffer;
	WriteBMP(img, "image.bmp");
	return 0;
}
