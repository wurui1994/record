#include <windows.h>
#include <commctrl.h>

int main()
{
	MSG msg;
	WNDCLASS wndclass;
    wndclass.cbClsExtra = 0;                                          // 类附加内存
    wndclass.cbWndExtra = 0;                                          // 窗口附加内存
    wndclass.hbrBackground = (HBRUSH) GetStockObject(COLOR_WINDOW);    // 背景画刷句柄
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                   // 窗口光标句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                       // 窗口图标句柄
    wndclass.hInstance = 0;                                   // 包含窗口过程函数的程序实例
    wndclass.lpfnWndProc = DefWindowProc;                                // 只想窗口过程函数的指针
    wndclass.lpszClassName = "CRoot";                                // 窗口类名称
    wndclass.lpszMenuName = NULL;                                     // 菜单资源
    wndclass.style = CS_HREDRAW | CS_VREDRAW;                         // 窗口样式
    RegisterClass(&wndclass);
    // 创建窗口， 定义一个变量用来保存成功创建窗口后返回的句柄
    HWND hwnd;
    hwnd = CreateWindow("CRoot","Hello World",WS_CAPTION|WS_SYSMENU,
                        350, 120, 500, 500,
                        NULL,NULL,0,NULL
                       );
    // 显示及刷新窗口
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
	
	const int BUTTONNUMS = 2;
	//按钮
	TBBUTTON tbb[2];
	ZeroMemory(tbb, sizeof(tbb));
	//CUT,COPY,PASTE
	/*
	#define STD_CUT 0
	#define STD_COPY 1
	#define STD_PASTE 2
	#define STD_UNDO 3
	#define STD_REDOW 4
	#define STD_DELETE 5
	#define STD_FILENEW 6
	#define STD_FILEOPEN 7
	#define STD_FILESAVE 8
	#define STD_PRINTPRE 9
	#define STD_PROPERTIES 10
	#define STD_HELP 11
	#define STD_FIND 12
	#define STD_REPLACE 13
	#define STD_PRINT 14
	*/
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
	
	HWND hwnd2=CreateWindow(TOOLBARCLASSNAME,"按钮",WS_VISIBLE|WS_CHILD|WS_BORDER,
	                   0,0,0,0,hwnd,(HMENU)0,0,0);
	//将位图添加到工具栏
	SendMessage(hwnd2,TB_ADDBITMAP,0,(LPARAM)&tbBitmap1);
	//计算工具栏大小
	SendMessage(hwnd2,TB_BUTTONSTRUCTSIZE,(WPARAM)sizeof(TBBUTTON),0);
	//添加按钮到工具栏
	SendMessage(hwnd2,TB_ADDBUTTONS,(WPARAM)BUTTONNUMS,(LPARAM)&tbb);
	
	while(GetMessage(&msg,hwnd,0,0))
	{
		if(msg.message == NULL)break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}