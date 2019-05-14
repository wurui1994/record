#include <windows.h>
int main()
{
	static TCHAR szAppName[] = TEXT(" ");

	MSG          msg;
	WNDCLASS     wndclass;
	int iCmdShow = 1;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = DefWindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = 0;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		//return;
	}


	HWND hwnd = CreateWindow(szAppName, TEXT(""), WS_OVERLAPPEDWINDOW,
	                         300, 120, 640, 480, NULL, NULL, hInstance, NULL);
	HDC hdc = GetDC(hwnd);
	int w = 640, h = 480;
	BYTE *PImage = (BYTE)malloc(w*h * 3);

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	HDC screen_dc = CreateCompatibleDC(hdc);

	//ReleaseDC(hwnd, hdc);

	//BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
	//w * h * 4, 0, 0, 0, 0 }  };
	HBITMAP screen_hb = CreateDIBSection(screen_dc, &bmi, DIB_RGB_COLORS, (void**)&PImage, 0, 0);
	for (int i = 0; i < w*h * 3; i++)PImage[i] = rand() % 256;
	SelectObject(screen_dc, screen_hb);

	//
	while (TRUE) {
		//Sleep(40);//降低CPU占用率
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		} else {

			BitBlt(hdc, 0, 0, w, h, screen_dc, 0, 0, SRCCOPY);
			//SetDIBitsToDevice(hdc, 0, 0, w, h,
			//0, 0, 0, h, PImage, &bmi, DIB_RGB_COLORS);
		}
	}
	return msg.wParam;
}