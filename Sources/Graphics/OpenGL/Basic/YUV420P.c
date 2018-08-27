/*
 * Very simple example of how to perform YUV->RGB (YCrCb->RGB)
 * conversion with an OpenGL fragmen shader. The data (not included)
 * is presumed to be three files with Y, U and V samples for a 720x576
 * pixels large image.
 *
 * Note! The example uses NVidia extensions for rectangular textures
 * to make it simpler to read (non-normalised coordinates).
 * Rewriting it without the extensions is quite simple, but left as an
 * exercise to the reader. (The trick is that the shader must know the
 * image dimensions instead)
 *
 * The program also does not check to see if the shader extensions are
 * available - this is after all just a simple example.
 *
 * This code is released under a BSD style license. Do what you want, but
 * do not blame me.
 *
 * Peter Bengtsson, Dec 2004.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL/SDL.h>

int Quit=0;

static int B_WIDTH=640;
static int B_HEIGHT=480;

int main(int cnt,char *arg[])
{
SDL_Surface *Win=NULL;
GLubyte *Ytex,*Utex,*Vtex;
SDL_Event evt;
int i;
GLhandleARB FSHandle,PHandle;
char *s;
FILE *fp;

char *FProgram=
  "uniform sampler2DRect Ytex;\n"
  "uniform sampler2DRect Utex,Vtex;\n"
  "void main(void) {\n"
  "  float nx,ny,r,g,b,y,u,v;\n"
  "  vec4 txl,ux,vx;"
  "  nx=gl_TexCoord[0].x;\n"
  "  ny=576.0-gl_TexCoord[0].y;\n"
  "  y=texture2DRect(Ytex,vec2(nx,ny)).r;\n"
  "  u=texture2DRect(Utex,vec2(nx/2.0,ny/2.0)).r;\n"
  "  v=texture2DRect(Vtex,vec2(nx/2.0,ny/2.0)).r;\n"

  "  y=1.1643*(y-0.0625);\n"
  "  u=u-0.5;\n"
  "  v=v-0.5;\n"

  "  r=y+1.5958*v;\n"
  "  g=y-0.39173*u-0.81290*v;\n"
  "  b=y+2.017*u;\n"

  "  gl_FragColor=vec4(r,g,b,1.0);\n"
  "}\n";


if(!SDL_Init(SDL_INIT_VIDEO)) {

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  Win=SDL_SetVideoMode(B_WIDTH,B_HEIGHT,32,SDL_HWSURFACE|SDL_ANYFORMAT|SDL_OPENGL);

  if(Win) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,B_WIDTH,0,B_HEIGHT,-1,1);
    glViewport(0,0,B_WIDTH,B_HEIGHT);
    glClearColor(0,0,0,0);
    glColor3f(1.0,0.84,0.0);
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

    /* Set up program objects. */
    PHandle=glCreateProgramObjectARB();
    FSHandle=glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

    /* Compile the shader. */
    glShaderSourceARB(FSHandle,1,&FProgram,NULL);
    glCompileShaderARB(FSHandle);

    /* Print the compilation log. */
    glGetObjectParameterivARB(FSHandle,GL_OBJECT_COMPILE_STATUS_ARB,&i);
    s=malloc(32768);
    glGetInfoLogARB(FSHandle,32768,NULL,s);
    printf("Compile Log: %s\n", s);
    free(s);

    /* Create a complete program object. */
    glAttachObjectARB(PHandle,FSHandle);
    glLinkProgramARB(PHandle);

    /* And print the link log. */
    s=malloc(32768);
    glGetInfoLogARB(PHandle,32768,NULL,s);
    printf("Link Log: %s\n", s);
    free(s);

    /* Finally, use the program. */
    glUseProgramObjectARB(PHandle);

    /* Load the textures. */
    Ytex=malloc(414720);
    Utex=malloc(103680);
    Vtex=malloc(103680);

    fp=fopen("Image.Y","rb");
    fread(Ytex,414720,1,fp);
    fclose(fp);
    fp=fopen("Image.U","rb");
    fread(Utex,103680,1,fp);
    fclose(fp);
    fp=fopen("Image.V","rb");
    fread(Vtex,103680,1,fp);
    fclose(fp);

    /* This might not be required, but should not hurt. */
    glEnable(GL_TEXTURE_2D);

    /* Select texture unit 1 as the active unit and bind the U texture. */
    glActiveTexture(GL_TEXTURE1);
    i=glGetUniformLocationARB(PHandle,"Utex");
    glUniform1iARB(i,1);  /* Bind Utex to texture unit 1 */
    glBindTexture(GL_TEXTURE_RECTANGLE_NV,1);

    glTexParameteri(GL_TEXTURE_RECTANGLE_NV,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_RECTANGLE_NV,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glTexImage2D(GL_TEXTURE_RECTANGLE_NV,0,GL_LUMINANCE,376,288,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,Utex);

    /* Select texture unit 2 as the active unit and bind the V texture. */
    glActiveTexture(GL_TEXTURE2);
    i=glGetUniformLocationARB(PHandle,"Vtex");
    glBindTexture(GL_TEXTURE_RECTANGLE_NV,2);
    glUniform1iARB(i,2);  /* Bind Vtext to texture unit 2 */

    glTexParameteri(GL_TEXTURE_RECTANGLE_NV,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_RECTANGLE_NV,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glTexImage2D(GL_TEXTURE_RECTANGLE_NV,0,GL_LUMINANCE,376,288,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,Vtex);

    /* Select texture unit 0 as the active unit and bind the Y texture. */
    glActiveTexture(GL_TEXTURE0);
    i=glGetUniformLocationARB(PHandle,"Ytex");
    glUniform1iARB(i,0);  /* Bind Ytex to texture unit 0 */
    glBindTexture(GL_TEXTURE_RECTANGLE_NV,3);

    glTexParameteri(GL_TEXTURE_RECTANGLE_NV,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_RECTANGLE_NV,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glTexImage2D(GL_TEXTURE_RECTANGLE_NV,0,GL_LUMINANCE,752,576,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,Ytex);

    /* Simple loop, just draws the image and waits for quit. */
    while(!Quit) {
      if(SDL_PollEvent(&evt)) {
        switch(evt.type) {
        case  SDL_KEYDOWN:
        case  SDL_QUIT:
          Quit=1;
        break;
        }
      }
    
      glClear(GL_COLOR_BUFFER_BIT);

      /* Draw image (again and again). */

      glBegin(GL_QUADS);
        glTexCoord2i(0,0);
        glVertex2i(0,0);
        glTexCoord2i(720,0);
        glVertex2i(B_WIDTH,0);
        glTexCoord2i(720,576);
        glVertex2i(B_WIDTH,B_HEIGHT);
        glTexCoord2i(0,576);
        glVertex2i(0,B_HEIGHT);
      glEnd();

      /* Flip buffers. */

      glFlush();
      SDL_GL_SwapBuffers();

      sleep(1);
    } /* while(!Quit) */

    /* Clean up before exit. */

    glUseProgramObjectARB(0);
    glDeleteObjectARB(sprog);

    free(Ytex);
    free(Utex);
    free(Vtex);

  } else {
    fprintf(stderr,"Unable to create primary surface. \"%s\".\n",SDL_GetError());
  }
  SDL_Quit();
} else {
  fprintf(stderr,"Initialisation failed. \"%s\".\n",SDL_GetError());
}

return(0);
}


