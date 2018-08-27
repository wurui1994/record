#include <windows.h>
#include <stdio.h>

#pragma comment(lib,"user32")
#pragma comment(lib,"advapi32")

int count = 0;

static int  nFlag = 0;
// 以下代码抄了网上的
BOOL __stdcall EveryWindowProc(HWND hWnd, LPARAM parameter)
{
	// 不可见、不可激活的窗口不作考虑。

	/*if (!IsWindowVisible(hWnd))
	return TRUE;

	if (!IsWindowEnabled(hWnd))
	return TRUE;*/

	// 弹出式窗口，但没有标题的不作考虑。
	/*LONG gwl_style = GetWindowLong(hWnd, GWL_STYLE);
	if ((gwl_style & WS_POPUP) && !(gwl_style & WS_CAPTION))
	return TRUE;*/

	// 父窗口是可见或可激活的窗口不作考虑。
	// /*HWND hParent = (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);
	// if (IsWindowEnabled(hParent))
	// return TRUE;
	// if (IsWindowVisible(hParent))
	// return TRUE;*/

	// Shell_TrayWnd类的窗口（托盘里面的）不作考虑。
	TCHAR szClassName[MAX_PATH];
	GetClassName(hWnd, szClassName, MAX_PATH);
	if(IsWindowVisible(hWnd))printf("%s\n", szClassName);
	if (!wcscmp(szClassName, TEXT("Shell_TrayWnd")))
		return TRUE;


	//if (nFlag == 0)
	//{
	//	// 最小化
	//	CloseWindow(hWnd);
	//}
	//else
	//{
	//	// 激活并恢复原大小及位置
	//	OpenIcon(hWnd);
	//}
	count++;
	return TRUE;
}
int main()
{
	EnumWindows(EveryWindowProc, (LPARAM)0);
	printf("There are %d windows.\n",count);
	return 0;
}


