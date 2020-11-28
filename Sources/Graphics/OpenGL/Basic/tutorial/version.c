#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//显示模式初始化
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	//定义窗口大小
	glutInitWindowSize(300, 300);
	//定义窗口位置
	glutInitWindowPosition(100, 100);
	//创建窗口
	glutCreateWindow("OpenGL Version");
	const GLubyte *name = glGetString(GL_VENDOR);			//返回负责当前OpenGL实现厂商的名字
	const GLubyte *biaoshifu = glGetString(GL_RENDERER);	//返回一个渲染器标识符，通常是个硬件平台
	const GLubyte *OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号
	const GLubyte *gluVersion = gluGetString(GLU_VERSION);  //返回当前GLU工具库版本
	printf("OpenGL实现厂商的名字：%s\n", name);
	printf("渲染器标识符：%s\n", biaoshifu);
	printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
	printf("GLU工具库版本：%s\n", gluVersion);

	return 0;
}