#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hThisApp,HINSTANCE hPrevApp,LPSTR cmdLine,
	int nShow)
{
	WNDCLASS wc = {};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "MyApp";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hThisApp;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	//注册窗口类
	RegisterClass(&wc);
	//创建窗口
	HWND hwnd = CreateWindow("MyApp", "test",
		WS_OVERLAPPEDWINDOW,
		350, 120,
		500, 500,
		NULL, NULL, hThisApp, NULL);

	if (hwnd == NULL)
		return 0;
	// 显示窗口
	ShowWindow(hwnd, nShow);
	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hListBox;
	HFONT hfont;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		hListBox = CreateWindow("LISTBOX"," ",
			WS_CHILD | WS_VSCROLL | WS_TABSTOP | WS_VISIBLE|LBS_STANDARD,
			230, 20, 60, 100,hwnd, (HMENU)0,(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);
		//ShowWindow(hListBox, SW_SHOW);
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"你好");
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"我好");
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"他好");
		hfont = CreateFont(20, 0, 0, 0, 0, FALSE, FALSE, FALSE, 1, 0, 0, 0, 0, "微软雅黑");
		SendMessage(hListBox, WM_SETFONT, (WPARAM)hfont, (LPARAM)0);
		break;
	default:
		// 如果不处理消息，交回系统处理
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}