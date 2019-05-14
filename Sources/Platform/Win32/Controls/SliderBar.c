#include <windows.h>
#include <CommCtrl.h>
// #pragma comment(lib,"comctl32.lib")
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	wc.lpfnWndProc = (WNDPROC)WndProc;
	//注册窗口类
	RegisterClass(&wc);
	//创建窗口
	HWND hwnd =
	    CreateWindow("MyApp", "test",WS_OVERLAPPEDWINDOW,350, 120,
	                 500, 500,NULL, NULL, hThisApp, NULL);

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



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int cx = rect.right - rect.left;
	int cy = rect.bottom - rect.top;

	switch (message) {
	case WM_CREATE: {
		HWND hButton =
		    CreateWindow(TRACKBAR_CLASS, "",WS_VISIBLE | WS_CHILD
		                 //| TBS_AUTOTICKS | TBS_HORZ | TBS_BOTH | WS_TABSTOP
		                 ,10, 160,450,50,hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}