#include <commctrl.h>

void CreateSimpleButton(HWND hwnd)
{
	HWND hwndButton =
	    CreateWindow(
	        "BUTTON",  // Predefined class; Unicode assumed
	        "OK",      // Button text
	        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
	        10,         // x position
	        10,         // y position
	        100,        // Button width
	        100,        // Button height
	        hwnd,     // Parent window
	        NULL,       // No menu.
	        (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
	        NULL);

}