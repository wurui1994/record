#include <QtWidgets/QApplication>

#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLPixelBuffer>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Construct an OpenGL pixel buffer.
    QGLPixelBuffer pixelBuffer(100, 100); 
    // Make the QGLContext object bound to pixel buffer the current context
    pixelBuffer.makeCurrent();

    // The opengl commands 
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glViewport(0, 0, 100, 100);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(4.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(0, 0);
    glVertex2i(100, 0);
    glVertex2i(50, 100);
    glEnd();

    // At last, the pixel buffer was saved as an image
    QImage pImage = pixelBuffer.toImage();
    pImage.save(QString::fromLocal8Bit("gl.png"));

    //return a.exec();
}