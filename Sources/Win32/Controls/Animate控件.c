#include <windows.h>
#include <CommCtrl.h>
#include <stdio.h>
// #pragma comment(lib,"comctl32.lib")
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	HWND hbar;
	switch (message) {
		/*case WM_CREATE:
		CreateAnimationCtrl(hwnd, 0);
		break;*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
HWND CreateAnimationCtrl(HWND hwndDlg, int nIDCtl, char* filename)
{

	HWND hwndAnim = NULL;
	HINSTANCE hinst = (HINSTANCE)GetWindowLong(hwndDlg, GWL_HINSTANCE);
	// Create the animation control.
	// IDC_ANIMATE - identifier of the animation control. 
	// hwndDlg - handle to the dialog box.
	RECT rc;
	hwndAnim = Animate_Create(hwndDlg, 0,
		WS_BORDER | WS_CHILD, hinst);

	// Get the screen coordinates of the specified control button.
	// nIDCtl - identifier of the control below which the animation control is to be positioned.
	GetWindowRect(GetDlgItem(hwndDlg, nIDCtl), &rc);

	// Convert the coordinates of the lower-left corner to 
	// client coordinates.
	POINT pt;
	pt.x = rc.left;
	pt.y = rc.bottom;
	ScreenToClient(hwndDlg, &pt);

	// Position the animation control below the Stop button.
	// CX_FRAME, CY_FRAME - width and height of the frames in the AVI clip.      
	SetWindowPos(hwndAnim, 0, pt.x, pt.y + 20,
		200, 200,
		SWP_NOZORDER | SWP_DRAWFRAME);

	// Open the AVI clip, and show the animation control.
	Animate_Open(hwndAnim, filename);
	Animate_Play(hwndAnim, 0, -1, -1);
	ShowWindow(hwndAnim, SW_SHOW);

	return hwndAnim;
}
int  main(int argc,char* argv[])
{
	HINSTANCE hThisApp;
	WNDCLASS wc = {};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "MyApp";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC)WndProc;
	//注册窗口类
	RegisterClass(&wc);
	//创建窗口
	HWND hwnd = CreateWindow("MyApp", "test",
		WS_OVERLAPPEDWINDOW,
		350, 120,
		500, 500,
		NULL, NULL, 0, NULL);
	CreateAnimationCtrl(hwnd, 0, argv[1]);
	if (hwnd == NULL)
		return 0;
	// 显示窗口
	ShowWindow(hwnd, SW_SHOW);
	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}




