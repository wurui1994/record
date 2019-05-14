// SetWindowLong(hwnd,GWL_EXSTYLE,GetWindowLong(hwnd,GWL_EXSTYLE)|WS_EX_LAYERED);   
// SetLayeredWindowAttributes(hwnd,0,255*0.8,LWA_ALPHA);//0.8的透明度

#include <windows.h>
LRESULT WINAPI WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	hDC= GetWindowDC(hWnd);
	static HRGN hRgn;
	hRgn= CreateRectRgn(120, 70, 280, 230);
	switch(uMsg) {
	case WM_ERASEBKGND: {
		DefWindowProc(hWnd, uMsg, wParam, lParam);
		FillRgn(hDC, hRgn, CreateSolidBrush(RGB(255, 165, 0))); // Orange
		SelectObject(hDC, hRgn);
		return 0;
	}
	case WM_CREATE: {
		HRGN hRgn1 = CreateEllipticRgn(0, 0, 400, 300);
		HRGN hRgn2 = CreateEllipticRgn(150, 100, 250, 200);
		CombineRgn(hRgn1, hRgn1, hRgn2, RGN_XOR);
		SetWindowRgn(hWnd, hRgn1, TRUE);
		DeleteObject(hRgn1);
		DeleteObject(hRgn2);
		break;
	}
	case WM_LBUTTONDOWN: {
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		break;
	}
	case WM_DESTROY: {
		DeleteObject(hRgn);
		ReleaseDC(hWnd, hDC);
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, LPSTR name, BOOL cmd)
{
	WNDCLASS wc = {0};
	wc.lpszClassName = "wndclass";
	wc.hbrBackground = CreateSolidBrush(RGB(255, 99, 71));
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = WinProc;
	RegisterClass(&wc);
	HWND hWnd = CreateWindowEx(WS_EX_LAYERED, "wndclass", "Window", WS_POPUP|WS_VISIBLE, 480, 120, 400, 300, 0, 0, hInstance, 0);
	if (hWnd == NULL)
		return 1;
	SetLayeredWindowAttributes(hWnd, 0, 178, LWA_ALPHA); // Tomato
	MSG msg = {0};
	while (GetMessage(&msg, 0, 0, 0)) 
	{
		DispatchMessage(&msg);
	}
	return 0;
}