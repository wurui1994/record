#include <windows.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	default:
		return DefWindowProc(hwnd, msg, w, l);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lp, int n)
{
	MSG msg;
	WNDCLASS wc = { sizeof(WNDCLASS) };
	char c[] = "theclass", t[] = "test";
	wc.lpszClassName = c;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(c, t, WS_SYSMENU, 350, 120, 500, 500,0, 0, hInst, 0);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}