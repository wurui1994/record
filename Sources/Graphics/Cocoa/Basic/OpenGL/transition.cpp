/*
  clang++ -framework OpenGL shader.m
*/
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <OpenGL/OpenGL.h>
#include <Opengl/glext.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl3.h>
#else
#include <GL/glu.h>
#endif

//
#define width 400
#define height 400
//
#define USE_BUFFER 1

static const float position[12] = {
    -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};

#if 1
static const GLchar *v_shader_source =
  "#version 330\n"
  "in vec2 position;\n"
  "out vec2 _uv;\n"
  "void main(void) {\n"
  "  gl_Position = vec4(position, 0, 1);\n"
  "  vec2 uv = position * 0.5 + 0.5;\n"
  "  _uv = vec2(uv.x, 1.0 - uv.y);\n"
  "}\n";

static const GLchar *f_shader_template =
  "#version 330\n"
  "in vec2 _uv;\n"
  "uniform sampler2D from;\n"
  "uniform sampler2D to;\n"
  "uniform float progress;\n"
  "uniform float ratio;\n"
  "uniform float _fromR;\n"
  "uniform float _toR;\n"
  "\n"
  "vec4 getFromColor(vec2 uv) {\n"
  "  return texture(from, vec2(uv.x, 1.0 - uv.y));\n"
  "}\n"
  "\n"
  "vec4 getToColor(vec2 uv) {\n"
  "  return texture(to, vec2(uv.x, 1.0 - uv.y));\n"
  "}\n"
  "\n"
  "\n%s\n"
  "out vec4 color;\n"
  "void main() {\n"
  "  color = transition(_uv);\n"
  "}\n";

// default to a basic fade effect
static const GLchar *f_default_transition_source =
  "vec4 transition (vec2 uv) {\n"
  "  return mix(\n"
  "    getFromColor(uv),\n"
  "    getToColor(uv),\n"
  "    progress\n"
  "  );\n"
  "}\n";
#else
static const GLchar *v_shader_source =
    "#version 330\n"
    "in vec2 position;\n"
    "out vec2 _uv;\n"
    "void main(void) {\n"
    "  gl_Position = vec4(position, 0, 1);\n"
    "  vec2 uv = position * 0.5 + 0.5;\n"
    "  _uv = vec2(uv.x, 1.0 - uv.y);\n"
    "}\n";

static const GLchar *f_shader_template =
    "#version 330\n"
    "in vec2 _uv;\n"
    "uniform sampler2D from;\n"
    "uniform sampler2D to;\n"
    "uniform float progress;\n"
    "uniform float ratio;\n"
    "uniform float _fromR;\n"
    "uniform float _toR;\n"
    "\n"
    "vec4 getFromColor(vec2 uv) {\n"
    "  return texture(from, vec2(uv.x, 1.0 - uv.y));\n"
    "}\n"
    "\n"
    "vec4 getToColor(vec2 uv) {\n"
    "  return texture(to, vec2(uv.x, 1.0 - uv.y));\n"
    "}\n"
    "\n"
    "\n%s\n"
    "out vec4 color;\n"
    "void main() {\n"
    // "  color = transition(_uv);\n"
    "  color = vec4(1.0,0.0,1.0,1.0);\n"
    "}\n";

// default to a basic fade effect
static const GLchar *f_default_transition_source =
    "vec4 transition (vec2 uv) {\n"
    "  return mix(\n"
    "    getFromColor(uv),\n"
    "    getToColor(uv),\n"
    "    progress\n"
    "  );\n"
    "}\n";
#endif
//
CGLContextObj setupContext()
{
    CGLContextObj context;
    CGLPixelFormatAttribute attributes[13] = {
        kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute)kCGLOGLPVersion_GL4_Core,
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
    return context;
}

#include <unistd.h>

#define PIXEL_FORMAT (GL_RGB)

typedef struct GLTransitionContext
{
    // const AVClass *class;
    // FFFrameSync fs;
    int hsub, vsub; ///< chroma subsampling values
    int nb_planes;
    char *all_expr;
    // enum BlendMode all_mode;
    double all_opacity;

    int depth;
    // FilterParams params[4];
    int tblend;
    // AVFrame *prev_frame;        /* only used with tblend */

    // input options
    double duration;
    double offset;
    char *source;

    // timestamp of the first frame in the output, in the timebase units
    int64_t first_pts;

    // uniforms
    GLuint from;
    GLuint to;
    GLint progress;
    GLint ratio;
    GLint _fromR;
    GLint _toR;

    // internal state
    GLuint posBuf;
    GLuint program;

    // GLFWwindow    *window;
    CGLContextObj context;

    GLchar *f_shader_source;
} GLTransitionContext;

typedef struct AVFilterContext
{
    GLTransitionContext *priv;
} AVFilterContext;

typedef struct AVFilterLink
{
    int w;
    int h;
    AVFilterContext *dst;
} AVFilterLink;

