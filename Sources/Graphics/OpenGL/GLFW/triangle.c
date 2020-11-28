/* 
macOS: 
  brew install glfw glew
  clang `pkg-config --libs glfw3 glew` -framework OpenGL triangle.c -o triangle
  ./triangle
*/
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#endif
#include <GLFW/glfw3.h>

// #pragma comment(lib,"glfw3")
// #pragma comment(lib,"opengl32")

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 320, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(window, (mode->width - 480) / 2, (mode->height - 320) / 2);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        /* Draw a triangle */
        glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0); // Red
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0.0, 1.0, 0.0); // Green
        glVertex3f(-1.0, -1.0, 0.0);

        glColor3f(0.0, 0.0, 1.0); // Blue
        glVertex3f(1.0, -1.0, 0.0);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}