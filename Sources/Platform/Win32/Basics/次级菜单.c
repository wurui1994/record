#include <Windows.h>
//#include "resource.h"
// #include <WindowsX.h>

LRESULT CALLBACK MyMainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	wc.lpfnWndProc = (WNDPROC)MyMainWindowProc;
	//注册窗口类
	RegisterClass(&wc);
	//创建窗口
	HWND hwnd = CreateWindow("MyApp", "test",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
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
#define IDM_OPT1     301
#define IDM_OPT2     302
LRESULT CALLBACK MyMainWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case 0:
			MessageBox(hwnd, "你选择了Love", "提示", MB_OK);
			break;
		case 1:
			MessageBox(hwnd, "你选择了Happiness", "提示", MB_OK);
			break;
		case 2:
			MessageBox(hwnd, "你选择了Health", "提示", MB_OK);
			break;
		case 3:
			MessageBox(hwnd, "你选择了Money in Level1", "提示", MB_OK);
			break;
		case 4:
			MessageBox(hwnd, "你选择了Wine in Level1", "提示", MB_OK);
			break;
		}
	}
					 return 0;
	case WM_CONTEXTMENU: {
		RECT rect;
		POINT pt;
		// 获取鼠标右击是的坐标
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		//获取客户区域大小
		GetClientRect((HWND)wParam, &rect);
		//把屏幕坐标转为客户区坐标
		ScreenToClient((HWND)wParam, &pt);
		//判断点是否位于客户区域内
		if (PtInRect(&rect, pt)) {
			//加载菜单资源
			HMENU hroot = CreateMenu();
			HMENU pop1 = CreatePopupMenu();
			AppendMenu(hroot, MF_POPUP, (UINT_PTR)pop1, "操作");//ParentMenu
			//次级菜单
			HMENU pop2 = CreatePopupMenu();
			AppendMenu(pop1, MF_POPUP, (UINT_PTR)pop2, "Level1");
			AppendMenu(pop2, MF_STRING, 3, "Money");
			AppendMenu(pop2, MF_STRING, 4, "Wine");
			// 一种方法是使用AppendMenu函数
			AppendMenu(pop1, MF_STRING, 0, "Love");
			//
			AppendMenu(pop1, MF_STRING, 1, "Happiness");
			//AppendMenu(pop1, MF_STRING, 2, "Health");
			// 另一种方法是使用InsertMenuItem函数
			MENUITEMINFO mif;
			mif.cbSize = sizeof(MENUITEMINFO);
			mif.cch = 100;
			mif.dwItemData = 0;
			mif.dwTypeData = "Health";
			mif.fMask = MIIM_ID | MIIM_STRING | MIIM_STATE;
			mif.fState = MFS_ENABLED;
			mif.fType = MIIM_STRING;
			mif.wID = 2;

			InsertMenuItem(pop1, IDM_OPT2, FALSE, &mif);
			if (hroot) {
				// 获取第一个弹出菜单
				HMENU hpop = GetSubMenu(hroot, 0);
				// 把客户区坐标还原为屏幕坐标
				ClientToScreen((HWND)wParam, &pt);
				//显示快捷菜单
				TrackPopupMenu(hpop,
					TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
					pt.x,
					pt.y,
					0,
					(HWND)wParam,
					NULL);
				// 用完后要销毁菜单资源
				DestroyMenu(hroot);
			}
		}
		else {
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
						 break;
	default:
		// 如果不处理消息，交回系统处理
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}