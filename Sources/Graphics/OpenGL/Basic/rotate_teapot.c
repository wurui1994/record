#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
float x_rotate = 0.0;
float y_rotate = 0.0;
float last_x;
float last_y;
typedef float GLMatrixf[16];
GLMatrixf mat_rotate;
GLMatrixf mat_saved;
void matrix_mult_f(float ori[16], float mul[16])
{
    float tmp[16];
    int o_r;
    int m_c;
    int i;
    memset(tmp, 0, sizeof(float) * 16);

    for (o_r = 0; o_r < 4; ++o_r)
    {
        for (m_c = 0; m_c < 4; ++m_c)
        {
            for (i = 0; i < 4; ++i)
            {
                tmp[o_r * 4 + m_c] += ori[o_r * 4 + i] * mul[i * 4 + m_c];
            }
        }
    }
    memcpy(ori, tmp, sizeof(tmp));
}
void matrix_rotate_x(float mat[16], float angle)
{
    float radious;

    memset(mat, 0, sizeof(float) * 16);
    radious = M_PI * angle / 180.0;

    mat[0] = 1.0;
    mat[15] = 1.0;
    mat[5] = cos(radious);
    mat[6] = sin(radious);
    mat[9] = 0 - mat[6];
    mat[10] = mat[5];
}
void matrix_rotate_y(float mat[16], float angle)
{
    float radious;

    memset(mat, 0, sizeof(float) * 16);
    radious = M_PI * angle / 180.0;

    mat[5] = 1.0;
    mat[15] = 1.0;
    mat[0] = cos(radious);
    mat[8] = sin(radious);
    mat[2] = 0 - mat[8];
    mat[10] = mat[0];
}
void matrix_init_e(float mat[16])
{
    memset(mat, 0, sizeof(float) * 16);
    mat[0] = 1.0;
    mat[5] = 1.0;
    mat[10] = 1.0;
    mat[15] = 1.0;
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    matrix_init_e(mat_saved);
}
void draw_model(GLenum mode)
{
    glColor3f(1.0, 1.0, 0.0);
    glutWireTeapot(1.5);
}
void rotate_model(void)
{
    // 如果没有拖动鼠标，就不进行后续的运算了。
    if ((0.01 > x_rotate && -0.01 < x_rotate) && (0.01 > y_rotate && -0.01 < y_rotate))
    {
        glMultMatrixf(mat_saved);

        return;
    }

    if (0.01 < x_rotate || -0.01 > x_rotate)
    {
        matrix_rotate_x(mat_rotate, x_rotate);
        matrix_mult_f(mat_saved, mat_rotate);

        x_rotate = 0.0;
    }
    if (0.01 < y_rotate || -0.01 > y_rotate)
    {
        matrix_rotate_y(mat_rotate, y_rotate);
        matrix_mult_f(mat_saved, mat_rotate);

        y_rotate = 0.0;
    }
    glMultMatrixf(mat_saved);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); /* clear the matrix */
    /* viewing transformation  */
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    rotate_model();

    draw_model(GL_RENDER);
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}
void motion_func(int x, int y)
{
    y_rotate += (x - last_x) / 3.0;
    x_rotate += (y - last_y) / 3.0;
    last_x = x;
    last_y = y;
}
void mouse_func(int button, int state, int x, int y)
{
    if (GLUT_LEFT_BUTTON == button)
    {
        if (GLUT_DOWN == state)
        {
            last_y = y;
            last_x = x;
        }
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cube for Test");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion_func);
    glutMouseFunc(mouse_func);

    glutMainLoop();
    return 0;
}
