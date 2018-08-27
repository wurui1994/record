#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define Random (rand()%256)

// int  g_nX, g_nY;
// HBRUSH g_hBrush;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	static HFONT hFont;
	int h=24;
	//LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) {
	case WM_CREATE:
		hFont=CreateFont(h,0,0,0,0,0,0,0,1,0,0,0,0,"Consolas");
		// g_hBrush = CreateSolidBrush( RGB(0,0,0) );
		// g_nX = g_nY = 100;
		break;



	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		RECT rcText;
		// rcText.left = 0;
		// rcText.top = 0;
		// rcText.right = 500;
		// rcText.bottom = 100;

		//创建黑色的画刷,
		//HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
		//SetBkMode(hdc,TRANSPARENT);
		//用黑色的画刷填充四边形的颜色.
		//FillRect(hdc,&rcText,hbrush);
		SelectObject(hdc,hFont);
		
		char string[]="Hello World!\n你好,世界!Hello World!\n你好,世界!Hello World!\n你好,世界!Hello World!\n你好,世界!";
		for(int i=0;i<640/h;i++){
			SetTextColor(hdc,RGB(Random,Random,Random));
			TextOut(hdc,0,i*h,string,strlen(string));
		}
		EndPaint(hWnd, &ps);
		break;



	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Typer") ;
	HWND         hwnd ;
	MSG          msg ;
	WNDCLASS     wndclass ;

	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass)) {
		MessageBox (NULL, TEXT ("This program requires Windows NT!"),
		            szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hwnd = CreateWindow (szAppName, TEXT ("Typing Program"),
	                     WS_OVERLAPPEDWINDOW,
	                     CW_USEDEFAULT, CW_USEDEFAULT,
	                     CW_USEDEFAULT, CW_USEDEFAULT,
	                     NULL, NULL, hInstance, NULL) ;

	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	return msg.wParam ;
}
