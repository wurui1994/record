#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,1);
	//glColor3i(0,(1<<31)-1,(1<<31)-1);
	//glColor3s(0,(1<<15)-1,(1<<15)-1);
	//GLfloat c[]={0,1,1};
	//glColor3fv(c);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(1,1);
	glEnd();
	glFlush();
}
int main(int argc,char*argv[])
{
	glutInit(&argc,argv);
	glutCreateWindow("title");
	glutDisplayFunc(display);
	glutMainLoop();
}