#include <GL/glut.h>
void display(void)
{
	glClear(0);
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