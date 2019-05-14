// win32.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include <commctrl.h>
#include <commdlg.h>
#define WM_TAB (WM_USER)
#define WM_ESC (WM_USER + 1)
#define WM_ENTER (WM_USER + 2)

//  Global variables
HWND    hwndMain;
WNDPROC lpfnEditWndProc; //  Original wndproc for the combo box
HINSTANCE hInst;
//  Prototypes
LRESULT CALLBACK SubClassProc(HWND, UINT, WPARAM, LPARAM);

/********************************************************

FUNCTION:   ToolbarWindowProc

PURPOSE:    Window procedure for the toolbar window

*********************************************************/

LRESULT CALLBACK ToolbarWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND   hwndEdit1;
	static HWND   hwndEdit2;
	static HWND   hwndCombo1;
	static HWND   hwndCombo2;
	POINT       pt;
	DWORD       dwBaseUnits;
	HWND        hwndCombo;
	DWORD       dwIndex;
	char achTemp[256];       //  Temporary buffer

	switch (msg) {
	case WM_CREATE:
		//  Create two combo box child windows.
		dwBaseUnits = GetDialogBaseUnits();

		hwndCombo1 = CreateWindow(L"COMBOBOX", L"",
		                          CBS_DROPDOWN | WS_CHILD | WS_VISIBLE,
		                          (6 * LOWORD(dwBaseUnits)) / 4,
		                          (2 * HIWORD(dwBaseUnits)) / 8,
		                          (100 * LOWORD(dwBaseUnits)) / 4,
		                          (50 * HIWORD(dwBaseUnits)) / 8,
		                          hwnd, NULL, NULL, NULL);

		hwndCombo2 = CreateWindow(L"COMBOBOX", L"",
		                          CBS_DROPDOWN | WS_CHILD | WS_VISIBLE,
		                          (112 * LOWORD(dwBaseUnits)) / 4,
		                          (2 * HIWORD(dwBaseUnits)) / 8,
		                          (100 * LOWORD(dwBaseUnits)) / 4,
		                          (50 * HIWORD(dwBaseUnits)) / 8,
		                          hwnd, NULL, hInst, NULL);

		//  Get the edit window handle to each combo box.
		pt.x = 1;
		pt.y = 1;
		hwndEdit1 = ChildWindowFromPoint(hwndCombo1, pt);
		hwndEdit2 = ChildWindowFromPoint(hwndCombo2, pt);

		//  Change the window procedure for both edit windows
		//  to the subclass procedure.
		lpfnEditWndProc = (WNDPROC)SetWindowLong(hwndEdit1,
		                  GWL_WNDPROC, (DWORD)SubClassProc);

		SetWindowLong(hwndEdit2, GWL_WNDPROC, (DWORD)SubClassProc);

		break;

	case WM_SETFOCUS:
		SetFocus(hwndCombo1);
		break;

	case WM_TAB:
		if (GetFocus() == hwndEdit1)
			SetFocus(hwndCombo2);
		else
			SetFocus(hwndCombo1);
		break;

	case WM_ESC:
		hwndCombo = GetFocus() == hwndEdit1 ? hwndCombo1 : hwndCombo2;

		// Clear the current selection.
		SendMessage(hwndCombo, CB_SETCURSEL,
		            (WPARAM)(-1), 0);

		//  Set the focus to the main window.
		SetFocus(hwndMain);
		break;

	case WM_ENTER:
		hwndCombo = GetFocus() == hwndEdit1 ? hwndCombo1 : hwndCombo2;
		SetFocus(hwndMain);

		//  If there is no current selection, set one.
		if (SendMessage(hwndCombo, CB_GETCURSEL, 0, 0)
		        == CB_ERR) {
			if (SendMessage(hwndCombo, WM_GETTEXT,
			                sizeof(achTemp), (LPARAM)achTemp) == 0)
				break;      //  Empty selection field
			dwIndex = SendMessage(hwndCombo,
			                      CB_FINDSTRINGEXACT, (WPARAM)(-1),
			                      (LPARAM)achTemp);

			//  Add the string, if necessary, and select it.
			if (dwIndex == CB_ERR)
				dwIndex = SendMessage(hwndCombo, CB_ADDSTRING,
				                      0, (LPARAM)achTemp);
			if (dwIndex != CB_ERR)
				SendMessage(hwndCombo, CB_SETCURSEL,
				            dwIndex, 0);
		}
		break;

		// .
		// .  Process additional messages.
		// .

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


/********************************************************

FUNCTION:   SubClassProc

PURPOSE:    Process TAB and ESCAPE keys, and pass all
other messages to the class window
procedure.

*********************************************************/
LRESULT CALLBACK SubClassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_TAB:
			SendMessage(hwndMain, WM_TAB, 0, 0);
			return 0;
		case VK_ESCAPE:
			SendMessage(hwndMain, WM_ESC, 0, 0);
			return 0;
		case VK_RETURN:
			SendMessage(hwndMain, WM_ENTER, 0, 0);
			return 0;
		}
		break;

	case WM_KEYUP:
	case WM_CHAR:
		switch (wParam) {
		case VK_TAB:
		case VK_ESCAPE:
		case VK_RETURN:
			return 0;
		}
	}

	//  Call the original window procedure for default processing.
	return CallWindowProc(lpfnEditWndProc, hwnd, msg, wParam, lParam);
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
	wc.lpfnWndProc = ToolbarWindowProc;
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



