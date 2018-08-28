#include <windows.h>
#include <gdiplus.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma comment(lib, "gdiplus")
using namespace std;
using namespace Gdiplus;

vector<string> vec;
int num = 0;
UINT *pixels;
BitmapData *bitmapData = new BitmapData;
//================================
GLuint LoadJPEG(const char *file)

{
	size_t len = strlen(file) + 1;
	size_t converted = 0;
	wchar_t *wstr = new wchar_t[len];
	mbstowcs_s(&converted, wstr, len, file, _TRUNCATE);
	Bitmap bitmap(wstr);
	BitmapData *bitmapData = new BitmapData;
	int w = bitmap.GetWidth(), h = bitmap.GetHeight();
	Rect rect(0, 0, w, h);

	// Lock a 5x3 rectangular portion of the bitmap for reading.
	bitmap.LockBits(&rect, ImageLockModeRead, PixelFormat24bppRGB, bitmapData);
	//printf("The stride is %d.\n\n", bitmapData->Stride);
	// Display the hexadecimal value of each pixel in the 5x3 rectangle.
	UINT *pixels = (UINT *)bitmapData->Scan0;
	bitmap.UnlockBits(bitmapData);

	delete bitmapData;

	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	return texture_id; // for OpenGL tex maps
}

void subimage(string &s)
{
	int texGround = LoadJPEG(s.c_str());
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
}
void initiate()
{
	//
	ifstream ifs("test.txt");
	string temp;
	int tempr, tempt;
	while (!ifs.eof())
	{
		getline(ifs, temp);
		if (temp.length() > 4)
			vec.push_back(temp);
		//cout<<temp<<endl;
	}
	ifs.close();
	//cout<<vec.size()<<endl;
}
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//

	// for(int i=0;i<vec.size();i++)
	// cout<<vec[i]<<endl;
	//
	if (num == vec.size())
		return;
	subimage(vec[num]);
	num++;
	glutSwapBuffers();
	//glFlush();
}

int main(int argc, char **argv)
{
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(350, 120);
	glutInitWindowSize(500, 500);
	glutCreateWindow("");
	initiate();
	glEnable(GL_TEXTURE_2D);
	glutDisplayFunc(display);
	//getchar();
	//glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
	GdiplusShutdown(gdiplusToken);
	return 0;
}