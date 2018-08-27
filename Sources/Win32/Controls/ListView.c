#include <windows.h>
#include <CommCtrl.h>
// #pragma comment(lib,"comctl32.lib")
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	wc.lpfnWndProc = (WNDPROC)WndProc;
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



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int cx = rect.right - rect.left;
	int cy = rect.bottom - rect.top;

	switch (message) {
	case WM_CREATE: {
		HWND hButton = CreateWindow("syslistview32", "",
		                            WS_VISIBLE | WS_CHILD | WS_BORDER |
		                            LVS_REPORT | LVS_SHOWSELALWAYS,
		                            10, 20,
		                            cx - 30,
		                            cy - 100,
		                            hwnd, NULL, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
		// 添加数据
		LV_ITEM item;       // 项
		LV_COLUMN colmn;     // 列
		ZeroMemory(&item, sizeof(LV_ITEM));
		ZeroMemory(&colmn, sizeof(LV_COLUMN));

		colmn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM; // 风格
		colmn.cx = 0x28;
		colmn.pszText = "进程名"; // 文字
		colmn.cx = 0x42;         // 后面列
		SendMessage(hButton, LVM_INSERTCOLUMN, 0, (LPARAM)&colmn);
		colmn.pszText = "内存使用";
		SendMessage(hButton, LVM_INSERTCOLUMN, 0, (LPARAM)&colmn);
		colmn.pszText = "ID";
		SendMessage(hButton, LVM_INSERTCOLUMN, 0, (LPARAM)&colmn);

		// 添加一些行项
		item.mask = LVIF_TEXT;       // 文字
		//item.cchTextMax = MAX_PATH;       // 文字长度
		item.iItem = 0;
		item.iSubItem = 0;
		item.pszText = "Notepad";
		SendMessage(hButton, LVM_INSERTITEM, 0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = "3.3M";
		SendMessage(hButton, LVM_SETITEM, 0, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = "213";
		SendMessage(hButton, LVM_SETITEM, 0, (LPARAM)&item);
		//
		item.iItem = 1;
		item.iSubItem = 0;
		item.pszText = "Mspaint";
		SendMessage(hButton, LVM_INSERTITEM, 0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = "10.3M";
		SendMessage(hButton, LVM_SETITEM, 0, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = "433";
		SendMessage(hButton, LVM_SETITEM, 0, (LPARAM)&item);
		//
		item.iItem = 2;
		item.iSubItem = 0;
		item.pszText = "CMD";
		SendMessage(hButton, LVM_INSERTITEM, 0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = "5.3M";
		SendMessage(hButton, LVM_SETITEM, 0, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = "576";
		SendMessage(hButton, LVM_SETITEM, 0, (LPARAM)&item);

	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}