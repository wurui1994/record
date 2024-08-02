/* 
  clang++ -framework OpenGL shader.m
*/
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#endif

#include <stdio.h>

#include <OpenGL/OpenGL.h>
#include <Opengl/glext.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#else
#include <GL/glu.h>
#endif

#include <OpenGL/OpenGL.h>

#import <AppKit/AppKit.h>


void run_two(void)
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
	glShaderSource(vs, 1, &vs_s, 0);
	glShaderSource(fs, 1, &fs_s, 0);
	//
	// glCompileShader(vs);
	glCompileShader(fs);
	//
	GLuint program = glCreateProgram();
	// glAttachShader(program, vs);
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

#if USE_BUFFER
	unsigned int VBO, VAO;
	glGenVertexArraysAPPLE(1, &VAO);
    glBindVertexArrayAPPLE(VAO);
    
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
#else
    //
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)vertices);
#endif
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// glutSwapBuffers();
    glFinish();
}

#include <unistd.h>
//
int main(int argc, char *argv[])
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
      (CGLPixelFormatAttribute)0};
  CGLPixelFormatObj pix;
  CGLError errorCode;
  GLint num;
  errorCode = CGLChoosePixelFormat(attributes, &pix, &num);
  errorCode = CGLCreateContext(pix, NULL, &context);
  CGLDestroyPixelFormat(pix);
  errorCode = CGLSetCurrentContext(context);

int width = 400;
  int height = 400;


    GLuint m_frameBufferID, m_renderBufferID, m_depthBufferID;
    glGenFramebuffers(1, &m_frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);

    glGenRenderbuffers(1, &m_renderBufferID);

    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, width, height);

    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderBufferID);
    
    // run_one();
    glViewport(0, 0, width, height);
    run_two();
    //
    char img[width * height * 3];
	// glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    // glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);
    FILE* ff = fopen("abc.ppm", "w");
    char header[256];
    snprintf(header, 256, "P6 %d %d 255 ", width, height);
    size_t i = fwrite(header, sizeof(char), 16, ff);
    i = fwrite(img, sizeof(char), width * height * 3, ff);
    fclose(ff);
}