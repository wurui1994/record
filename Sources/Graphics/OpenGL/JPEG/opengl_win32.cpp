#define FAST_IS_JPEG
#include <jpeglib.h>
#include <jerror.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
vector<string> vec;
int num = 0;

//================================
GLuint LoadJPEG(const char *FileName)
//================================
{
	unsigned long x, y;
	unsigned int texture_id;
	unsigned long data_size; // length of the file
	int channels;			 //  3 =>RGB   4 =>RGBA
	unsigned int type;
	unsigned char *rowptr[1];			// pointer to an array
	unsigned char *jdata;				// data for the image
	struct jpeg_decompress_struct info; //for our jpeg info
	struct jpeg_error_mgr err;			//the error handler

	FILE *file = fopen(FileName, "rb"); //open the file

	info.err = jpeg_std_error(&err);
	jpeg_create_decompress(&info); //fills info structure

	//if the jpeg file doesn't load
	if (!file)
	{
		fprintf(stderr, "Error reading JPEG file %s!", FileName);
		return 0;
	}

	jpeg_stdio_src(&info, file);
	jpeg_read_header(&info, TRUE); // read jpeg file header
	info.do_fancy_upsampling = FALSE;
	jpeg_start_decompress(&info); // decompress the file

	//set width and height
	x = info.output_width;
	y = info.output_height;
	channels = info.num_components;
	type = GL_RGB;
	if (channels == 4)
		type = GL_RGBA;

	data_size = x * y * 3;

	//--------------------------------------------
	// read scanlines one at a time & put bytes
	//    in jdata[] array. Assumes an RGB image
	//--------------------------------------------
	jdata = (unsigned char *)malloc(data_size);
	while (info.output_scanline < info.output_height)
	{ // loop
		// Enable jpeg_read_scanlines() to fill our jdata array
		rowptr[0] = (unsigned char *)jdata + // secret to method
					3 * info.output_width * (info.output_height - info.output_scanline);

		jpeg_read_scanlines(&info, rowptr, 1);
	}
	//---------------------------------------------------

	jpeg_finish_decompress(&info); //finish decompressing

	//----- create OpenGL tex map (omit if not needed) --------
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, x, y, GL_RGB, GL_UNSIGNED_BYTE, jdata);

	fclose(file); //close the file
	free(jdata);

	return texture_id; // for OpenGL tex maps
}

void subimage(string &s)
{
	const GLuint texGround = LoadJPEG(s.c_str());
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	glDeleteTextures(1, &texGround);
}
void initiate()
{
	//
	ifstream ifs("test.txt");
	string temp;
	int tempr, tempt;
	while (!ifs.eof())
	{
		getline(ifs, temp);
		if (temp.length() > 4)
			vec.push_back(temp);
		//cout<<temp<<endl;
	}
	ifs.close();
	//cout<<vec.size()<<endl;
}

//#include <GL/glaux.h>		// Header File For The Glaux Library

HDC hDC = NULL;		 // Private GDI Device Context
HGLRC hRC = NULL;	// Permanent Rendering Context
HWND hWnd = NULL;	// Holds Our Window Handle
HINSTANCE hInstance; // Holds The Instance Of The Application

bool keys[256];			// Array Used For The Keyboard Routine
bool active = TRUE;		// Window Active Flag Set To TRUE By Default
bool fullscreen = TRUE; // Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) // Resize And Initialize The GL Window
{
	if (height == 0)
	{				// Prevent A Divide By Zero By
		height = 1; // Making Height Equal One
	}

	glViewport(0, 0, width, height); // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity();			 // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity();			// Reset The Modelview Matrix
}

int InitGL(GLvoid) // All Setup For OpenGL Goes Here
{
	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_TEXTURE_2D);
	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE; // Initialization Went OK
}

