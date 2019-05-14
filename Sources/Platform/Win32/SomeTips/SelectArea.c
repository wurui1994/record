#include <windows.h>
#include <stdio.h>
typedef int bool;
#define false 0
#define true (!false)
// - 项目是Unicode字符集
RECT rectOld;

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rc;
	static POINT pt;

	static bool bIsMove = false;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	
	case WM_LBUTTONDOWN:
		//确定鼠标起始位置
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rc);
		FillRect(hdc, &rc, WHITE_BRUSH);
		bIsMove = true;
		return 0;
	case WM_LBUTTONUP:
		//确定鼠标释放位置
		if (bIsMove)
		{
			
			bIsMove = false;
		}

		return 0;
	case WM_MOUSEMOVE:
		if (bIsMove)
		{
			//鼠标移动画边框
			POINT ptMove;
			ptMove.x = LOWORD(lParam);
			ptMove.y = HIWORD(lParam);

			hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rc);
			FillRect(hdc, &rc, WHITE_BRUSH);
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			SelectObject(hdc, pen);
			Rectangle(hdc, pt.x, pt.y, ptMove.x, ptMove.y);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
int main()
{
	rectOld.left = 10, rectOld.top = 10, rectOld.right = 110, rectOld.bottom = 70;
	HINSTANCE hInstance;
	int iShow;
	TCHAR ClassName[] = "MyClass";
	TCHAR title1[] = " ";
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WinProc;
	wndClass.lpszClassName = ClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wndClass)) return 0;
	HWND hwnd = CreateWindow(ClassName, title1, WS_OVERLAPPEDWINDOW, 300, 120, 640, 480, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

