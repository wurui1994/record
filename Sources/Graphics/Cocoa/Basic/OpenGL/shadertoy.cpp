/**
 * Shadertoy ffmpeg filter
 * @Date    20210530
 * @Author  Canta <canta@canta.com.ar>
 *
 * @Comments: Check previous projects from other authors:
 *            - https://github.com/transitive-bullshit/ffmpeg-gl-transition
 *            - https://github.com/nervous-systems/ffmpeg-opengl
 *            - https://github.com/numberwolf/FFmpeg-Plus-OpenGL
 *
 */

// clang++ -std=c++11 shadertoy.cpp -framework OpenGL

#include <stdio.h>
#include <stdlib.h>

#include <OpenGL/OpenGL.h>
#include <Opengl/glext.h>

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
#include <Opengl/glu.h>

// #include "libavutil/opt.h"
// #include "internal.h"
// #include "video.h"

#ifdef __APPLE__
#define __gl_h_
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

#define width 400
#define height 400
//
#define USE_BUFFER 1

// #define TS2T(ts, tb) ((ts) == AV_NOPTS_VALUE ? NAN : (double)(ts)*av_q2d(tb))

static const float position[12] = {
    -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f};

static const GLchar *v_shader_source = "\
#version 400 \n\
in vec2 position;\n\
void main()\n\
{\n\
  gl_Position = vec4(position, 0.0, 1.0);\n\
}\n";

