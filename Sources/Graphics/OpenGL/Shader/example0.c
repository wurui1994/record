#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
//
#define width 640
#define height 480
//
void Run(void);
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
	// glClearColor(1,1,1,1);
	glutDisplayFunc(Run);
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
void Run(void)
{
	//
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//
	const GLchar *vs_s = "attribute vec4 p;void main(){gl_Position=p;}";
	const GLchar *fs_s = "void main(){gl_FragColor=vec4(1.0,0.0,0.0,1.0);}";
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
	//
	float vertices[] = {
		-0.9f, -0.5f, 0.0f, // left
		-0.0f, -0.5f, 0.0f, // right
		-0.45f, 0.5f, 0.0f, // top
							// second triangle
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glutSwapBuffers();
}