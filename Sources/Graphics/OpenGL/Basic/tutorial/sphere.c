#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define tick 8
void display()
{
	static float rot = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1, 0);
	glLoadIdentity();
	glRotatef(60, 1, 0, 0);
	//glLoadIdentity();
	glRotatef(rot++, 0, 0, 1);
	glutWireSphere(0.8, 20, 20);
	glFlush();
}
void OnTimer(int id)
{
	glutPostRedisplay();
	glutTimerFunc(tick,OnTimer,1);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutTimerFunc(tick, OnTimer, 1);
	//glutIdleFunc(display);
	glutMainLoop();
	return 0;
}