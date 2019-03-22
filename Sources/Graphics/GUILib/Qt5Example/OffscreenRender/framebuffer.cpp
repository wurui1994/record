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
    
    QOpenGLContext context;
    context.setFormat(QSurfaceFormat::defaultFormat());
    context.create();

    QOffscreenSurface surface;
    surface.create();
    surface.setFormat(context.format());

    context.makeCurrent(&surface);

    QOpenGLFramebufferObject frameBuffer(100,100);
     
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
    
    // At last, the frame buffer was saved as an image
    QImage pImage = frameBuffer.toImage();
    pImage.save(QString::fromLocal8Bit("opengl.png"));

    //return a.exec();
}