static const GLchar f_shader_source_template[] = "\
#version 400 \n\
#ifdef GL_OES_standard_derivatives\n\
#extension GL_OES_standard_derivatives : enable\n\
#endif\n\
\n\
float round( float x ) { return floor(x+0.5); }\n\
vec2 round(vec2 x) { return floor(x + 0.5); }\n\
vec3 round(vec3 x) { return floor(x + 0.5); }\n\
vec4 round(vec4 x) { return floor(x + 0.5); }\n\
float trunc( float x, float n ) { return floor(x*n)/n; }\n\
mat3 transpose(mat3 m) { return mat3(m[0].x, m[1].x, m[2].x, m[0].y, m[1].y, m[2].y, m[0].z, m[1].z, m[2].z); }\n\
float determinant( in mat2 m ) { return m[0][0]*m[1][1] - m[0][1]*m[1][0]; }\n\
float determinantMat4( mat4 m ) { float b00 = m[0][0] * m[1][1] - m[0][1] * m[1][0], b01 = m[0][0] * m[1][2] - m[0][2] * m[1][0], b02 = m[0][0] * m[1][3] - m[0][3] * m[1][0], b03 = m[0][1] * m[1][2] - m[0][2] * m[1][1], b04 = m[0][1] * m[1][3] - m[0][3] * m[1][1], b05 = m[0][2] * m[1][3] - m[0][3] * m[1][2], b06 = m[2][0] * m[3][1] - m[2][1] * m[3][0], b07 = m[2][0] * m[3][2] - m[2][2] * m[3][0], b08 = m[2][0] * m[3][3] - m[2][3] * m[3][0], b09 = m[2][1] * m[3][2] - m[2][2] * m[3][1], b10 = m[2][1] * m[3][3] - m[2][3] * m[3][1], b11 = m[2][2] * m[3][3] - m[2][3] * m[3][2];  return b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;}\n\
mat2 inverse(mat2 m) { float det = determinant(m); return mat2(m[1][1], -m[0][1], -m[1][0], m[0][0]) / det; }\n\
mat4 inverseMat4(mat4 m ) { float inv0 = m[1].y*m[2].z*m[3].w - m[1].y*m[2].w*m[3].z - m[2].y*m[1].z*m[3].w + m[2].y*m[1].w*m[3].z + m[3].y*m[1].z*m[2].w - m[3].y*m[1].w*m[2].z; float inv4 = -m[1].x*m[2].z*m[3].w + m[1].x*m[2].w*m[3].z + m[2].x*m[1].z*m[3].w - m[2].x*m[1].w*m[3].z - m[3].x*m[1].z*m[2].w + m[3].x*m[1].w*m[2].z; float inv8 = m[1].x*m[2].y*m[3].w - m[1].x*m[2].w*m[3].y - m[2].x  * m[1].y * m[3].w + m[2].x  * m[1].w * m[3].y + m[3].x * m[1].y * m[2].w - m[3].x * m[1].w * m[2].y; float inv12 = -m[1].x  * m[2].y * m[3].z + m[1].x  * m[2].z * m[3].y +m[2].x  * m[1].y * m[3].z - m[2].x  * m[1].z * m[3].y - m[3].x * m[1].y * m[2].z + m[3].x * m[1].z * m[2].y; float inv1 = -m[0].y*m[2].z * m[3].w + m[0].y*m[2].w * m[3].z + m[2].y  * m[0].z * m[3].w - m[2].y  * m[0].w * m[3].z - m[3].y * m[0].z * m[2].w + m[3].y * m[0].w * m[2].z; float inv5 = m[0].x  * m[2].z * m[3].w - m[0].x  * m[2].w * m[3].z - m[2].x  * m[0].z * m[3].w + m[2].x  * m[0].w * m[3].z + m[3].x * m[0].z * m[2].w - m[3].x * m[0].w * m[2].z; float inv9 = -m[0].x  * m[2].y * m[3].w +  m[0].x  * m[2].w * m[3].y + m[2].x  * m[0].y * m[3].w - m[2].x  * m[0].w * m[3].y - m[3].x * m[0].y * m[2].w + m[3].x * m[0].w * m[2].y; float inv13 = m[0].x  * m[2].y * m[3].z - m[0].x  * m[2].z * m[3].y - m[2].x  * m[0].y * m[3].z + m[2].x  * m[0].z * m[3].y + m[3].x * m[0].y * m[2].z - m[3].x * m[0].z * m[2].y; float inv2 = m[0].y  * m[1].z * m[3].w - m[0].y  * m[1].w * m[3].z - m[1].y  * m[0].z * m[3].w + m[1].y  * m[0].w * m[3].z + m[3].y * m[0].z * m[1].w - m[3].y * m[0].w * m[1].z; float inv6 = -m[0].x  * m[1].z * m[3].w + m[0].x  * m[1].w * m[3].z + m[1].x  * m[0].z * m[3].w - m[1].x  * m[0].w * m[3].z - m[3].x * m[0].z * m[1].w + m[3].x * m[0].w * m[1].z; float inv10 = m[0].x  * m[1].y * m[3].w - m[0].x  * m[1].w * m[3].y - m[1].x  * m[0].y * m[3].w + m[1].x  * m[0].w * m[3].y + m[3].x * m[0].y * m[1].w - m[3].x * m[0].w * m[1].y; float inv14 = -m[0].x  * m[1].y * m[3].z + m[0].x  * m[1].z * m[3].y + m[1].x  * m[0].y * m[3].z - m[1].x  * m[0].z * m[3].y - m[3].x * m[0].y * m[1].z + m[3].x * m[0].z * m[1].y; float inv3 = -m[0].y * m[1].z * m[2].w + m[0].y * m[1].w * m[2].z + m[1].y * m[0].z * m[2].w - m[1].y * m[0].w * m[2].z - m[2].y * m[0].z * m[1].w + m[2].y * m[0].w * m[1].z; float inv7 = m[0].x * m[1].z * m[2].w - m[0].x * m[1].w * m[2].z - m[1].x * m[0].z * m[2].w + m[1].x * m[0].w * m[2].z + m[2].x * m[0].z * m[1].w - m[2].x * m[0].w * m[1].z; float inv11 = -m[0].x * m[1].y * m[2].w + m[0].x * m[1].w * m[2].y + m[1].x * m[0].y * m[2].w - m[1].x * m[0].w * m[2].y - m[2].x * m[0].y * m[1].w + m[2].x * m[0].w * m[1].y; float inv15 = m[0].x * m[1].y * m[2].z - m[0].x * m[1].z * m[2].y - m[1].x * m[0].y * m[2].z + m[1].x * m[0].z * m[2].y + m[2].x * m[0].y * m[1].z - m[2].x * m[0].z * m[1].y; float det = m[0].x * inv0 + m[0].y * inv4 + m[0].z * inv8 + m[0].w * inv12; det = 1.0 / det; return det*mat4( inv0, inv1, inv2, inv3,inv4, inv5, inv6, inv7,inv8, inv9, inv10, inv11,inv12, inv13, inv14, inv15);}\n\
float sinh(float x)  { return (exp(x)-exp(-x))/2.; }\n\
float cosh(float x)  { return (exp(x)+exp(-x))/2.; }\n\
float tanh(float x)  { return sinh(x)/cosh(x); }\n\
float coth(float x)  { return cosh(x)/sinh(x); }\n\
float sech(float x)  { return 1./cosh(x); }\n\
float csch(float x)  { return 1./sinh(x); }\n\
float asinh(float x) { return    log(x+sqrt(x*x+1.)); }\n\
float acosh(float x) { return    log(x+sqrt(x*x-1.)); }\n\
float atanh(float x) { return .5*log((1.+x)/(1.-x)); }\n\
float acoth(float x) { return .5*log((x+1.)/(x-1.)); }\n\
float asech(float x) { return    log((1.+sqrt(1.-x*x))/x); }\n\
float acsch(float x) { return    log((1.+sqrt(1.+x*x))/x); }\n\
\n\
uniform vec3      iResolution;           // viewport resolution (in pixels)\n\
uniform float     iTime;                 // shader playback time (in seconds)\n\
uniform float     iTimeDelta;            // render time (in seconds)\n\
uniform int       iFrame;                // shader playback frame\n\
uniform float     iChannelTime[4];       // channel playback time (in seconds)\n\
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)\n\
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click\n\
uniform sampler2D iChannel0;             // input channel. XX = 2D/Cube\n\
uniform sampler2D iChannel1;\n\
uniform sampler2D iChannel2;\n\
uniform sampler2D iChannel3;\n\
uniform vec4      iDate;                 // (year, month, day, time in seconds)\n\
uniform float     iSampleRate;           // sound sample rate (i.e., 44100)\n\
uniform vec2      iOffset;               // pixel offset for tiled rendering\n\
uniform vec2      iFrameRate;            // input frame rate\n\
\n\
\n\
// Fragment shader goes here\n\
\n\
%s\n\
\n\
// end fragment shader \n\
out vec4 outColor;\n\
void main()\n\
{\n\
    outColor.b=1;\n\
    mainImage(outColor, gl_FragCoord.xy + iOffset);\n\
}\n";

