// clang++ -std=c++11 shader.cpp -framework OpenGL

#ifndef EGLWRAPPER_HH
#define EGLWRAPPER_HH

#include <OpenGL/CGLTypes.h>
#include <OpenGL/CGLCurrent.h>
#include <OpenGL/OpenGL.h>
#include <fstream>
#include <iostream>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#else
#include <GL/glu.h>
#endif

#include <map>
#include <string>
#include <iostream>
// #include <GL/glew.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#else
#include <GL/glu.h>
#endif

inline std::string glGetErrorString()
{
    GLenum error;
    std::string result;
    std::map<GLuint, const char *> errorDescriptions = {
        {GL_INVALID_ENUM, "Invalid enum"},
        {GL_INVALID_VALUE, "Invalid value (out of range)"},
        {GL_INVALID_OPERATION, "Invalid operation (not allowed in current state)"},
        {GL_INVALID_FRAMEBUFFER_OPERATION, "Invalid framebuffer operation (framebuffer not complete)"},
        {GL_OUT_OF_MEMORY, "Out of memory"},
        {GL_STACK_UNDERFLOW, "Stack underflow"},
        {GL_STACK_OVERFLOW, "Stack overflow"},
    };
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        if (result.size())
            result += '\n';
        try
        {
            result += errorDescriptions.at(error);
        }
        catch (...)
        {
            result += "Unknown";
        }
    }
    return result;
}

inline void glCheckError(const std::string &operation = "")
{
    auto err = glGetErrorString();
    if (err.size())
    {
        throw std::runtime_error("GL error" + ((operation.size() ? " encountered in " : "") + operation) + ":\n" + err);
    }
}

inline void glCheckStatus(GLint id, GLenum statusType)
{
    GLint success;
    std::string desc;
    if (statusType == GL_COMPILE_STATUS)
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        desc = "Shader compilation";
    }
    else if (statusType == GL_LINK_STATUS)
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        desc = "Program link";
    }
    else
    {
        throw std::logic_error("Unknown status type");
    }

    if (success == GL_FALSE)
    {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cerr << desc << " failed: " << infoLog << std::endl;
        throw std::runtime_error(desc + " failed -- check cerr");
    }
}

using ImageBuffer = std::vector<unsigned char>;
struct CGLWrapper
{
    CGLWrapper(int width, int height, GLenum /* format */ = GL_RGBA,
               GLint depthBits = 24, GLint stencilBits = 0, GLint accumBits = 0)
    {
        // Initialize CGL
        // CGLPixelFormatAttribute pixAttributes[12] = {
        //     kCGLPFAAccelerated,                                                      // Presence of boolean flags implies `true` value according to documentation
        //     kCGLPFAOpenGLProfile, CGLPixelFormatAttribute(kCGLOGLPVersion_3_2_Core), // Uses latest available version (not actually 3.2!!)
        //     kCGLPFADepthSize, CGLPixelFormatAttribute(depthBits),
        //     kCGLPFAAlphaSize, CGLPixelFormatAttribute(8),
        //     kCGLPFAStencilSize, CGLPixelFormatAttribute(stencilBits),
        //     kCGLPFAAccumSize, CGLPixelFormatAttribute(accumBits),
        //     CGLPixelFormatAttribute(0)};

        CGLPixelFormatAttribute pixAttributes[13] = {
            kCGLPFAOpenGLProfile,
            (CGLPixelFormatAttribute)kCGLOGLPVersion_GL4_Core,
            kCGLPFAAccelerated,
            kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
            kCGLPFAAlphaSize, (CGLPixelFormatAttribute)8,
            kCGLPFADoubleBuffer,
            kCGLPFASampleBuffers, (CGLPixelFormatAttribute)1,
            kCGLPFASamples, (CGLPixelFormatAttribute)4,
            (CGLPixelFormatAttribute)0
    };

        {
            CGLPixelFormatObj pix;
            GLint num;
            CGLError errorCode = CGLChoosePixelFormat(pixAttributes, &pix, &num);
            if (errorCode != kCGLNoError)
                throw std::runtime_error("CGLChoosePixelFormat failure");

            errorCode = CGLCreateContext(pix, NULL, &m_ctx);
            if (errorCode != kCGLNoError)
                throw std::runtime_error("CGLCreateContext failure");

            CGLDestroyPixelFormat(pix);
        }

        // std::cout << "Initialize CGL " << m_ctx << std::endl;

        m_makeCurrent();

        static bool firstTime = true;
        if (firstTime)
        {
            std::cout << glGetString(GL_VERSION) << std::endl;
            firstTime = false;
        }

        // Initialize GLEW entry points for our new context
        // m_glewInit();

        glGenFramebuffers(1, &m_frameBufferID);
        glGenRenderbuffers(1, &m_renderBufferID);
        // glGenRenderbuffers(1, &m_depthBufferID);

        resize(width, height); // Trigger buffer generation/binding
    }

