#include <math.h>
#include <windows.h>
#pragma comment(lib, "msimg32")
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, dstmem, srcmem;
	PAINTSTRUCT ps;
	BITMAP bmp;
	static HBITMAP hdstbmp, hsrcbmp;
	static SIZE dstbmp, srcbmp;
	switch (message)
	{
	case WM_CREATE:
		//
		hdstbmp = (HBITMAP)LoadImage(0, "view.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hsrcbmp = (HBITMAP)LoadImage(0, "little.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(hdstbmp, sizeof(BITMAP), &bmp);
		dstbmp.cx = bmp.bmWidth;
		dstbmp.cy = bmp.bmHeight;
		GetObject(hsrcbmp, sizeof(BITMAP), &bmp);
		srcbmp.cx = bmp.bmWidth;
		srcbmp.cy = bmp.bmHeight;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		dstmem = CreateCompatibleDC(hdc);
		srcmem = CreateCompatibleDC(hdc);
		SelectObject(dstmem, hdstbmp);
		SelectObject(srcmem, hsrcbmp);
		for (int i = 0; i < 6; i++)
			TransparentBlt(dstmem, 280 + 200 * sin(i), 200 + 200 * cos(i), srcbmp.cx, srcbmp.cy,
						   srcmem, 0, 0, srcbmp.cx, srcbmp.cy, GetPixel(srcmem, 0, 0));
		BitBlt(hdc, 0, 0, dstbmp.cx, dstbmp.cy, dstmem, 0, 0, SRCCOPY);
		DeleteDC(dstmem);
		DeleteDC(srcmem);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		if (hdstbmp)
			DeleteObject(hdstbmp);
		if (hsrcbmp)
			DeleteObject(hsrcbmp);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
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
	hwnd = CreateWindow(szAppName, TEXT("TransParent Demo"), WS_OVERLAPPEDWINDOW,
						cxScreen / 4, cyScreen / 8, cxScreen / 2, cyScreen * 3 / 4,
						NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}