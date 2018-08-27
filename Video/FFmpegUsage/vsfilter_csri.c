#include "csri.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib,"VSFilter")

typedef struct image_s {
	int width, height, stride;
	unsigned char *buffer;      // RGB24
} image_t;

static void flip(image_t * frame)
{

	//unsigned short bpp = Data->Info.bmiHeader.biBitCount;
	unsigned int width = abs(frame->width);
	unsigned int height = abs(frame->height);
	unsigned int stride = abs(frame->stride);

	unsigned char* buffer = (unsigned char*)malloc(stride);

	unsigned char *cur = frame->buffer;

	for (unsigned int i = 0; i <= height / 2; i++)
	{
		memcpy(buffer, cur + i * stride, stride);
		memcpy(cur + i * stride, cur + (height - 1 - i)*stride, stride);
		memcpy(cur + (height - 1 - i)*stride, buffer, stride);
	}
	free(buffer);
}

void WriteBMP(const char* filename, image_t *img)
{
	// flip(img);
	int w = img->width;
	int h = img->height;
	int l = (w * 3 + 3) / 4 * 4;
	int bmi[] = { l*h + 54,0,54,40,w,h,1 | 3 * 8 << 16,0,l*h,0,0,100,0 };
	FILE *fp = fopen(filename, "wb");
	fprintf(fp, "BM");
	fwrite(&bmi, 52, 1, fp);
	fwrite(img->buffer, 1, l*h, fp);
	fclose(fp);
}

int main()
{
	const char *filename = "test.ass";

	float fps = 1;
	int width = 1280;
	int height = 720;
	double start = 0;
	double end = 3;

	csri_inst * g_csri_inst_yyy = NULL;
	csri_rend * csri_rend_xxx = csri_renderer_default();

	g_csri_inst_yyy = csri_open_file(csri_rend_xxx, filename, NULL);

	struct csri_fmt fmt = { CSRI_F_BGR_, width, height };

	unsigned char* canvas = NULL;
	unsigned char* whiteboard = NULL;

	struct csri_frame this_frame;
	memset(&this_frame, 0, sizeof(this_frame));
	this_frame.pixfmt = CSRI_F_BGR_;

	int byte_size = width * height * 4;

	canvas = malloc(byte_size);
	whiteboard = malloc(byte_size);
	//
	memset(canvas, 0, byte_size);
	memset(whiteboard, 255, byte_size);

	this_frame.planes[0] = canvas + (height - 1) * width * 4;
	this_frame.strides[0] = -(signed)width * 4;

	int state = csri_request_fmt(g_csri_inst_yyy, &fmt);

	csri_render(g_csri_inst_yyy, &this_frame, 2);

	int px_count = byte_size;

	image_t *img = malloc(sizeof(image_t));
	img->width = width;
	img->height = height;
	img->stride = width * 3;
	img->buffer = (unsigned char *)calloc(1, height * width * 4);

	unsigned char opacity = 255;
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	for (int i = 0; i < px_count; i += 4)
	{
		unsigned k = ((unsigned)canvas[i / 4]) * opacity / 255;
		canvas[i] = (k * b + (255 - k) * canvas[i]) / 255;
		canvas[i + 1] = (k * g + (255 - k) * canvas[i + 1]) / 255;
		canvas[i + 2] = (k * r + (255 - k) *canvas[i + 2]) / 255;
	}

	for (int index = 0; index < height*width; ++index)
	{
		img->buffer[index * 3] = canvas[index * 4];
		img->buffer[index * 3 + 1] = canvas[index * 4 + 1];
		img->buffer[index * 3 + 2] = canvas[index * 4 + 2];
	}
	WriteBMP("test.bmp", img);
	system("test.bmp");

	csri_close(g_csri_inst_yyy);
	free(img->buffer);
}