static GLchar fragment_shader[65535];
// static char * fragment_shader;

#define PIXEL_FORMAT GL_RGB

typedef struct
{
    // const AVClass *class;
    double start_play_time;
    // AVRational      timebase;
    char *shadertoy_file;
    char *vertex_file;
    int64_t render_start_time;
    int64_t render_start_time_tb;
    double render_start_time_ft;
    int64_t duration;
    int64_t duration_tb;
    double duration_ft;

    GLchar *shadertoy_file_data;
    GLchar *vertex_file_data;
    GLint play_time;
    GLuint program;
    GLuint frame_tex;
    // GLFWwindow      *window;
    CGLContextObj context;
    GLuint pos_buf;

    // Shadertoy vars
    GLuint resolution;
    GLfloat timedelta;
    GLuint frame;
    GLuint channeltime;
    GLuint channelresolution;
    GLuint mouse;
    GLuint channel0;
    GLuint channel1;
    GLuint channel2;
    GLuint channel3;
    GLuint date;
    GLuint samplerate;
    GLuint offset;
    int res[3];
} shadertoyContext;

typedef struct
{
    int w;
    int h;
} AVFilterLink;

#define OFFSET(x) offsetof(shadertoyContext, x)
#define FLAGS AV_OPT_FLAG_FILTERING_PARAM | AV_OPT_FLAG_VIDEO_PARAM
// static const AVOption shadertoy_options[] = {
//     {"shadertoy_file",  "Required. "
//                         "Path to file containing a shadertoy's code.",
//                         OFFSET(shadertoy_file),
//                         AV_OPT_TYPE_STRING,
//                         {.str = NULL},
//                         CHAR_MIN,
//                         CHAR_MAX,
//                         FLAGS},
//     {"vertex_file", "Optional. "
//                     "Path to file with custom vertex shader for the shadertoy. "
//                     "By default this filter uses shadertoy webside default vertex shader.",
//                     OFFSET(vertex_file),
//                     AV_OPT_TYPE_STRING,
//                     {.str = NULL},
//                     CHAR_MIN,
//                     CHAR_MAX,
//                     FLAGS},
//     {"start", "Optional. "
//               "Starting time for the shader render, in seconds.",
//               OFFSET(render_start_time),
//               AV_OPT_TYPE_DURATION,
//               {.i64 = 0.},
//               0,
//               INT64_MAX,
//               FLAGS},
//     {"duration",  "Optional. Render duration.",
//                   OFFSET(duration),
//                   AV_OPT_TYPE_DURATION,
//                   {.i64 = 0.},
//                   0,
//                   INT64_MAX,
//                   FLAGS},
//     {NULL}
// };

