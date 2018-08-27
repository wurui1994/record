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
	static POINT ptOld, ptNew;
	static RECT rectMove, rectNew, rectLast;
	
	static bool bIsMove = false;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//SelectObject(hdc, GetStockObject(WHITE_PEN));
		//SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
		SelectObject(ps.hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(0, 0, 255));
		printf("%d %d %d %d\n", rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
		Rectangle(ps.hdc, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
		//Rectangle(ps.hdc, 20, 18, 68, 50);
		/*SetDCBrushColor(ps.hdc, RGB(220, 32, 70));
		Rectangle(ps.hdc, 125, 100, 230, 300);
		SetDCBrushColor(ps.hdc, RGB(30, 235, 12));
		Ellipse(ps.hdc, 270, 80, 390, 223);
		SetDCBrushColor(ps.hdc, RGB(35, 160, 242));
		Chord(ps.hdc, 185, 260, 420, 480, 190, 260, 405, 479);
		SetDCBrushColor(ps.hdc, RGB(211, 254, 41));
		Pie(ps.hdc, 35, 320, 300, 600, 56, 470, 60, 360);*/
		EndPaint(hwnd, &ps);
		return 0;
	case WM_RBUTTONDOWN:
		//绘制第一个矩形
		hdc = GetDC(hwnd);
		SetRect(&rectOld, 10, 10, 110, 70);//保存上次矩形的位置
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
		Rectangle(hdc, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
		//ReleaseDC(hwnd, hdc);
		return 0;
	case WM_LBUTTONDOWN:
		//确定鼠标起始位置
		ptOld.x = LOWORD(lParam);
		ptOld.y = HIWORD(lParam);
		if (PtInRect(&rectOld, ptOld))
		{
			bIsMove = true;
		}
		else
		{
			bIsMove = false;
		}
		return 0;
	case WM_LBUTTONUP:
		//确定鼠标释放位置
		if (bIsMove)
		{
			hdc = GetDC(hwnd);
			bIsMove = false;
			ptNew.x = LOWORD(lParam);
			ptNew.y = HIWORD(lParam);
			rectNew.left = rectOld.left + (ptNew.x - ptOld.x);
			rectNew.top = rectOld.top + (ptNew.y - ptOld.y);
			rectNew.right = rectNew.left + 100;
			rectNew.bottom = rectNew.top + 60;

			CopyRect(&rectOld, &rectNew);
			InvalidateRect(hwnd, NULL, TRUE);
			ReleaseDC(hwnd, hdc);
		}

		return 0;
	case WM_MOUSEMOVE:
		if (bIsMove)
		{
			//鼠标移动画边框
			POINT ptMove;
			ptMove.x = LOWORD(lParam);
			ptMove.y = HIWORD(lParam);
			rectMove.left = rectOld.left + (ptMove.x - ptOld.x);
			rectMove.top = rectOld.top + (ptMove.y - ptOld.y);
			rectMove.right = rectMove.left + 100;
			rectMove.bottom = rectMove.top + 60;

			hdc = GetDC(hwnd);
			//-擦掉上一次的拖动的矩形轨迹
			SelectObject(hdc, GetStockObject(WHITE_PEN));
			SelectObject(hdc, GetStockObject(WHITE_BRUSH));
			Rectangle(hdc, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);

			////实时移动矩形
			SelectObject(hdc,GetStockObject(NULL_PEN));
			SelectObject(hdc,GetStockObject(LTGRAY_BRUSH));
			Rectangle(hdc,rectMove.left,rectMove.top,rectMove.right,rectMove.bottom);
			CopyRect(&rectLast,&rectMove);  

			//使用虚框代替矩形实时移动效果
			//画初始的矩形
			/*SelectObject(hdc, GetStockObject(NULL_PEN));
			SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
			Rectangle(hdc, rectOld.left, rectOld.top, rectOld.right, rectOld.bottom);
			//画本次移动的矩形轨迹
			SelectObject(hdc, GetStockObject(BLACK_PEN));
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, rectMove.left, rectMove.top, rectMove.right, rectMove.bottom);
			CopyRect(&rectLast, &rectMove);*/
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
	HWND hwnd = CreateWindow(ClassName, title1, WS_OVERLAPPEDWINDOW, 0, 0, 440, 440, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

