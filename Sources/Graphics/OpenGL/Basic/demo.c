// #include <Windows.h>
#include <GL/glut.h>
//
#define width 640
#define height 480
//
void Run(void)
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat c[] = {0, 0, 1};
    glColor3fv(c);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(1, 1);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - 640) / 2);
    glutInitWindowSize(width, height);
    glutCreateWindow("title");

    // glClearColor(1,1,1,1);
    glutDisplayFunc(Run);
    glutMainLoop();
}