// AVFILTER_DEFINE_CLASS(shadertoy);

void glfw_onError(int error, const char *description);

static GLuint build_shader(shadertoyContext *ctx, const GLchar *shader_source, GLenum type)
{
    GLuint shader;
    int InfoLogLength;
    char *ShaderErrorMessage;
    GLint status;
    GLuint ret;

    printf("vf_shadertoy: build_shader (%s)\n",
           type == GL_VERTEX_SHADER ? "vertex" : "fragment");

    shader = glCreateShader(type);
    if (!shader || !glIsShader(shader))
    {
        printf("vf_shadertoy: build_shader glCreateShader glIsShader FAILED!\n");
        return 0;
    }
    else
    {
        printf("vf_shadertoy: shader created.\n");
    }

    glShaderSource(shader, 1, &shader_source, 0);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // error message
    InfoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        ShaderErrorMessage = (char *)malloc(InfoLogLength);

        glGetShaderInfoLog(shader, InfoLogLength, NULL, ShaderErrorMessage);
        printf("vf_shadertoy: build_shader ERROR: %s\n", ShaderErrorMessage);
    }

    ret = status == GL_TRUE ? shader : 0;
    return ret;
}

static void vbo_setup(shadertoyContext *gs)
{
    GLint loc;

    unsigned int VAO;
	glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &gs->pos_buf);
    glBindBuffer(GL_ARRAY_BUFFER, gs->pos_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

    loc = glGetAttribLocation(gs->program, "position");
    printf("loc %d\n", loc);
    glEnableVertexAttribArray(loc);
    glCheckError();
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

static void tex_setup(AVFilterLink *inlink, shadertoyContext *gs)
{
    // AVFilterContext   *ctx = inlink->dst;
    // shadertoyContext  *gs = ctx->priv;

    glGenTextures(1, &gs->frame_tex);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, gs->frame_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inlink->w, inlink->h, 0, PIXEL_FORMAT, GL_UNSIGNED_BYTE, NULL);

    glUniform1i(glGetUniformLocation(gs->program, "iChannel0"), 0);
}

