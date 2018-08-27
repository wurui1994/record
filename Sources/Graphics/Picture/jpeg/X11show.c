#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <jpeglib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
typedef unsigned char byte;
typedef struct
{
	int Width, Height;
	byte *Data;
} Image;
Image img;
int num = 0;
typedef struct
{
	int length;
	char **strs;
} vecstr;
vecstr vs;
void initiate()
{
	char filename[FILENAME_MAX] = "test.txt";
	vs.length = 0;
	vs.strs = NULL;
	FILE *fp = fopen(filename, "rt");
	while (!feof(fp))
	{
		char *line = (char *)malloc(BUFSIZ);
		memset(line, 0, BUFSIZ);
		fgets(line, BUFSIZ, fp);
		line[strlen(line) - 1] = '\0'; //去除\n
		//puts(line);
		vs.strs = (char **)realloc(vs.strs, ++(vs.length) * sizeof(char *));
		vs.strs[vs.length - 1] = line;
	}
	fclose(fp);
	//printf("%d\n",vs.length);
}
void swap(byte *a, byte *b)
{
	byte tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void readjpeg(const char filename[], Image *img)
{
	//Read the file
	FILE *fp = fopen(filename, "rb");
	if (!fp)
		return;
	//
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPARRAY buffer;
	//unsigned char *src_buff;
	unsigned char *point;

	cinfo.err = jpeg_std_error(&jerr); //一下为libjpeg函数，具体参看相关文档
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	unsigned long width = cinfo.output_width;
	unsigned long height = cinfo.output_height;
	unsigned short depth = cinfo.output_components;

	img->Data = (byte *)malloc(width * height * depth);
	img->Width = width, img->Height = height;
	byte *src_buff = img->Data;
	//src_buff=new unsigned char[width*height*depth];
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);

	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width * depth, 1);

	point = src_buff;
	while (cinfo.output_scanline < height)
	{
		jpeg_read_scanlines(&cinfo, buffer, 1); //读取一行jpg图像数据到buffer
		memcpy(point, *buffer, width * depth);  //将buffer中的数据逐行给src_buff
		point += width * depth;					//一次改变一行
	}
	//write_bmp_header(&cinfo);            //写bmp文件头
	//write_bmp_data(&cinfo,src_buff);    //写bmp像素数据
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	//delete[] src_buff;
	//
	//fread(pimg, w*h* 3, 1, fp);
	fclose(fp);
	//
	///Two Steps,From ppm-order to bmp-order.
	//RGB2BGR,swap B and R.
	byte *pimg = img->Data;
	int base;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			base = width * i * 3 + j * 3;
			swap(pimg + base + 0, pimg + base + 2);
		}
	}
	//Flip,swap Top and Bottom.
	//int size=width*3;
	//byte* line=(byte*)malloc(size);
	//for(int k=0; k<height/2; k++) {
	//	memcpy(line,pimg+size*k,size);
	//	memcpy(pimg+size*k,pimg+size*(height-1-k),size);
	//	memcpy(pimg+size*(height-1-k),line,size);
	//}
}
void draw(char *rgb_out, int w, int h)
{
	int i = 0;

	for (i = 0; i < w * h * 3; i += 3)
	{
		rgb_out[i + 0] = rand() % 256;
		rgb_out[i + 1] = rand() % 256;
		rgb_out[i + 2] = rand() % 256;
	}

	return;
}
char *addalpha(char *data, int w, int h)
{
	char *buffer = (char *)malloc(w * h * 4 * sizeof(char));
	int i = 0;

	for (i = 0; i < w * h; i++)
	{
		buffer[4 * i + 0] = data[3 * i + 0];
		buffer[4 * i + 1] = data[3 * i + 1];
		buffer[4 * i + 2] = data[3 * i + 2];
		//buffer[4*i+3]=rand()%256;
	}
	//data=(char*)realloc(data,w*h*4*sizeof(char));
	//memcpy(data,buffer,w*h*4);
	free(data);
	return buffer;
}

XImage *create_ximage(Display *display, Visual *visual, int width, int height)
{
	char *image32 = (char *)malloc(width * height * 3);
	draw(image32, width, height);
	image32 = addalpha(image32, width, height);
	return XCreateImage(display, visual, 24,
						ZPixmap, 0, image32,
						width, height, 32, 0);
}

int main(int argc, char **argv)
{
	int win_b_color;
	int win_w_color;
	XEvent xev;
	Window window;
	GC gc;
	Display *display = XOpenDisplay(NULL);
	Visual *visual;
	XImage *ximage;

	win_b_color = BlackPixel(display, DefaultScreen(display));
	win_w_color = BlackPixel(display, DefaultScreen(display));
	window = XCreateSimpleWindow(display,
								 DefaultRootWindow(display),
								 0, 0, 640, 480, 0,
								 win_b_color, win_w_color);

	visual = DefaultVisual(display, 0);

	XSelectInput(display, window, ExposureMask | KeyPressMask);

	XMapWindow(display, window);
	XFlush(display);
	gc = XCreateGC(display, window, 0, NULL);

	XEvent event;
	bool flag = false;
	initiate();
	while (1)
	{
		int r;

		//XNextEvent(display, &event);

		//if (event.type == Expose)
		//{
		if (num == vs.length - 1)
			exit(0);
		readjpeg(vs.strs[num++], &img);
		//ximage = create_ximage(display, visual, img.Width, img.Height);
		//char *image32 = (char *)malloc(width * height * 3);
		char *image32 = (char *)img.Data;
		int width = img.Width;
		int height = img.Height;
		//draw(image32, width, height);
		image32 = addalpha(image32, width, height);
		ximage = XCreateImage(display, visual, 24,
							  ZPixmap, 0, image32,
							  width, height, 32, 0);
		r = XPutImage(display, window,
					  gc, ximage, 0, 0, 0, 0,
					  640, 480);
		free(image32);
		//printf("RES: %i\n", r);
		//}
		//else if (event.type == KeyPress)
		//  flag= true;
	}

	return 0;
}