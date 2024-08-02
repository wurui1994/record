#include <stdio.h>

#include <OpenGL/OpenGL.h>
#include <Opengl/glext.h>
#include <Opengl/glu.h>

int main(int argc, const char* argv[])
{
    CGLContextObj context;
    CGLPixelFormatAttribute attributes[13] = {
        kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute)kCGLOGLPVersion_Legacy,
        kCGLPFAAccelerated,
        kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
        kCGLPFAAlphaSize, (CGLPixelFormatAttribute)8,
        kCGLPFADoubleBuffer,
        kCGLPFASampleBuffers, (CGLPixelFormatAttribute)1,
        kCGLPFASamples, (CGLPixelFormatAttribute)4,
        (CGLPixelFormatAttribute)0
    };
    CGLPixelFormatObj pix;
    CGLError errorCode;
    GLint num;
    errorCode = CGLChoosePixelFormat(attributes, &pix, &num);
    errorCode = CGLCreateContext(pix, NULL, &context);
    CGLDestroyPixelFormat(pix);
    errorCode = CGLSetCurrentContext(context);

    //--------
    GLuint fbo, rbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 100, 100);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);
    // glBindRenderbuffer( GL_RENDERBUFFER, 0 );

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
    // -------
    // errorCode = CGLFlushDrawable(context);

    char data[100 * 100 * 3];
    glReadPixels(0, 0, 100, 100, GL_BGR, GL_UNSIGNED_BYTE, data);
    FILE* ff = fopen("pippo.ppm", "w");
    char* header = "P6 100 100 255 ";
    size_t i = fwrite(header, sizeof(char), 16, ff);
    i = fwrite(data, sizeof(char), 100 * 100 * 3, ff);
    fclose(ff);

    return 0;
}