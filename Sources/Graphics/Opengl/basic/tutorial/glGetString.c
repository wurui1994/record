#include <GL/glut.h>
#include <stdio.h>
/*装驱动前输出:
Microsoft Corporation
GDI Generic
1.1.0
GL_WIN_swap_hint GL_EXT_bgra GL_EXT_paletted_texture
装驱动后输出:
ATI Technologies Inc.
AMD Radeon HD 7520G + 7450M Dual Graphics
4.2.11764 Compatibility Profile Context
GL_AMDX_debug_output GL_AMDX_vertex_shader_tessellator......
*/
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("test");
	const GLubyte *VENDOR, *RENDERER, *VERSION, *EXTENSIONS;
	VENDOR = glGetString(GL_VENDOR);
	puts(VENDOR);
	RENDERER = glGetString(GL_RENDERER);
	puts(RENDERER);
	VERSION = glGetString(GL_VERSION);
	puts(VERSION);
	EXTENSIONS = glGetString(GL_EXTENSIONS);
	puts(EXTENSIONS);
	return 0;
}