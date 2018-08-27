#pragma comment(lib, "jpeg.lib")
#include <jpeglib.h>
#include <jerror.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
vector<string> vec;
int num = 0;
//================================
GLuint LoadJPEG(const char *FileName)
//================================
{
	FILE *fd;
	unsigned char *image;
	int width, height, depth;
	fd = fopen(FileName, "rb");
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPROW row_pointer[1];
	unsigned long location = 0;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fd);
	jpeg_read_header(&cinfo, 0);
	cinfo.scale_num = 1;
	//cinfo.scale_denom = SCALE;
	jpeg_start_decompress(&cinfo);
	width = cinfo.output_width;
	height = cinfo.output_height;
	depth = cinfo.num_components; //should always be 3
	image = (unsigned char *)malloc(width * height * depth);
	row_pointer[0] = (unsigned char *)malloc(width * depth);
	/* read one scan line at a time */
	while (cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo, row_pointer, 1);
		for (int i = 0; i < (width * depth); i++)
			image[location++] = row_pointer[0][i];
	}
	fclose(fd);
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	GLuint texture_id;
	//----- create OpenGL tex map (omit if not needed) --------
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
	free(image);
	return texture_id; // for OpenGL tex maps
}

void subimage(string &s)
{
	GLuint texGround = LoadJPEG(s.c_str());
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	glDeleteTextures(1, &texGround);
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
	cout << vec.size() << endl;
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
	//cout<<vec[0]<<endl;
	if (num == vec.size())
		exit(0);
	subimage(vec[num++]);
	glutSwapBuffers();
	//glFlush();
}

int main(int argc, char **argv)
{
	initiate();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(350, 120);
	glutInitWindowSize(500, 500);
	glutCreateWindow("");
	glEnable(GL_TEXTURE_2D);
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}