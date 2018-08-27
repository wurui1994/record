/*
* FileName: Image_Linux.c
* Usage:    tcc -lX11 -run Image_Linux.c
*/
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char **argv)
{
	int win_b_color;
	int win_w_color;
	XEvent xev;
	Window window;
	Visual *visual;
	XImage *ximage;
	GC gc;
	
	char*buffer=(char*)malloc(WIDTH*HEIGHT*4*sizeof(char));
	
	Display *display = XOpenDisplay(NULL);
	win_b_color = BlackPixel(display, DefaultScreen(display));
	win_w_color = BlackPixel(display, DefaultScreen(display));
	window = XCreateSimpleWindow(display,DefaultRootWindow(display),0, 0, WIDTH, HEIGHT, 0,win_b_color, win_w_color);
	visual = DefaultVisual(display, 0);
	//XSelectInput(display, window, ExposureMask | KeyPressMask);
	XMapWindow(display, window);
	XFlush(display);
	gc = XCreateGC(display, window, 0, NULL);
	//XEvent event;
	while (1) {
		for (int i = 0; i < WIDTH*HEIGHT*4; i ++)
			buffer[i] = rand()%256;
		ximage=XCreateImage(display, visual, 24,ZPixmap, 0, buffer,WIDTH, HEIGHT, 32, 0);
		XPutImage(display, window,gc, ximage, 0, 0, 0, 0,WIDTH, HEIGHT);
	}
	return 0;
}
