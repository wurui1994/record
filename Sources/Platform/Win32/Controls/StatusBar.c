// win32.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include <commctrl.h>
#include <commdlg.h>
// #pragma comment(lib,"comctl32.lib")


// Description:
//   Creates a status bar and divides it into the specified number of parts.
// Parameters:
//   hwndParent - parent window for the status bar.
//   idStatus - child window identifier of the status bar.
//   hinst - handle to the application instance.
//   cParts - number of parts into which to divide the status bar.
// Returns:
//   The handle to the status bar.
//
HWND DoCreateStatusBar(HWND hwndParent, int idStatus, HINSTANCE
                       hinst, int cParts)
{
	HWND hwndStatus;
	RECT rcClient;
	HLOCAL hloc;
	PINT paParts;
	int i, nWidth;

	// Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Create the status bar.
	hwndStatus = CreateWindowEx(
	                 0,                       // no extended styles
	                 STATUSCLASSNAME,         // name of status bar class
	                 (PCTSTR)NULL,           // no text when first created
	                 SBARS_SIZEGRIP |         // includes a sizing grip
	                 WS_CHILD | WS_VISIBLE,   // creates a visible child window
	                 0, 0, 0, 0,              // ignores size and position
	                 hwndParent,              // handle to parent window
	                 (HMENU)idStatus,       // child window identifier
	                 hinst,                   // handle to application instance
	                 NULL);                   // no window creation data

	// Get the coordinates of the parent window's client area.
	GetClientRect(hwndParent, &rcClient);

	// Allocate an array for holding the right edge coordinates.
	hloc = LocalAlloc(LHND, sizeof(int) * cParts);
	paParts = (PINT)LocalLock(hloc);

	// Calculate the right edge coordinate for each part, and
	// copy the coordinates to the array.
	nWidth = rcClient.right / cParts;
	int rightEdge = nWidth;
	for (i = 0; i < cParts; i++) {
		paParts[i] = rightEdge;
		rightEdge += nWidth;
	}

	// Tell the status bar to create the window parts.
	SendMessage(hwndStatus, SB_SETPARTS, (WPARAM)cParts, (LPARAM)
	            paParts);
	SendMessage(hwndStatus, WM_SETTEXT,(WPARAM)cParts, (LPARAM)
	            L"Hello World");

	// Free the array, and return.
	LocalUnlock(hloc);
	LocalFree(hloc);
	return hwndStatus;
}

HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParem)
{

	switch (msg) {
	case WM_CREATE:
		DoCreateStatusBar(hwnd,1,hinst,3);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParem);
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	WNDCLASS wc = { sizeof(WNDCLASS) };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszClassName = L" ";
	wc.lpfnWndProc = WndProc;
	//
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(L" ", L"", WS_OVERLAPPEDWINDOW, 350, 120, 500, 500, 0, 0, hInstance, 0);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}



