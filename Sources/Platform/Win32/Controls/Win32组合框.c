#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hThisApp,HINSTANCE hPrevApp,LPSTR cmdLine,
	int nShow)
{
	WNDCLASS wc = {};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "MyApp";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hThisApp;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	//注册窗口类
	RegisterClass(&wc);
	//创建窗口
	HWND hwnd = CreateWindow("MyApp", "test",
		WS_OVERLAPPEDWINDOW,
		350, 120,
		500, 500,
		NULL, NULL, hThisApp, NULL);

	if (hwnd == NULL)
		return 0;
	// 显示窗口
	ShowWindow(hwnd, nShow);
	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndButton;
	HWND combo;
	TCHAR Planets[9][10] =
	{
		TEXT("Mercury"), TEXT("Venus"), TEXT("Terra"), TEXT("Mars"),
		TEXT("Jupiter"), TEXT("Saturn"), TEXT("Uranus"), TEXT("Neptune"),
		TEXT("Pluto")
	};
	int  k = 0;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		combo=CreateWindow(
			"COMBOBOX",  " ",      
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD| WS_OVERLAPPED|WS_VSCROLL| WS_VISIBLE,  // Styles 
			50,20,80, 100, hwnd, (HMENU)0,  (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);
		for (k = 0; k <= 8; k += 1){
			// Add string to combobox.
			SendMessage(combo, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)Planets[k]);
		}
		// Send the CB_SETCURSEL message to display an initial item 
		//  in the selection field  
		SendMessage(combo, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
		break;
	default:
		// 如果不处理消息，交回系统处理
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}