#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

void render(void)
{
	const int n = 20;
	const GLfloat R = 0.5f;
	const GLfloat Pi = 3.1415926536f;
	//
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i)
	{
		glVertex2f(R * cos(2 * Pi / n * i), R * sin(2 * Pi / n * i));
	}
	glEnd();
	glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Circle");
	glutDisplayFunc(&render);
	glutMainLoop();
	return 0;
}