#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);            //声明窗口过程函数

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("FlashWindow");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	//窗口类成员属性
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.hInstance = hInstance;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszMenuName = NULL;

	//注册窗口类
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("错误, 窗口注册失败!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return 0;
	}

	//创建窗口
	hwnd = CreateWindow(szAppName, TEXT("Flash Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	//显示窗口
	ShowWindow(hwnd, SW_MINIMIZE);
	UpdateWindow(hwnd);

	//获取、翻译、分发消息
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int inc = 0;

	switch (message)
	{
	case WM_CREATE:
		//MoveWindow(hwnd,0,100,500,500,0);
		SetTimer(hwnd, 1, 10, 0);
	
		break;
	case WM_TIMER:    //处理WM_PAINT消息
	{
		FLASHWINFO finfo;
		finfo.cbSize = sizeof(FLASHWINFO);
		finfo.hwnd = hwnd;
		finfo.uCount = 10;
		finfo.dwTimeout = 400;
		finfo.dwFlags = FLASHW_ALL; //Flash window and tray icon
		FlashWindowEx(&finfo);
		KillTimer(hwnd,1);
	}
		break;
	case WM_DESTROY:    //处理WM_DESTROY消息
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}