    virtual ~CGLWrapper()
    {
        // std::cout << "Destroy CGL " << m_ctx << std::endl;
        makeCurrent();

        auto oldErrors = glGetErrorString(); // Flush any old errors
        if (oldErrors.size())
            std::cerr << "Unreported errors found on context destruction:" << std::endl
                      << oldErrors << std::endl;

        glDeleteRenderbuffers(1, &m_renderBufferID);
        glDeleteRenderbuffers(1, &m_depthBufferID);
        glDeleteFramebuffers(1, &m_frameBufferID);

        // CGLSetCurrentContext(nullptr);
        CGLDestroyContext(m_ctx);
    }

    void resize(int width, int height, bool skipViewportCall = false)
    {
        m_width = width;
        m_height = height;
        m_buffer.resize(width * height * 4);
        m_resizeImpl(width, height);
        if (!skipViewportCall)
            glViewport(0, 0, width, height);
    }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    void makeCurrent() { m_makeCurrent(); }

    void finish()
    {
        glFinish();
        m_readImage();
    }

    const ImageBuffer &buffer() const { return m_buffer; }

    const ImageBuffer unpremultipliedBuffer() const
    {
        // For transparent images, the render output has a "premultiplied alpha"
        // (i.e., the color components are scaled by the alpha component, and
        // the image has already effectively been composited against a black background).
        // We must divide by the alpha channel before saving.

        // More cache friendly, direct implementation (somehow ~20x faster than the fastest Eigen variant above!)
        ImageBuffer result = m_buffer;
        unsigned char *end = result.data() + m_buffer.size();
        for (unsigned char *pixel = result.data(); pixel != end; pixel += 4)
        {
            // const unsigned char alpha_uchar = pixel[3] == 0 ? 1 : pixel[3];
            // float scale = 255.0f / alpha_uchar;
            const unsigned char alpha_uchar = pixel[3];
            float scale = (alpha_uchar == 0) ? 1.0f : 255.0f / alpha_uchar;
            pixel[0] = (unsigned char)(float(pixel[0]) * scale + 0.5f);
            pixel[1] = (unsigned char)(float(pixel[1]) * scale + 0.5f);
            pixel[2] = (unsigned char)(float(pixel[2]) * scale + 0.5f);
        }
        return result;
    }

    void writePPM(const std::string &path, bool unpremultiply = true) const
    {
        std::ofstream outFile(path, std::ofstream::binary);
        if (!outFile.is_open())
            throw std::runtime_error("Failed to open " + path);

        outFile << "P6\n";
        outFile << m_width << " " << m_height << "\n";
        outFile << "255\n";

        const ImageBuffer &buf = unpremultiply ? unpremultipliedBuffer() : buffer();

        // Write the RGB components of the image in PPM format.
        // Due to the opposite vertical axis conventions of OpenGL and PPM, the
        // buffer holds a vertically flipped image; we flip it while writing.
        for (int row = 0; row < m_height; ++row)
        {
            for (int col = 0; col < m_width; ++col)
            {
                int pixel = (m_height - row - 1) * m_width + col;
                outFile.write((const char *)&buf[4 * pixel], 3);
            }
        }
    }

private:
    void m_makeCurrent()
    {
        // std::cout << "Make current CGL " << m_ctx << std::endl;
        CGLError errorCode = CGLSetCurrentContext(m_ctx);
        if (errorCode != kCGLNoError)
            throw std::runtime_error("CGLSetCurrentContext failure");
    }

