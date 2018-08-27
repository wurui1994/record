#include <windows.h>
#include <stdio.h>
#define CLSNAME "Clipview"
#define WNDNAME ""
LRESULT CALLBACK WindowProc(HWND hwnd,
                            UINT uMsg,
                            WPARAM wParam,
                            LPARAM lParam
                           );

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR szCmdLine,
                   int iCmdShow)
{
	static TCHAR clsname[] = TEXT(CLSNAME);
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = clsname;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL,
		           TEXT("This program requires Windows NT!"),
		           clsname,
		           MB_ICONERROR);
		return 0;
	}

	HWND hwnd;
	hwnd = CreateWindow(clsname, TEXT(WNDNAME),
	                    WS_OVERLAPPEDWINDOW,
	                    CW_USEDEFAULT, CW_USEDEFAULT,
	                    CW_USEDEFAULT, CW_USEDEFAULT,
	                    NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd,
                            UINT uMsg,
                            WPARAM wParam,
                            LPARAM lParam
                           )
{
	static HWND hwndNextViewer;
	HGLOBAL hGlobal;
	PTSTR pGlobal;

	RECT rect;
	HDC hdc;
	PAINTSTRUCT ps;

	switch (uMsg) {
	case WM_CREATE:
		//改为护眼的颜色
		SetClassLong(hwnd, GCL_HBRBACKGROUND,
		             (LONG)CreateSolidBrush(RGB(202, 234, 207)));

		//清空剪切板
		OpenClipboard(hwnd);
		EmptyClipboard();
		CloseClipboard();

		//让程序成为剪切板的一部分
		hwndNextViewer = SetClipboardViewer(hwnd);
		return 0;

		//更新剪切板
	case WM_DRAWCLIPBOARD:
		//让每个剪切板都更新，重画
		if (hwndNextViewer)
			SendMessage(hwndNextViewer, WM_DRAWCLIPBOARD,
			            wParam, lParam);

		InvalidateRect(hwnd, NULL, true);
		return 0;

		//当剪切板查看器链中有一个退出时，更新链
	case WM_CHANGECBCHAIN:
		if ((HWND)wParam == hwndNextViewer)
			hwndNextViewer = (HWND)lParam;

		//如果下一个不为空，那么将下一个更改
		else if (hwndNextViewer)
			SendMessage(hwndNextViewer, WM_CHANGECBCHAIN,
			            wParam, lParam);
		return 0;

	case WM_DESTROY:
		ChangeClipboardChain(hwnd, hwndNextViewer);
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//设置文本背景颜色
		SetBkColor(hdc, GetSysColor(COLOR_WINDOW));

		GetClientRect(hwnd, &rect);
		OpenClipboard(hwnd);

#ifdef UNICODE
		hGlobal = GetClipboardData(CF_UNICODETEXT);
#else
		hGlobal = GetClipboardData(CF_TEXT);
#endif

		if (hGlobal) {
			pGlobal = (PTSTR)GlobalLock(hGlobal);
			DrawText(hdc, pGlobal, -1, &rect, DT_EXPANDTABS);
			GlobalUnlock(hGlobal);
		} else {
			//如果没有数据，那红色显示
			SetTextColor(hdc, RGB(255, 0, 0));
			DrawText(hdc, TEXT("剪切板没有数据哦！！"),
			         -1, &rect, DT_EXPANDTABS);
		}
		CloseClipboard();
		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}