static int build_program(shadertoyContext *ctx)
{
    GLuint v_shader, f_shader;
    shadertoyContext *gs;
    FILE *f;
    unsigned long fsize;
    const char *gl_shadertoy_file_dst;
    const char *gl_vertex_file_dst;
    GLint status;

    printf("start vf_shadertoy build_program action\n");
    // gs = ctx->priv;
    gs = ctx;
    gs->shadertoy_file_data = NULL;
    gs->vertex_file_data = NULL;

    /*
     * fragments shader
     */
    if (gs->shadertoy_file)
    {
        printf("vf_shadertoy: build_program shader params: %s\n", gs->shadertoy_file);
        f = fopen(gs->shadertoy_file, "rb");
        if (!f)
        {
            printf("vf_shadertoy: build_program shader: invalid shader source file \"%s\"\n", gs->shadertoy_file);
            return -1;
        }

        // get file size
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        gs->shadertoy_file_data = (GLchar *)malloc(fsize + 1);
        status = fread(gs->shadertoy_file_data, fsize, 1, f);
        fclose(f);
        gs->shadertoy_file_data[fsize] = 0;

        // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: loaded shader: %s\n", gs->shadertoy_file_data);
        // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: will blend shader into: %s\n", f_shader_source_template);

        // mixing input shader with shadertoy base code
        printf("vf_shadertoy: sizes: \nfragment_shader: %ld\nloaded shader: %ld\ntemplate: %ld",
               sizeof(fragment_shader),
               sizeof(gs->shadertoy_file_data),
               sizeof(f_shader_source_template));

        snprintf(
            fragment_shader,
            sizeof(f_shader_source_template) + fsize + 1,
            f_shader_source_template,
            gs->shadertoy_file_data);

        // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: blended shader: %s\n", fragment_shader);
    }
    else
    {
        printf("vf_shadertoy: no shadertoy code. Impossible to continue.\n");
        return -1;
    }

    /*
     * vertex shader
     */
    if (gs->vertex_file)
    {
        printf("vf_shadertoy: build_program vertex params: %s\n", gs->vertex_file);
        f = fopen(gs->vertex_file, "rb");
        if (!f)
        {
            printf(
                "vf_shadertoy: build_program shader: invalid shader source file \"%s\"\n", gs->vertex_file);
            return -1;
        }

        // get file size
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        gs->vertex_file_data = (GLchar *)malloc(fsize + 1);
        status = fread(gs->vertex_file_data, fsize, 1, f);
        fclose(f);
        gs->vertex_file_data[fsize] = 0;
    }
    else
    {
        printf("vf_shadertoy: no custom vertex, using default.\n");
    }

    gl_shadertoy_file_dst = fragment_shader;
    gl_vertex_file_dst = gs->vertex_file_data ? gs->vertex_file_data : v_shader_source;

    printf(
        "vf_shadertoy: build_program build_shader debug shaders ===================================>\n");
    /*av_log(ctx, AV_LOG_DEBUG,
        "vf_shadertoy: build_program build_shader fragment shaders:\n%s\n", gl_shadertoy_file_dst);*/
    printf(
        "vf_shadertoy: build_program build_shader vertex shader:\n%s\n", gl_vertex_file_dst);

    if (gs->render_start_time > 0)
    {
        // gs->duration_tb = TS2T(gs->duration, gs->timebase);
        //  gs->render_start_time_tb = av_rescale_q(gs->render_start_time, AV_TIME_BASE_Q, gs->timebase);
        //  gs->render_start_time_ft = TS2T(gs->render_start_time_tb, gs->timebase);
        gs->duration += gs->render_start_time;
    }
    else
    {
        gs->duration_tb = 0;
        gs->duration_ft = 0;
    }
    printf("vf_shadertoy: render_start_time:%ld, render_start_time_tb:%ld, render_start_time_ft:%f\n",
           gs->render_start_time, gs->render_start_time_tb, gs->render_start_time_ft);

    if (gs->duration > 0)
    {
        // gs->duration_tb = TS2T(gs->duration, gs->timebase);
        //  gs->duration_tb = av_rescale_q(gs->duration, AV_TIME_BASE_Q, gs->timebase);
        //  gs->duration_ft = TS2T(gs->duration_tb, gs->timebase);
    }
    else
    {
        gs->duration_tb = -1;
        gs->duration_ft = -1;
    }
    printf("vf_shadertoy: duration:%ld, duration_tb:%ld, duration_ft:%f\n",
           gs->duration, gs->duration_tb, gs->duration_ft);

    if (!((v_shader = build_shader(ctx, gl_vertex_file_dst, GL_VERTEX_SHADER)) &&
          (f_shader = build_shader(ctx, gl_shadertoy_file_dst, GL_FRAGMENT_SHADER))))
    {
        printf("vf_shadertoy: build_program failed!\n");
        return -1;
    }

    // render shader object
    printf("vf_shadertoy: build_program create program\n");
    gs->program = glCreateProgram();
    glAttachShader(gs->program, v_shader);
    glAttachShader(gs->program, f_shader);
    glLinkProgram(gs->program);

    glGetProgramiv(gs->program, GL_LINK_STATUS, &status);
    if (gs->shadertoy_file_data)
    {
        free(gs->shadertoy_file_data);
        gs->shadertoy_file_data = NULL;
    }
    if (gs->vertex_file_data)
    {
        free(gs->vertex_file_data);
        gs->vertex_file_data = NULL;
    }

    printf("vf_shadertoy: build_program finished\n");
    return status == GL_TRUE ? 0 : -1;
}

