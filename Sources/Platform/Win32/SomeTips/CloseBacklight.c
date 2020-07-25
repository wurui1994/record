#include <windows.h>  
  
int APIENTRY WinMain(HINSTANCE hInstance,  
                     HINSTANCE hPrevInstance,  
                     LPSTR     lpCmdLine,  
                     int        nCmdShow)  
{  
    PostMessage(HWND_BROADCAST,WM_SYSCOMMAND,SC_MONITORPOWER,2);  
    return 0;  
}  