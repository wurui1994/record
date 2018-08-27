// #pragma comment(linker,"\"/manifestdependency:type='win32' "\  
                        // "name='Microsoft.Windows.Common-Controls' "\  
                        // "version='6.0.0.0' processorArchitecture='*' "\  
                        // "publicKeyToken='6595b64144ccf1df' language='*'\"")  
#include <windows.h>

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

// 
LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindProc(HWND, UINT, WPARAM, LPARAM);
WNDPROC Button1Proc;
int WINAPI WinMain(
    HINSTANCE hInstance,         // handle to current instance
    HINSTANCE hPrevInstance,     // handle to previous instance
    LPSTR lpCmdLine,             // command line
    int nCmdShow                 // show state
)
{
    WNDCLASS wndclass;
    wndclass.cbClsExtra = 0;                                       
    wndclass.cbWndExtra = 0;                                       
    wndclass.hbrBackground = (HBRUSH) GetStockObject(COLOR_WINDOW);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);              
    wndclass.hInstance = hInstance;                                
    wndclass.lpfnWndProc = WinProc;                                
    wndclass.lpszClassName = "CRoot";                              
    wndclass.lpszMenuName = NULL;                                  
    wndclass.style = CS_HREDRAW | CS_VREDRAW;                      
    RegisterClass(&wndclass);
    //
    HWND hwnd;
    hwnd = CreateWindow("CRoot","Hello World",WS_CAPTION|WS_SYSMENU,
                        500, 240, 200, 120,
                        NULL,NULL,hInstance,NULL
                       );
                       
    CenterWindow(hwnd);
    // 
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    // 
    MSG msg;
    while (GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
// 
LRESULT CALLBACK WinProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    WORD wmId    = LOWORD(wParam);
    HWND hBtn1;
    switch(uMsg) {
    case WM_CREATE: {
        hBtn1=CreateWindow("Button","按钮",WS_VISIBLE|WS_CHILD|BS_FLAT,
                           50,20,70,40,hwnd,(HMENU)0,((LPCREATESTRUCT)lParam)->hInstance,0);
        Button1Proc= (WNDPROC)SetWindowLong(hBtn1, GWL_WNDPROC,(LONG)ChildWindProc);
    }
    break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK ChildWindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC				hdc,hdc2;
    PAINTSTRUCT		ps;
    RECT			rect;
    HFONT hFont;
    int h=24;
    switch (message) {
    case WM_CREATE:
        SetWindowLong(hwnd, 0, 0);
        return 0;
    // case WM_LBUTTONDBLCLK:
        // MessageBoxA(NULL,"Hello Button2!","My TestProject",MB_OK);
        // hdc = GetDC(hwnd);
        // hFont=CreateFont(h,0,0,0,0,0,0,0,1,0,0,0,0,"Consolas");
        // SelectObject(hdc,hFont);
        // SetBkMode(hdc,OPAQUE);
        // SetTextColor(hdc,RGB(0,0,255));
        // SetBkColor(hdc,RGB(255,0,255));
        // TextOut(hdc,0,0,"hello",sizeof("hello")-1);
        // return 0;//This return is different to break;
    // case WM_LBUTTONDOWN:
        // MessageBoxA(NULL,"Hello Button2!","My TestProject",MB_OK);
        // hdc = GetDC(hwnd);
        // hFont=CreateFont(h,0,0,0,0,0,0,0,1,0,0,0,0,"Consolas");
        // SelectObject(hdc,hFont);
        // SetBkMode(hdc,OPAQUE);
        // SetTextColor(hdc,RGB(0,0,255));
        // SetBkColor(hdc,RGB(0,255,255));
        // TextOut(hdc,0,0,"hello",sizeof("hello")-1);
        // return 0;//This return is different to break;
    // case WM_MOUSEMOVE:
        // hdc = GetDC(hwnd);
        // hFont=CreateFont(h,0,0,0,0,0,0,0,1,0,0,0,0,"Consolas");
        // SelectObject(hdc,hFont);
        // SetBkMode(hdc,OPAQUE);
        // SetTextColor(hdc,RGB(255,0,0));
        // SetBkColor(hdc,RGB(0,255,255));
        // TextOut(hdc,0,0,"hello",sizeof("hello")-1);
        // TRACKMOUSEEVENT tme;
        // tme.cbSize = sizeof (tme);
        // tme.dwFlags = TME_LEAVE|TME_HOVER;
        // tme.dwHoverTime = HOVER_DEFAULT;
        // tme.hwndTrack = hwnd;
        // TrackMouseEvent(&tme);
        // return 0;
    // case WM_MOUSELEAVE:
        // InvalidateRect(hwnd, NULL, FALSE);
        // MessageBoxA(NULL,"Hello Button2!","My TestProject",MB_OK);
        // return 0;
    // case WM_PAINT:
        // hdc=BeginPaint(hwnd,&ps);
        // hFont=CreateFont(h,0,0,0,0,0,0,0,1,0,0,0,0,"Consolas");
        // SelectObject(hdc,hFont);
        // SetBkMode(hdc,OPAQUE);
        // SetTextColor(hdc,RGB(255,0,0));
        // SetBkColor(hdc,RGB(0,255,0));
        // TextOut(hdc,0,0,"hello",sizeof("hello")-1);
        // ValidateRect(hwnd,NULL);
        // EndPaint(hwnd,&ps);
        // return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return CallWindowProc(Button1Proc,hwnd, message, wParam, lParam);
}