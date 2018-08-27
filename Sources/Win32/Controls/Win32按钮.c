#include <Windows.h>

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
	HWND hwndButton;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		CreateWindow(
			"BUTTON",  "PUSH",      
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			50,20, 80, 50, hwnd, NULL,  (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);   
		CreateWindow(
			"BUTTON", "CHECK",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD| BS_AUTOCHECKBOX,  // Styles 
			150, 20, 80, 50, hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		CreateWindow(
			"BUTTON", "RADIO",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,  // Styles 
			250, 20, 80, 50, hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		hwndButton=CreateWindow(
			"BUTTON", "GROUP",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_GROUPBOX|BS_CENTER,  // Styles 
			30, 100, 200, 200, hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		CreateWindow(
			"BUTTON", "SUB1",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			50, 40, 100, 50, hwndButton, NULL, (HINSTANCE)GetWindowLong(hwndButton, GWL_HINSTANCE), NULL);
		CreateWindow(
			"BUTTON", "3STATE",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTO3STATE,  // Styles 
			50, 120, 100, 50, hwndButton, NULL, (HINSTANCE)GetWindowLong(hwndButton, GWL_HINSTANCE), NULL);
		break;
	default:
		// 如果不处理消息，交回系统处理
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}