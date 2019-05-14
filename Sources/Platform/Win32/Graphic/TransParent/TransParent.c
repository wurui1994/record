//TransParent.c
#include <windows.h>
//#include<wingdi.h>

#pragma comment(lib, "msimg32")
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   PSTR szCmdLine,
				   int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("TransParent");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	int cxScreen, cyScreen;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
				   szAppName, MB_ICONERROR);
		return 0;
	}
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	hwnd = CreateWindow(szAppName,
						TEXT("TransParent Demo"),
						WS_OVERLAPPEDWINDOW,
						cxScreen / 4,
						cyScreen / 8,
						cxScreen / 2,
						cyScreen * 3 / 4,
						NULL,
						NULL,
						hInstance,
						NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBmp, hBmp1;
	static SIZE sBmp, sBmp1;
	static BYTE bTrans = 128, bTrans1;
	static BLENDFUNCTION bf, bf1;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
		//
		hBmp = (HBITMAP)LoadImage(((LPCREATESTRUCT)lParam)->hInstance,
								  "view.bmp",
								  IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,".\view.bmp");
		{
			BITMAP bmp;
			GetObject(hBmp, sizeof(BITMAP), &bmp);
			sBmp.cx = bmp.bmWidth;
			sBmp.cy = bmp.bmHeight;
		}
		//
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = bTrans;
		bf.AlphaFormat = 0;
		hBmp1 = (HBITMAP)LoadImage(((LPCREATESTRUCT)lParam)->hInstance,
								   "back.bmp",
								   IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,".\view.bmp");
		{
			BITMAP bmp1;
			GetObject(hBmp1, sizeof(BITMAP), &bmp1);
			sBmp1.cx = bmp1.bmWidth;
			sBmp1.cy = bmp1.bmHeight;
		}
		//
		bf1.BlendOp = AC_SRC_OVER;
		bf1.BlendFlags = 0;
		bf1.SourceConstantAlpha = 255 * 0.5;
		bf1.AlphaFormat = 0;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBmp);
		AlphaBlend(hdc, 0, 0, sBmp.cx, sBmp.cy, hdcMem, 0, 0, sBmp.cx, sBmp.cy, bf);
		SelectObject(hdcMem, hBmp1);
		AlphaBlend(hdc, 0, 0, sBmp.cx, sBmp.cy, hdcMem, 0, 0, sBmp1.cx, sBmp1.cy, bf1); //
		DeleteDC(hdcMem);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_MOUSEWHEEL:
		//
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0 && bTrans <= 234)
		{
			bTrans += 20;
			bf.SourceConstantAlpha = bTrans;
			InvalidateRect(hwnd, NULL, FALSE); //
		}
		if (GET_WHEEL_DELTA_WPARAM(wParam) < 0 && bTrans >= 20)
		{
			bTrans -= 20;
			bf.SourceConstantAlpha = bTrans;
			InvalidateRect(hwnd, NULL, TRUE); //
		}
		return 0;
	case WM_DESTROY:
		if (hBmp)
			DeleteObject(hBmp);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}