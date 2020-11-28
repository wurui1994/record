#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Width 500
#define Height 500

GLubyte PixelData[Width*Height*3];

void WriteBMP(GLubyte *img,const char* filename,int w,int h)
{
	int l=(w*3+3)/4*4;
	int bmi[]= {l*h+54,0,54,40,w,h,1|3*8<<16,0,l*h,0,0,0,0};
	FILE *fp = fopen(filename,"wb");
	fprintf(fp,"BM");
	fwrite(&bmi,52,1,fp);
	fwrite(img,1,l*h,fp);
	fclose(fp);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	
	//
	glReadPixels(0, 0, Width, Height,GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	WriteBMP(PixelData,"test.bmp",Width,Height);
	//
	glutSwapBuffers();
	// xrot = xrot + 1;
	// yrot = yrot + 1;
	// zrot = zrot + 1;
}

void reshape(int w, int h)
{
	int factor = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-factor, factor, -factor * (GLfloat)h / (GLfloat)w, factor * (GLfloat)h / (GLfloat)w, -factor, factor);
	else
		glOrtho(-factor*(GLfloat)w / (GLfloat)h, factor*(GLfloat)w / (GLfloat)h, -factor, factor, -factor, factor);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(350, 120);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);
	//glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