    void m_readImage()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
        // glReadPixels(0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer.data());
        glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_buffer.data());
        FILE* ff = fopen("pippo.ppm", "w");
        char* header = "P6 400 400 255 ";
        size_t i = fwrite(header, sizeof(char), 16, ff);
        i = fwrite(m_buffer.data(), sizeof(char), m_width * m_height * 3, ff);
        fclose(ff);
        exit(0);
        glCheckError("Read image");
    }

    void m_resizeImpl(int width, int height)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);

        // glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferID);
        // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderBufferID);
        // glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferID);

        glCheckError("allocate framebuffers");

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("framebuffer is not complete!");
    }

    CGLContextObj m_ctx = nullptr;
    GLuint m_frameBufferID = 0,
           m_renderBufferID = 0,
           m_depthBufferID = 0;

    int m_width, m_height;
    ImageBuffer m_buffer;
};

#endif /* end of include guard: EGLWRAPPER_HH */

#include <stdio.h>
#include <stdlib.h>

// #include <Eigen/Dense>
#include <stdexcept>
// #include "OpenGLContext.hh"
// #include "CGLWrapper.inl"

int main(int argc, char *argv[])
{
    int width = 400;
    int height = 400;
    char *filename = NULL;

    if (argc < 2)
    {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  osdemo filename [width height]\n");
        return 0;
    }

    filename = argv[1];
    if (argc == 4)
    {
        width = atoi(argv[2]);
        height = atoi(argv[3]);
    }

    // auto ctx = OpenGLContext::construct(width, height);
    CGLWrapper ctx(width, height);
    ctx.makeCurrent();

    // auto shader = Shader::fromFiles(ctx, SHADER_PATH "/demo.vert", SHADER_PATH "/demo.frag");
    // for (const auto &u : shader->getUniforms())
    // {
    //     std::cout << "Uniform " << u.loc << ": " << u.name << std::endl;
    // }
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *vs_s = "#version 330 core\n"
                         "layout (location = 0) in vec3 position;\n"
                         "void main()\n"
                         "{\n"
                         "gl_Position = vec4(position, 1.0);\n"
                         "}\0";
    const GLchar *fs_s = "#version 330 core\n"
                         "out vec4 color;\n"
                         "void main()\n"
                         "{\n"
                         "color = vec4(1.0f,0.0f, 1.0f,1.0f);\n"
                         "}\n\0";
    //
    glShaderSource(vs, 1, &vs_s, NULL);
    glShaderSource(fs, 1, &fs_s, 0);
    //
    glCompileShader(vs);
    int success;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        printf("ERROR::SHADER::vs::COMPILATION_FAILED\n%s\n", infoLog);
    }
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        printf("ERROR::SHADER::fs::COMPILATION_FAILED\n%s\n", infoLog);
    }
    //
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    glUseProgram(program);

    ctx.makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // vao.draw(*shader);
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    float data_out[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};
    float data[] = {
        -0.9f, -0.5f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, // top
                            // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 9 * sizeof(float),
                 data, GL_STATIC_DRAW);

    int loc = 0;
    glVertexAttribPointer(loc,
                          3, GL_FLOAT, // # cols floats per vertex
                          GL_FALSE,    // Don't normalize
                          0, 0);       // No gap between vertex data, and no offset from array beginning.
    glCheckError();
    glEnableVertexAttribArray(loc);
    glCheckError();
    glCheckError();

    // bind();
    glCheckError();

    std::cout << "glDrawArrays (unindexed)" << 9 << std::endl;
    // glDrawArraysInstanced(GL_TRIANGLES, 0, 18, instances);
    glDrawArrays(GL_TRIANGLES, 0, 18);

    ctx.finish();

    if (filename)
        // ctx.writePNG(filename);
        ctx.writePPM(filename);

    return 0;
}
