//tcc -lgsl -lglut -lGL -run gsl_opengl.c
#include <gsl/gsl_qrng.h>
#include <GL/glut.h>

// #pragma comment(lib,"glut32")
// #pragma comment(lib,"gsl")
// #pragma comment(lib,"opengl32")
// #pragma comment(lib,"freeglut")

void glutInitialize()
{
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1,-1,0);
    glScalef(2,2,1);
    glViewport(0,0,512,512);
    glPointSize(3.0);
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    const int n = 100;
    gsl_qrng* qrng = gsl_qrng_alloc(gsl_qrng_sobol,2);
    glBegin(GL_POINTS);
    glColor3f(0,0,1);
    for( int i=0; i<n; i++ )
    {
        double s[2];
        gsl_qrng_get(qrng,s);
        glVertex3f(s[0],s[1],0.0);
    }
    glEnd();
    gsl_qrng_free(qrng);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-512)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-640)/2);
    glutInitWindowSize(512,512);
    glutCreateWindow("GSL Quasi Random Number Generator");
    glutInitialize();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}