static void uni_setup(AVFilterLink *inLink, shadertoyContext *ctx)
{
    // AVFilterContext   *ctx = inLink->dst;
    // shadertoyContext  *c = ctx->priv;

    shadertoyContext *c = ctx;
    // Shadertoy vars
    /*
    uniform vec3      iResolution;           // viewport resolution (in pixels)
    uniform float     iTime;                 // shader playback time (in seconds)
    uniform float     iTimeDelta;            // render time (in seconds)
    uniform int       iFrame;                // shader playback frame
    uniform float     iChannelTime[4];       // channel playback time (in seconds)
    uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
    uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
    uniform sampler2D iChannel0;             // input channel. XX = 2D/Cube
    uniform sampler2D iChannel1;
    uniform sampler2D iChannel2;
    uniform sampler2D iChannel3;
    uniform vec4      iDate;                 // (year, month, day, time in seconds)
    uniform float     iSampleRate;           // sound sample rate (i.e., 44100)
    uniform vec2      iOffset;               // pixel offset for tiled rendering
    */
    c->play_time = glGetUniformLocation(c->program, "iTime");
    glUniform1f(c->play_time, 0.0f);

    c->resolution = glGetUniformLocation(c->program, "iResolution");
    glUniform3f(c->resolution, inLink->w, inLink->h, 1.0);

    c->timedelta = glGetUniformLocation(c->program, "iTimeDelta");
    c->frame = glGetUniformLocation(c->program, "iFrame");
    c->channeltime = glGetUniformLocation(c->program, "iChannelTime");
    c->channelresolution = glGetUniformLocation(c->program, "iChannelResolution");
    c->mouse = glGetUniformLocation(c->program, "iMouse");

    c->channel0 = glGetUniformLocation(c->program, "iChannel0");
    c->channel1 = glGetUniformLocation(c->program, "iChannel1");
    c->channel2 = glGetUniformLocation(c->program, "iChannel2");
    c->channel3 = glGetUniformLocation(c->program, "iChannel3");

    c->date = glGetUniformLocation(c->program, "iDate");
    c->samplerate = glGetUniformLocation(c->program, "iSampleRate");
    c->offset = glGetUniformLocation(c->program, "iOffset");
}

// static int init(AVFilterContext *ctx) {

//   //glfwSetErrorCallback(glfw_onError);

//   return 0;
// }

