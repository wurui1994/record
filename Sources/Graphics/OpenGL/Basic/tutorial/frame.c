#include <stdio.h>
#include <time.h>
#define false 0
#define true (!false)
typedef int bool;
#include <GL/glut.h>

void display();
void keyboard(unsigned char key, int x, int y);

float g_fps(void (*func)(void), int n_frame);

bool finish_without_update = false;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("fps");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'F':
	case 'f':
		finish_without_update = true;
		printf("%f fps\n", g_fps(display, 100));
		finish_without_update = false;
		break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1, 0.1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0, 0, 1,
		0, 0, 0,
		0, 1, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glutSolidTeapot(.1);
	glutSwapBuffers();
}

float g_fps(void (*func)(void), int n_frame)
{
	clock_t start, finish;
	int i;
	float fps;

	printf("Performing benchmark, please wait");
	start = clock();
	for (i = 0; i < n_frame; i++)
	{
		if ((i + 1) % 10 == 0)
			printf(".");
		func();
	}
	printf("done\n");
	finish = clock();

	fps = (float)(n_frame) / (finish - start) * CLOCKS_PER_SEC;
	return fps;
}