static void setup_vbo(GLTransitionContext *c)
{
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &c->posBuf);
    glBindBuffer(GL_ARRAY_BUFFER, c->posBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

    GLint loc = glGetAttribLocation(c->program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

static void setup_tex(AVFilterLink *fromLink)
{
    AVFilterContext *ctx = fromLink->dst;
    GLTransitionContext *c = ctx->priv;

    { // from
        glGenTextures(1, &c->from);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, c->from);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fromLink->w, fromLink->h, 0, PIXEL_FORMAT, GL_UNSIGNED_BYTE, NULL);

        glUniform1i(glGetUniformLocation(c->program, "from"), 0);
    }

    { // to
        glGenTextures(1, &c->to);
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, c->to);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fromLink->w, fromLink->h, 0, PIXEL_FORMAT, GL_UNSIGNED_BYTE, NULL);

        glUniform1i(glGetUniformLocation(c->program, "to"), 1);
    }
}

static void setup_uniforms(AVFilterLink *fromLink)
{
    AVFilterContext *ctx = fromLink->dst;
    GLTransitionContext *c = ctx->priv;

    c->progress = glGetUniformLocation(c->program, "progress");
    glUniform1f(c->progress, 0.5f);

    // TODO: this should be output ratio
    c->ratio = glGetUniformLocation(c->program, "ratio");
    glUniform1f(c->ratio, fromLink->w / (float)fromLink->h);

    c->_fromR = glGetUniformLocation(c->program, "_fromR");
    glUniform1f(c->_fromR, fromLink->w / (float)fromLink->h);

    // TODO: initialize this in config_props for "to" input
    c->_toR = glGetUniformLocation(c->program, "_toR");
    glUniform1f(c->_toR, fromLink->w / (float)fromLink->h);
}
//
int main(int argc, char *argv[])
{
    CGLContextObj context = setupContext();
    CGLError errorCode = CGLSetCurrentContext(context);
    GLuint m_frameBufferID, m_renderBufferID, m_depthBufferID;
    glGenFramebuffers(1, &m_frameBufferID);
    glGenRenderbuffers(1, &m_renderBufferID);

    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_renderBufferID);

    //
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glViewport(0, 0, width, height);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    //
    // const GLchar *vs_s = "#version 330\nin vec3 position;\nvoid main(){gl_Position=vec4(position, 1.0);;}";
    // const GLchar *fs_s = "#version 330\nprecision mediump float;out vec4 fragColor;\nvoid main(){fragColor=vec4(1.0,0.0,0.0,1.0);}";
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

    const char *transition_source = f_default_transition_source;

    int len = strlen(f_shader_template) + strlen(transition_source);
    char *f_shader_source = (char *)calloc(len, sizeof(f_shader_source));
    snprintf(f_shader_source, len * sizeof(f_shader_source), f_shader_template, transition_source);
    //
    // glShaderSource(vs, 1, &vs_s, NULL);
    glShaderSource(vs, 1, &v_shader_source, NULL);
    // glShaderSource(fs, 1, &fs_s, 0);
    glShaderSource(fs, 1, &f_shader_source, 0);
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
    // glUseProgram(program);
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

#if 0
#if 1
#if USE_BUFFER
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
#else
    // 无效
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)vertices);
#endif
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
#else
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
    // if (instanced)
    //     glVertexAttribDivisor(loc, 1);
    // glCheckError();
    glEnableVertexAttribArray(loc);

    glDrawArrays(GL_TRIANGLES, 0, 18);
    glFinish();
#endif
#else

    // makeCGLContextCurrent(c->context);

    //   glUseProgram(c->program);
    glUseProgram(program);
    // return 0;
    GLTransitionContext c;
    c.program = program;
    AVFilterContext cc;
    cc.priv = &c;
    AVFilterLink inLink;
    inLink.dst = &cc;
    setup_vbo(&c);
    setup_uniforms(&inLink);
    setup_tex(&inLink);

    // const float ts = ((fs->pts - c->first_pts) / (float)fs->time_base.den) - c->offset;
    //   const float ts = ((fs->pts - c->first_pts) / (float)fs->time_base.den) - c->offset;
    //   const float progress = FFMAX(0.0f, FFMIN(1.0f, ts / c->duration));
    //   av_log(ctx, AV_LOG_ERROR, "transition '%s' %llu %f %f\n", c->source, fs->pts - c->first_pts, ts, progress);
    glUniform1f(c.progress, 0.5);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, c.from);
    char fromFrameData[width * height * 3];
    for(int i=0;i<width * height * 3;i++)fromFrameData[i]=0;
    // glPixelStorei(GL_UNPACK_ROW_LENGTH, fromFrame->linesize[0] / 3);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, PIXEL_FORMAT, GL_UNSIGNED_BYTE, fromFrameData);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, c.to);
    // glPixelStorei(GL_UNPACK_ROW_LENGTH, toFrame->linesize[0] / 3);
    char toFrameData[width * height * 3];
    for(int i=0;i<width * height * 3;i++)toFrameData[i]=255;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, PIXEL_FORMAT, GL_UNSIGNED_BYTE, toFrameData);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    // glPixelStorei(GL_PACK_ROW_LENGTH, outFrame->linesize[0] / 3);
    // glReadPixels(0, 0, outLink->w, outLink->h, PIXEL_FORMAT, GL_UNSIGNED_BYTE, (GLvoid *)outFrame->data[0]);

    // glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    // glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    char img[width * height * 3];
    // glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    // glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, img);
    FILE *ff = fopen("abc.ppm", "w");
    char header[256];
    snprintf(header, 256, "P6 %d %d 255 ", width, height);
    size_t i = fwrite(header, sizeof(char), 16, ff);
    i = fwrite(img, sizeof(char), width * height * 3, ff);
    fclose(ff);
}