int DrawGLScene(GLvoid) // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	if (num == vec.size())
		return 0;
	subimage(vec[num]);
	num++;
	return TRUE; // Everything Went OK
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_PAINT:
		//if(num==vec.size())num-=vec.size();
		DrawGLScene();	// Draw The Scene
		SwapBuffers(hDC); // Swap Buffers (Double Buffering)
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
GLvoid KillGLWindow(GLvoid) // Properly Kill The Window
{
	if (fullscreen)
	{									// Are We In Fullscreen Mode?
		ChangeDisplaySettings(NULL, 0); // If So Switch Back To The Desktop
		ShowCursor(TRUE);				// Show Mouse Pointer
	}

	if (hRC)
	{ // Do We Have A Rendering Context?
		if (!wglMakeCurrent(NULL, NULL))
		{ // Are We Able To Release The DC And RC Contexts?
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))
		{ // Are We Able To Delete The RC?
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL; // Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))
	{ // Are We Able To Release The DC
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL; // Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))
	{ // Are We Able To Destroy The Window?
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL; // Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))
	{ // Are We Able To Unregister Class
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL; // Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char *title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;				  // Holds The Results After Searching For A Match
	WNDCLASS wc;					  // Windows Class Structure
	DWORD dwExStyle;				  // Window Extended Style
	DWORD dwStyle;					  // Window Style
	RECT WindowRect;				  // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;		  // Set Left Value To 0
	WindowRect.right = (long)width;   // Set Right Value To Requested Width
	WindowRect.top = (long)0;		  // Set Top Value To 0
	WindowRect.bottom = (long)height; // Set Bottom Value To Requested Height

	fullscreen = fullscreenflag; // Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);			   // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = DefWindowProc;				   // WndProc Handles Messages
	wc.cbClsExtra = 0;							   // No Extra Window Data
	wc.cbWndExtra = 0;							   // No Extra Window Data
	wc.hInstance = hInstance;					   // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);		   // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	  // Load The Arrow Pointer
	wc.hbrBackground = NULL;					   // No Background Required For GL
	wc.lpszMenuName = NULL;						   // We Don't Want A Menu
	wc.lpszClassName = "OpenGL";				   // Set The Class Name

	if (!RegisterClass(&wc))
	{ // Attempt To Register The Window Class
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (fullscreen)
	{															// Attempt Fullscreen Mode?
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;					// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;					// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE; // Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE; // Return FALSE
			}
		}
	}

	if (fullscreen)
	{								 // Are We Still In Fullscreen Mode?
		dwExStyle = WS_EX_APPWINDOW; // Window Extended Style
		dwStyle = WS_POPUP;			 // Windows Style
		ShowCursor(FALSE);			 // Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;					// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle); // Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,			  // Extended Style For The Window
								"OpenGL",			  // Class Name
								title,				  // Window Title
								dwStyle |			  // Defined Window Style
									WS_CLIPSIBLINGS | // Required Window Style
									WS_CLIPCHILDREN,  // Required Window Style
								350, 120,			  // Window Position
								500,				  // Calculate Window Width
								500,				  // Calculate Window Height
								NULL,				  // No Parent Window
								NULL,				  // No Menu
								hInstance,			  // Instance
								NULL)))
	{					// Dont Pass Anything To WM_CREATE
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	static PIXELFORMATDESCRIPTOR pfd = {
		// pfd Tells Windows How We Want Things To Be
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1,							   // Version Number
		PFD_DRAW_TO_WINDOW |		   // Format Must Support Window
			PFD_SUPPORT_OPENGL |	   // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,		   // Must Support Double Buffering
		PFD_TYPE_RGBA,				   // Request An RGBA Format
		bits,						   // Select Our Color Depth
		0, 0, 0, 0, 0, 0,			   // Color Bits Ignored
		0,							   // No Alpha Buffer
		0,							   // Shift Bit Ignored
		0,							   // No Accumulation Buffer
		0, 0, 0, 0,					   // Accumulation Bits Ignored
		16,							   // 16Bit Z-Buffer (Depth Buffer)
		0,							   // No Stencil Buffer
		0,							   // No Auxiliary Buffer
		PFD_MAIN_PLANE,				   // Main Drawing Layer
		0,							   // Reserved
		0, 0, 0						   // Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))
	{					// Did We Get A Device Context?
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{					// Did Windows Find A Matching Pixel Format?
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{					// Are We Able To Set The Pixel Format?
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))
	{					// Are We Able To Get A Rendering Context?
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))
	{					// Try To Activate The Rendering Context
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);	// Show The Window
	SetForegroundWindow(hWnd);	// Slightly Higher Priority
	SetFocus(hWnd);				  // Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height); // Set Up Our Perspective GL Screen

	if (!InitGL())
	{					// Initialize Our Newly Created GL Window
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	return TRUE; // Success
}

int WINAPI WinMain(HINSTANCE hInstance,		// Instance
				   HINSTANCE hPrevInstance, // Previous Instance
				   LPSTR lpCmdLine,			// Command Line Parameters
				   int nCmdShow)			// Window Show State
{
	MSG msg;		   // Windows Message Structure
	BOOL done = FALSE; // Bool Variable To Exit Loop
	initiate();

	fullscreen = FALSE; // Windowed Mode
	//}

	// Create Our OpenGL Window
	if (!CreateGLWindow("", 640, 480, 16, fullscreen))
	{
		return 0; // Quit If Window Was Not Created
	}

	while (1)
	{
		DrawGLScene();	// Draw The Scene
		SwapBuffers(hDC); // Swap Buffers (Double
		if (num == vec.size())
			return 0;
	}

	// Shutdown
	KillGLWindow();		 // Kill The Window
	return (msg.wParam); // Exit The Program
}
