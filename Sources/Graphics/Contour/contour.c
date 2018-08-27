#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#define random (rand()/(RAND_MAX+1.0))
static float xrot = 0.0;
static float yrot = 0.0;
static float zrot = 0.0;
const float d=0.1,dh=0;
//
inline float fun(float x,float y)
{
	//Matlab Peaks Function
	float z=3*(1-x)*(1-x)*exp(-x*x - (y+1)*(y+1))
	        - 10*(x/5 - x*x*x - y*y*y*y*y)*exp(-x*x-y*y)
	        - 1.0/3*exp(-(x+1)*(x+1) - y*y);
	return z/3.0;
}
void Initial()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);//注意:GL_CW与GL_CCW的区别。
	//glClearColor(1.0, 1.0, 1.0, 0.0);
}
inline void line(float x1,float y1,float x2,float y2)
{
	glBegin(GL_LINES);
	//glColor3f(random,random,random);
	glColor3f(0,1,0);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	//glVertex3f(x,z1,y);
	glEnd();
}
void contour(float x,float y,float z1,float z2,float z3,float z4,float h)
{
	float flag1=z1-h,flag2=z2-h,flag3=z3-h,flag4=z4-h;
	if(flag1<0&&flag2<0&&flag3<0&&flag4<0) { //0000
		//none
	} else if(flag1>=0&&flag2<0&&flag3<0&&flag4<0) { //1000
		line(x+d/2,y,x,y+d/2);
	} else if(flag1<0&&flag2<0&&flag3>=0&&flag4<0) { //0010
		line(x,y+d/2,x+d/2,y+d);
	} else if(flag1<0&&flag2<0&&flag3<0&&flag4>=0) { //0001
		line(x+d/2,y+d,x+d,y+d/2);
	} else if( flag1<0&&flag2>=0&&flag3<0&&flag4<0) { //0100
		line(x+d/2,y,x+d,y+d/2);
	} else if( flag1>=0&&flag2<0&&flag3>=0&&flag4<0) { //1010
		line(x+d/2,y,x+d/2,y+d);
	} else if (flag1>=0&&flag2>=0&&flag3<0&&flag4<0) { //1100
		line(x,y+d/2,x+d,y+d/2);
	} else if (flag1>=0&&flag2<0&&flag3<0&&flag4>=0) { //1001
		line(x+d/2,y,x+d,y+d/2);
		line(x,y+d/2,x+d/2,y+d);
	} else if( flag1>=0&&flag2>=0&&flag3>=0&&flag4>=0) { //1111
		//none
	} else if(flag1<0&&flag2>=0&&flag3>=0&&flag4>=0) { //0111
		line(x,y+d/2,x+d/2,y);
	} else if( flag1>=0&&flag2>=0&&flag3<0&&flag4>=0) {//1101
		line(x,y+d/2,x+d/2,y+d);
	} else if( flag1>=0&&flag2>=0&&flag3>=0&&flag4<0) { //1110
		line(x+d/2,y+d,x+d,y+d/2);
	} else if (flag1>=0&&flag2<0&&flag3>=0&&flag4>=0) { //1011
		line(x+d/2,y,x+d,y+d/2);
	} else if( flag1<0&&flag2>=0&&flag3<0&&flag4>=0 ) { //0101
		line(x+d/2,y,x+d/2,y+d);
	} else if (flag1<0&&flag2<0&&flag3>=0&&flag4>=0) { //0011
		line(x,y+d/2,x+d,y+d/2);
	} else if( flag1<0&&flag2>=0&&flag3>=0&&flag4<0) {//0110
		line(x+d/2,y+d,x+d,y+d/2);
		line(x,y+d/2,x+d/2,y);
	}

}
void DrawSurface()
{
	float x,y,z1,z2,z3,z4;

	glColor3f(0,1,1);
	//glEnable(GL_CULL_FACE); // 开启剪裁
	//glCullFace(GL_BACK); // 裁掉背面
	//
	for(float h=-9; h<9; h+=0.5) {
		for(x=-3; x<3; x+=d) {
			for(y=-3; y<3; y+=d) {
				z1=fun(x,y);
				z2=fun(x+d,y);
				z3=fun(x,y+d);
				z4=fun(x+d,y+d);
				contour(x,y,z1,z2,z3,z4,h);
			}
		}
	}
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(15, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glRotatef(zrot, 0, 0, 1);
	DrawSurface();
	//xrot = xrot + 1;
	yrot = yrot + 1;
	//zrot = zrot + 1;
	glutSwapBuffers();
	//glFlush();
}

void reshape(int w, int h)
{
	int factor=3;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-factor, factor, -factor *h/w, factor * h/w, -factor, factor);
	else
		glOrtho(-factor*w/h, factor*w/h, -factor, factor, -factor, factor);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	//glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(350, 120);
	glutInitWindowSize(500, 500);
	glutCreateWindow("");
	Initial();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(display);
	glutMainLoop();
	return 0;
}