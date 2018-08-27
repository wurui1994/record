#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
//
#define width 640
#define height 480

clock_t st, et;
GLuint program;
GLuint vs;
GLuint fs;
const GLchar *vs_s = "attribute vec4 p;void main(){gl_Position=p;}";

const GLchar *fs_s = "uniform vec4 ourColor;"
                     "void main(){gl_FragColor=ourColor;}";

void Run(void);
void Init(void);
void OnTimer(int value);
void glutCenterWindow(void);
//
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCenterWindow();
    glutCreateWindow("title");
    //
    if (glewInit() != GLEW_OK)
        return -1;
    //
    Init();
    glutDisplayFunc(Run);
    glutIdleFunc(Run);
    // glutTimerFunc(1000, OnTimer, 1);
    glutMainLoop();
}
//
void glutCenterWindow(void)
{
    int cx = glutGet(GLUT_SCREEN_WIDTH);
    int cy = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((cx - width) / 2, (cy - height) / 2);
}
//
void Init()
{
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    //

    //
    glShaderSource(vs, 1, &vs_s, NULL);
    glShaderSource(fs, 1, &fs_s, NULL);
    //
    glCompileShader(vs);
    glCompileShader(fs);
    //
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    float vertices[] =
        {
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            0.0f, 0.5f, 0.0f    // top
        };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    //
    st = clock();

    glUseProgram(program);
}
//
void OnTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000, OnTimer, 1);
}
//
void Run(void)
{
    //
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //
    int et = clock();
    float dt = 1.0 * (et - st) / CLOCKS_PER_SEC;
    float redValue = sin(dt);
    float greenValue = cos(dt) * sin(dt);
    float blueValue = cos(dt) * cos(dt);
    // printf("%f\n",greenValue);
    int vertexColorLocation = glGetUniformLocation(program, "ourColor");
    glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();
}