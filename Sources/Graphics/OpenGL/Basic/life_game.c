#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>
#include <GL/glut.h>
#define random (rand() / (RAND_MAX + 1.0))
#define M 1024
#define N 1024
static int G[M][N];
int c[M][N];
int s, x, y;

void square(int i, int j)
{
	i = i - M / 2.0;
	j = j - N / 2.0;
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(i, j);
	glVertex2f(i, j + 1);
	glVertex2f(i + 1, j + 1);
	glVertex2f(i + 1, j);
	glEnd();
	// glColor3f(1,0,1);
	// glBegin(GL_LINE_LOOP);
	// glVertex2f(i,j);
	// glVertex2f(i,j+1);
	// glVertex2f(i+1,j+1);
	// glVertex2f(i+1,j);
	// glEnd();
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			s = 0;
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					x = i + dx;
					y = j + dy;
					if (x == -1)
						x = M - 1;
					if (y == -1)
						y = N - 1;
					if (x == M)
						x = 0;
					if (y == N)
						y = 0;
					if (!(dx == 0 && dy == 0))
						s += G[x][y];
				}
			}
			c[i][j] = (G[i][j] & (s == 2)) | (s == 3);
		}
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			G[i][j] = c[i][j];
		}
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (G[i][j])
				square(i, j);
		}
	}
	Sleep(100);
	glutSwapBuffers();
	//glFlush();
}

void reshape(int w, int h)
{
	double factor = M / 2;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-factor, factor, -factor * h / w, factor * h / w, -factor, factor);
	else
		glOrtho(-factor * w / h, factor * w / h, -factor, factor, -factor, factor);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initiate()
{
	srand(time(NULL));
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			G[i][j] = round(random);
		}
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	//glutInitDisplayMode(GLUT_SINGLE);
	// glutInitWindowPosition(350, 120);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 512) / 2,
						   (glutGet(GLUT_SCREEN_HEIGHT) - 640) / 2);
	glutInitWindowSize(500, 500);
	glutCreateWindow("");
	initiate();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
