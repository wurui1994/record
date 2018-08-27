#include <GL/glew.h>
#include <GL/glut.h>
//
#include <time.h>
#include <math.h>
#include <stdlib.h>
//
#define width 640
#define height 480
//
void glutCenterWindow(void)
{
    int cx = glutGet(GLUT_SCREEN_WIDTH);
    int cy = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((cx - width) / 2, (cy - height) / 2);
}
//
void DrawWithShader(float vertices[], int number)
{
    const char *vs_s = "in vec3 aPos;\n"
                       "in vec3 aColor;\n"
                       "out vec3 ourColor;\n"
                       "void main()\n"
                       "{\n"
                       "   gl_Position = vec4(aPos, 1.0);\n"
                       "   ourColor = aColor;\n"
                       "}\0";
    const char *fs_s = "in vec3 ourColor;\n"
                       "void main()\n"
                       "{\n"
                       "   gl_FragColor = vec4(ourColor, 1.0f);\n"
                       "}\n\0";
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    //
    glShaderSource(vs, 1, &vs_s, NULL);
    glShaderSource(fs, 1, &fs_s, NULL);
    //
    glCompileShader(vs);
    glCompileShader(fs);
    //
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, number, vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
//
void Render(void)
{
    //
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //
    int st = clock();
    //
    float verticesOne[] = {
        // positions         // colors
        1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
    };
    //
    float verticesTwo[] = {
        // positions         // colors
        0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom right
        -1.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f   // top
    };
    DrawWithShader(verticesOne, sizeof(verticesOne));
    DrawWithShader(verticesTwo, sizeof(verticesTwo));
    int et = clock();
    // printf("Cost time = %fsecs.\n", 1.0 * (et - st) / CLOCKS_PER_SEC);
    glutSwapBuffers();
}
//
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCenterWindow();
    glutCreateWindow("Shader");
    //
    if (glewInit() != GLEW_OK)
        return -1;
    glutDisplayFunc(Render);
    glutIdleFunc(Render);
    glutMainLoop();
}