#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

GLfloat fLightPos[4] = {-100.0f, 100.0f, 50.0f, 1.0f};
GLfloat fNoLight[] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat fLowLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
GLfloat fBrightLight[] = {1.0f, 1.0f, 1.0f, 1.0f};

static GLfloat yRot;

void DrawGround()
{
	GLfloat fExtent = 20.0f;
	GLfloat y = -0.0f;
	GLfloat step = 0.5f;

	GLfloat x, z;
	int iColor = 0;
	glShadeModel(GL_FLAT);
	for (x = -fExtent; x <= fExtent; x += step)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (z = fExtent; z >= -fExtent; z -= step)
		{
			if ((iColor % 2) == 0)
			{
				glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
			}
			else
			{
				glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			}
			glVertex3f(x, y, z);
			glVertex3f(x + step, y, z);

			iColor++;
		}
		glEnd();
	}
	glShadeModel(GL_SMOOTH);
}

void DrawGemometry()
{
	glPushMatrix();
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawGround();

		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.3f, -3.5f);
		glRotatef(-yRot * 2.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.0f, 0.0f, 0.0f);
		glutSolidSphere(0.1f, 17, 13);
	}
	glPopMatrix();
}

void RenderScene()
{
	yRot = 35.0f;
	GLfloat pass = 10.0f;
	for (int i = 0; i < 10; ++i)
	{
		yRot += 0.75f;
		DrawGemometry();

		//复制到累积缓冲区
		if (i == 0)
		{
			glAccum(GL_LOAD, 0.5f);
		}
		else
		{
			//累加到累积缓冲区
			glAccum(GL_ACCUM, (0.5f * 1 / pass));
		}
	}

	glAccum(GL_RETURN, 1.0f);
	glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0)
	{
		h = 1;
	}

	glViewport(0, 0, w, h);

	GLfloat faspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(35.0f, faspect, 1.0f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -0.4f, 0.0f);

	glutPostRedisplay();
}

void SetupRC()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//设置光照
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fNoLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, fLowLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fBrightLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, fBrightLight);
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//开启颜色追踪
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
}

int main(int args, char **argv)
{
	glutInit(&args, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ACCUM);
	glutInitWindowSize(800, 600);
	glutCreateWindow("motion blur");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	SetupRC();

	glutMainLoop();
	return 0;
}