#include <Windows.h>
// #include <WindowsX.h>
#include <CommCtrl.h> //包含头文件
// 导入静态库
#pragma comment(lib, "Comctl32.lib")
// 开启视觉效果 Copy from MSDN
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// 先声明一个WindowProc回调
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
// 入口点
int WINAPI wWinMain(HINSTANCE hTheApp, HINSTANCE hPrevApp, LPWSTR lpCmd, int nShow)
{
    PCWSTR cn = L"My"; // 窗口名
    PCWSTR tt = L"应用程序"; // 窗口标题
                         // 设计窗口类
    WNDCLASS wc = { sizeof(WNDCLASS) };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    LoadIconMetric(hTheApp, IDI_APPLICATION, LIM_SMALL, &wc.hIcon);
    wc.lpszClassName = cn;
    wc.hInstance = hTheApp;
    RegisterClass(&wc); // 注册窗口类
                        // 创建窗口
    HWND hwnd = CreateWindow(cn, tt, WS_OVERLAPPEDWINDOW,
        28, 34, 400, 330, NULL, NULL, hTheApp, NULL);
    if (!hwnd)
    { /* 如果窗口创建失败，
      那继续执行也没有意义
      长痛不如短痛，结束吧。
      */
        return 0;
    }
    ShowWindow(hwnd, nShow); //显示窗口
    UpdateWindow(hwnd); //更新窗口
                        // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); //调度消息到WindowProc回调
    }
    return 0;
}

/*-----------------------------------------------------------------*/
//控件ID
#define IDC_RADBTN1			50001
#define IDC_RADBTN2			50002
#define IDC_RADBTN3			50003
#define IDC_RADBTNBLUE		51001
#define IDC_RADBTNRED		51002
#define IDC_RADBTNGREEN		51003
#define IDC_BTN_OK			1107 //确定按钮ID
/*-----------------------------------------------------------------*/
// 消息处理函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        // 获取当前实例句柄
        HINSTANCE hthisapp = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
        // 纵坐标，控件将以此作为基准，
        // 排列时依次增加
        int yLoc = 0;
        // 用来显示文本
        yLoc += 10;
        CreateWindow(L"Static", L"请问你的性别是：",
            SS_SIMPLE | WS_CHILD | WS_VISIBLE,
            10, yLoc, 160, 18,
            hwnd, NULL,
            hthisapp,
            NULL);
        // 第一组单选按钮
        yLoc += 22;
        CreateWindow(L"Button", L"男",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            12, yLoc, 60, 16,
            hwnd,
            (HMENU)IDC_RADBTN1,
            hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"女",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16,
            hwnd, (HMENU)IDC_RADBTN2, hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"人妖", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTN3, hthisapp, NULL);
        // 显示文本
        yLoc += 38;
        CreateWindow(L"Static", L"你喜欢哪一种颜色？",
            WS_CHILD | WS_VISIBLE | SS_SIMPLE,
            10, yLoc, 150, 18, hwnd, NULL, hthisapp, NULL);
        //第二组单选按钮
        yLoc += 22;
        CreateWindow(L"Button", L"蓝色", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTNBLUE, hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"红色", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTNRED, hthisapp, NULL);
        yLoc += 20;
        CreateWindow(L"Button", L"绿色", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            12, yLoc, 60, 16, hwnd, (HMENU)IDC_RADBTNGREEN, hthisapp, NULL);
        // 创建一个确定按钮
        CreateWindow(L"Button", L"确定", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            230, 180, 80, 27, hwnd, (HMENU)IDC_BTN_OK, hthisapp, NULL);
    }
    return 0;
    case WM_DESTROY:
        PostQuitMessage(0); //平安退出
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}