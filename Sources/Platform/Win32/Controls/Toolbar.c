#include <windows.h>
#include <commctrl.h>
#define ID_TOOLBAR 1
HINSTANCE hInst;
//新建工具栏
HWND CreateSimpleToolbar(HWND hwndParent)
{
	HWND hwndToolbar;
	//工具栏上按钮的数目
	const int BUTTONNUMS = 2;
	//按钮
	TBBUTTON tbb[2];
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[1].iBitmap = STD_REDOW;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	//位图,commctl中的标准位图
	TBADDBITMAP tbBitmap1;
	tbBitmap1.hInst = HINST_COMMCTRL;
	tbBitmap1.nID = IDB_STD_SMALL_COLOR;

	RECT windowRect;
	GetWindowRect(hwndParent,&windowRect);
	hwndToolbar = CreateWindowEx(0L,TOOLBARCLASSNAME,NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,0,0,0,0,
	                             hwndParent,(HMENU)ID_TOOLBAR,hInst,NULL);
	//将位图添加到工具栏
	SendMessage(hwndToolbar,TB_ADDBITMAP,0,(LPARAM)&tbBitmap1);
	//计算工具栏大小
	SendMessage(hwndToolbar,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0);
	//添加按钮到工具栏
	SendMessage(hwndToolbar,TB_ADDBUTTONS,(WPARAM)BUTTONNUMS,(LPARAM)&tbb);

	return hwndToolbar;
}
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParem)
{
	switch(msg) {
	case WM_CREATE:
		CreateSimpleToolbar(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParem);
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	WNDCLASS wc= {sizeof(WNDCLASS)};
	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wc.hInstance=hInstance;
	wc.lpszClassName=" ";
	wc.lpfnWndProc=WndProc;
	//
	wc.hCursor=LoadCursor(hInstance,IDC_ARROW);
	RegisterClass(&wc);
	HWND hwnd=CreateWindow(" ","",WS_OVERLAPPEDWINDOW,350,120,500,500,0,0,hInstance,0);
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	while(GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
