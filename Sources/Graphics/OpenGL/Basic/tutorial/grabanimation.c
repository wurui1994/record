#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define random (rand() / (RAND_MAX + 1.0))
static float xrot = 0.0;
static float yrot = 0.0;
static float zrot = 0.0;
const float d = 0.1;
float r, g, b;
int len;
float x, y;
#define range_max 3
#define range_min -3
GLfloat *data;
GLfloat *color;
int num = 0;
//
inline float fun(float x, float y)
{
	//Matlab Peaks Function
	float z = 3 * (1 - x) * (1 - x) * exp(-x * x - (y + 1) * (y + 1)) - 10 * (x / 5 - x * x * x - y * y * y * y * y) * exp(-x * x - y * y) - 1.0 / 3 * exp(-(x + 1) * (x + 1) - y * y);
	return z / 3.0;
}
void Initial()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE); // 开启剪裁
	glCullFace(GL_BACK);	// 裁掉背面
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	len = (range_max - range_min) / d;
	//printf("%d ", len);
	int index;
	data = malloc(sizeof(GLfloat) * len * len * 12);
	color = malloc(sizeof(GLfloat) * len * len * 12);
	for (int i = 0; i < len * len; i++)
	{
		r = random;
		g = random;
		b = random;
		for (int j = 0; j < 4; j++)
		{
			color[12 * i + 3 * j] = r;
			color[12 * i + 3 * j + 1] = g;
			color[12 * i + 3 * j + 2] = b;
		}
	}

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			x = range_min + 1.0 * i / len * (range_max - range_min);
			y = range_min + 1.0 * j / len * (range_max - range_min);
			index = i * len + j;
			data[12 * index] = x;
			data[12 * index + 1] = fun(x, y);
			data[12 * index + 2] = y;
			data[12 * index + 3] = x + d;
			data[12 * index + 4] = fun(x + d, y);
			data[12 * index + 5] = y;
			data[12 * index + 6] = x + d;
			data[12 * index + 7] = fun(x + d, y + d);
			data[12 * index + 8] = y + d;
			data[12 * index + 9] = x;
			data[12 * index + 10] = fun(x, y + d);
			data[12 * index + 11] = y + d;
		}
	}
}
GLubyte PixelData[500 * 500 * 3];
void WriteBMP(GLubyte *img, const char *filename, int w, int h)
{
	int l = (w * 3 + 3) / 4 * 4;
	int bmi[] = {l * h + 54, 0, 54, 40, w, h, 1 | 3 * 8 << 16, 0, l * h, 0, 0, 0, 0};
	FILE *fp = fopen(filename, "wb");
	fprintf(fp, "BM");
	fwrite(&bmi, 52, 1, fp);
	fwrite(img, 1, l * h, fp);
	fclose(fp);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(15, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glRotatef(zrot, 0, 0, 1);
	//glDrawElements(GL_LINES, 4, GL_UNSIGNED_BYTE, index);
	for (int i = 0; i < len * len; i++)
	{
		r = random;
		g = random;
		b = random;
		for (int j = 0; j < 4; j++)
		{
			color[12 * i + 3 * j] = r;
			color[12 * i + 3 * j + 1] = g;
			color[12 * i + 3 * j + 2] = b;
		}
	}
	glColorPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), color);
	glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), data);
	glDrawArrays(GL_QUADS, 0, 4 * len * len);
	//
	if (num < 100)
	{
		char str[10];
		glReadPixels(0, 0, 500, 500, GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
		sprintf(str, "%03d.bmp", num);
		WriteBMP(PixelData, str, 500, 500);
		num++;
	}

	//
	glutSwapBuffers();
	//xrot = xrot + 1;
	yrot = yrot + 1;

	//zrot = zrot + 1;
	//Sleep(100);
}

void reshape(int w, int h)
{
	float f = 5;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-f, f, -f * h / w, f * h / w, -f, f);
	else
		glOrtho(-f * w / h, f * w / h, -f, f, -f, f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(350, 120);
	glutInitWindowSize(500, 500);
	glutCreateWindow("");
	Initial();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
