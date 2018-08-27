//tcc -run gdiplus.c
#include <windows.h>
#pragma comment(lib,"gdiplus")

BOOL CenterWindow(HWND hwnd)
{
    HWND hwndParent;
    RECT rect, rectP;
    int width, height;      
    int screenwidth, screenheight;
    int x, y;
 
    //make the window relative to its parent
    hwndParent = GetDesktopWindow();    
     
    GetWindowRect(hwnd, &rect);
    GetWindowRect(hwndParent, &rectP);
     
    width  = rect.right  - rect.left;
    height = rect.bottom - rect.top;    
     
    x = ((rectP.right-rectP.left) -  width) / 2 + rectP.left;
    y = ((rectP.bottom-rectP.top) - height) / 2 + rectP.top;    
 
    screenwidth  = GetSystemMetrics(SM_CXSCREEN);
    screenheight = GetSystemMetrics(SM_CYSCREEN);
 
    //make sure that the dialog box never moves outside of//the screen
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(x + width  > screenwidth)  x = screenwidth  - width;
    if(y + height > screenheight) y = screenheight - height;    
 
    MoveWindow(hwnd, x, y, width, height, FALSE);
        return TRUE;
}


//GDI+Flat
typedef struct _GdiplusStartupInput
{
    unsigned int GdiplusVersion;
    unsigned int DebugEventCallback;
    BOOL SuppressBackgroundThread;
    BOOL SuppressExternalCodecs;
}GdiplusStartupInput;


int WINAPI GdiplusStartup(int* token, GdiplusStartupInput *input, int *output);
void WINAPI GdiplusShutdown(int token);
int WINAPI GdipCreateFromHDC(HDC hdc, int* graphics);
int WINAPI GdipDeleteGraphics(int graphics);
//画笔
int WINAPI GdipCreatePen1(unsigned int argb_color, float width, int unit, int** pen);
int WINAPI GdipDeletePen(int* pen);
int WINAPI GdipDrawRectangle(int graphics, int* pen, float x, float y, float width, float height);
int WINAPI GdipDrawLine(int graphics, int* pen, float x1, float y1, float x2, float y2);

int token;
int* pen;

//*************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

WNDCLASS wc;
const TCHAR* AppName = TEXT("MyWindowClass1");
HWND hwnd1;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    //GDI+开启
    GdiplusStartupInput StartupInput = { 0 };
    StartupInput.GdiplusVersion = 1;
    if (GdiplusStartup(&token, &StartupInput, NULL))MessageBox(0, TEXT("GdiPlus开启失败"), TEXT("错误"), MB_ICONERROR);

    //这里是在构建窗口类结构
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;//窗口回调函数指针
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;//实例句柄
    wc.hIcon = LoadIcon(hInstance, TEXT("ICON_1"));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);//默认指针
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);//默认背景颜色
    wc.lpszMenuName = NULL;
    wc.lpszClassName = AppName;//窗口类名

                               //注册窗口类
    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("注册窗口类失败!"), TEXT("错误"), MB_ICONERROR);
        return 0;
    }

    //创建窗口
    int style = WS_OVERLAPPEDWINDOW;
    hwnd1 = CreateWindow(AppName, TEXT("窗口标题"), style, 50, 50, 500, 500, 0,NULL, hInstance, 0);
    if (hwnd1 == NULL)
    {
        MessageBox(NULL, TEXT("创建窗口失败!"), TEXT("错误"), MB_ICONERROR);
        return 0;
    }
    //无边框窗口
    /*SetWindowLong(hwnd1, GWL_STYLE, WS_OVERLAPPED | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);*/

    CenterWindow(hwnd1);
    //显示、更新窗口
    ShowWindow(hwnd1, nCmdShow);
    UpdateWindow(hwnd1);

    //消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //GDI+关闭
    GdiplusShutdown(token);//可以把这个写在消息循环后面，程序退出就销毁，或者在不需要GDI+时调用，比如GDI+窗口的WM_DESTROY消息里调用
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (uMsg)
    {

        case WM_PAINT:
            
            
            hdc = BeginPaint(hwnd, &ps);

            int graphics;
            GdipCreateFromHDC(hdc, &graphics);//创建Graphics对象
            GdipCreatePen1(0x60FF2015, 1, 2, &pen);//创建画笔
            GdipDrawRectangle(graphics, pen, 20, 20, 120, 120);//画矩形
            GdipDrawLine(graphics, pen, 50, 60, 170, 340);//画直线

            GdipDeletePen(pen);//销毁画笔
            GdipDeleteGraphics(graphics);//销毁Graphics对象

            EndPaint(hwnd, &ps);
            return 0;//告诉系统，WM_PAINT消息我已经处理了，你那儿凉快哪儿玩去吧。
        case WM_CREATE:
            break;
        case WM_DESTROY://窗口已经销毁
            PostQuitMessage(0);//退出消息循环，结束应用程序
            return 0;
            break;
        case WM_LBUTTONDOWN://鼠标左键按下
                            //让无边框窗口能够拖动(在窗口客户区拖动)
            PostMessage(hwnd, WM_SYSCOMMAND, 61458, 0);
            break;
            /*case WM_MOUSEMOVE://鼠标移动
            int xPos, yPos;
            xPos = GET_X_LPARAM(lParam);//鼠标位置X坐标
            yPos = GET_Y_LPARAM(lParam);//鼠标位置Y坐标
            //不要用LOWORD和HIWORD获取坐标，因为坐标有可能是负的
            break;*/
        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);//其他消息交给系统处理
}