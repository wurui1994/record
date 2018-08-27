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
	unsigned long x, y;
	unsigned int texture_id;
	unsigned long data_size; // length of the file
	int channels;			 //  3 =>RGB   4 =>RGBA
	unsigned int type;
	unsigned char *rowptr[1];			// pointer to an array
	unsigned char *jdata;				// data for the image
	struct jpeg_decompress_struct info; //for our jpeg info
	struct jpeg_error_mgr err;			//the error handler

	FILE *file = fopen(FileName, "rb"); //open the file

	info.err = jpeg_std_error(&err);
	jpeg_create_decompress(&info); //fills info structure

	//if the jpeg file doesn't load
	if (!file)
	{
		fprintf(stderr, "Error reading JPEG file %s!", FileName);
		return 0;
	}

	jpeg_stdio_src(&info, file);
	jpeg_read_header(&info, TRUE); // read jpeg file header

	jpeg_start_decompress(&info); // decompress the file

	//set width and height
	x = info.output_width;
	y = info.output_height;
	channels = info.num_components;
	type = GL_RGB;
	if (channels == 4)
		type = GL_RGBA;

	data_size = x * y * 3;

	//--------------------------------------------
	// read scanlines one at a time & put bytes
	//    in jdata[] array. Assumes an RGB image
	//--------------------------------------------
	jdata = (unsigned char *)malloc(data_size);
	while (info.output_scanline < info.output_height)
	{ // loop
		// Enable jpeg_read_scanlines() to fill our jdata array
		rowptr[0] = (unsigned char *)jdata + // secret to method
					3 * info.output_width * (info.output_height - info.output_scanline);

		jpeg_read_scanlines(&info, rowptr, 1);
	}
	//---------------------------------------------------

	jpeg_finish_decompress(&info); //finish decompressing

	//----- create OpenGL tex map (omit if not needed) --------
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, x, y, GL_RGB, GL_UNSIGNED_BYTE, jdata);

	fclose(file); //close the file
	free(jdata);

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