void glfw_onError(int error, const char *description)
{
    printf(
        "vf_shadertoy: glfw error #%d:\n%s\n",
        error,
        description);
}

void test_opengl()
{
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
}

static CGLContextObj setupContext()
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
    //
    return context;
}

static void setOpenGLBuffer(int w, int h)
{
    // errorCode = CGLSetCurrentContext(context);
    //--------
    GLuint fbo, rbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

static CGLError makeCGLContextCurrent(CGLContextObj context)
{
    CGLError errorCode;
    errorCode = CGLSetCurrentContext(context);
    return errorCode;
}

static int config_props(AVFilterLink *inlink, shadertoyContext *gs)
{
    int ret;
    //   AVFilterContext  *ctx = inlink->dst;
    //   shadertoyContext *gs  = ctx->priv;
    gs->start_play_time = -1;

    // cgl_test();
    // exit(0);
    // if(glewInit() != GLEW_OK) {
    //     av_log(ctx, AV_LOG_ERROR, "vf_shadertoy: GLEW initialization failed\n");
    //     return -1;
    // }

    //   if (glfwInit() != GLFW_TRUE) {
    //     av_log(ctx, AV_LOG_ERROR, "vf_shadertoy: GLFW initialization failed\n");
    //     return -1;
    //   }

    // glfwWindowHint(GLFW_VISIBLE, 0);
    // gs->window = glfwCreateWindow(inlink->w, inlink->h, "", NULL, NULL);
    gs->context = setupContext();

    // glfwMakeContextCurrent(gs->window);
    makeCGLContextCurrent(gs->context);

    setOpenGLBuffer(inlink->w, inlink->h);

    glClearColor(1.0, 1.0, 0.0, 1.0);
    glViewport(0, 0, inlink->w, inlink->h);
    //   gs->timebase = inlink->time_base;

    if ((ret = build_program(gs)) < 0)
    {
        return ret;
    }

    glUseProgram(gs->program);
    glCheckError();
    vbo_setup(gs);
    // glCheckError();
    tex_setup(inlink, gs);
    // glCheckError();
    uni_setup(inlink, gs);
    // glCheckError();
    return 0;
}

int filter_frame(AVFilterLink *inlink, shadertoyContext *gs)
{
    // AVFrame *out;
    // int copy_props_ret;
    // AVFilterContext *ctx    = inlink->dst;
    // AVFilterLink *outlink   = ctx->outputs[0];
    // shadertoyContext *gs = ctx->priv;

    double play_time; // = TS2T(in->pts, gs->timebase);
    // check start time
    // if (gs->start_play_time < 0) {
    //     gs->start_play_time = play_time;
    // }
    // play_time -= gs->start_play_time;
    // printf(
    //        "vf_shadertoy: filter_frame get pts:%ld ,time->%f, duration:%f\n",
    //        in->pts,
    //        play_time,
    //        gs->duration_ft);

    // out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    // if (!out) {
    //     av_frame_free(&in);
    //     return AVERROR(ENOMEM);
    // }

    // copy_props_ret = av_frame_copy_props(out, in);
    // if (copy_props_ret < 0) {
    //     av_frame_free(&out);
    //     return -1;
    // }
    // glfwMakeContextCurrent(gs->window);
    makeCGLContextCurrent(gs->context);
    setOpenGLBuffer(inlink->w, inlink->h);
    glUseProgram(gs->program);

    printf("%d %d\n", inlink->w, inlink->h);

    if ( // check if render
        (gs->duration_ft < 0 || (gs->duration_ft > 0 && play_time <= gs->duration_ft)) && play_time >= gs->render_start_time_ft)
    {
        printf("sssss");
        // av_log(ctx, AV_LOG_DEBUG,
        //    "vf_shadertoy: filter_frame gl render pts:%ld ,time->%f, duration:%f\n", in->pts, play_time, gs->duration_ft);

        glUniform1f(gs->play_time, play_time);
        // glUniform1f(gs->frame, in->pts); //in->display_picture_number);
        glUniform1f(gs->frame, 1);
        char in_data[400 * 400 * 3];
        for (int i = 0; i < 400 * 400 * 3; i++)
            in_data[i] = 255;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, inlink->w, inlink->h, 0, PIXEL_FORMAT, GL_UNSIGNED_BYTE, in_data);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        char out_data[400 * 400 * 3];
        glReadPixels(0, 0, inlink->w, inlink->h, PIXEL_FORMAT, GL_UNSIGNED_BYTE, (GLvoid *)out_data);
        FILE *ff = fopen("test.ppm", "w");
        char *header = "P6 100 100 255 ";
        size_t i = fwrite(header, sizeof(char), 16, ff);
        i = fwrite(out_data, sizeof(char), 400 * 400 * 3, ff);
        fclose(ff);
    }
    else
    {
        printf("cccc");
        // av_log(ctx, AV_LOG_DEBUG,
        //    "vf_shadertoy: filter_frame copy pts:%ld ,time->%f, duration:%f\n", in->pts, play_time, gs->duration_ft);
        // av_frame_copy(out, in);
    }
    // test_opengl();
    // char data[400 * 400 * 3];
    // glReadPixels(0, 0, 400, 400, GL_BGR, GL_UNSIGNED_BYTE, data);
    // FILE* ff = fopen("test.ppm", "w");
    // char* header = "P6 100 100 255 ";
    // size_t i = fwrite(header, sizeof(char), 16, ff);
    // i = fwrite(data, sizeof(char), 400 * 400 * 3, ff);
    // fclose(ff);

    // av_frame_free(&in);
    // return ff_filter_frame(outlink, out);
}

static void uninit(shadertoyContext *ctx)
{
    shadertoyContext *c = ctx;

    // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: starting uninit action\n");
    // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: check window\n");
    if (c->context)
    { // @new
        // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: gldelete operations\n");
        glDeleteTextures(1, &c->frame_tex);
        glDeleteBuffers(1, &c->pos_buf);
        glDeleteProgram(c->program);
        // glfwDestroyWindow(c->window);
        CGLDestroyContext(c->context);
    }
    else
    {
        // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: no window, don't need gldelete operations\n");
    }

    // av_log(ctx, AV_LOG_DEBUG, "vf_shadertoy: finished\n");
}

// static const enum AVPixelFormat pixel_fmts[] = {AV_PIX_FMT_RGB24, AV_PIX_FMT_NONE};

// static const AVFilterPad shadertoy_inputs[] = {
//     {
//         .name = "default",
//         .type = AVMEDIA_TYPE_VIDEO,
//         .config_props = config_props,
//         .filter_frame = filter_frame
//     }
// };

// static const AVFilterPad shadertoy_outputs[] = {
//   {
//     .name = "default",
//     .type = AVMEDIA_TYPE_VIDEO
//   }
// };

// AVFilter ff_vf_shadertoy = {
//     .name          = "shadertoy",
//     .description   = NULL_IF_CONFIG_SMALL("Applies a shadertoy using ffmpeg filter"),
//     .priv_size     = sizeof(shadertoyContext),
//     .init          = init,
//     .uninit        = uninit,
//     .priv_class    = &shadertoy_class,
//     .flags         = AVFILTER_FLAG_SUPPORT_TIMELINE_GENERIC,
//     FILTER_PIXFMTS_ARRAY(pixel_fmts),
//     FILTER_INPUTS(shadertoy_inputs),
//     FILTER_OUTPUTS(shadertoy_outputs),
// };

#include <unistd.h>
//
int test()
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

int main()
{
    AVFilterLink inlink = {400, 400};
    shadertoyContext gs;
    gs.shadertoy_file = "test.glsl";
    config_props(&inlink, &gs);
    filter_frame(&inlink, &gs);
    // test();
    return 0;
}