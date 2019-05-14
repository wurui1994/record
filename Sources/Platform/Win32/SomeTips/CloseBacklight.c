#include <windows.h>  
  
int APIENTRY WinMain(HINSTANCE hInstance,  
                     HINSTANCE hPrevInstance,  
                     LPSTR     lpCmdLine,  
                     int        nCmdShow)  
{  
    SendMessage(FindWindow(0,0),WM_SYSCOMMAND,SC_MONITORPOWER,2);  
    //Sleep(5000);  
    //SendMessage(FindWindow(0,0),WM_SYSCOMMAND,SC_MONITORPOWER,-1);  
    return 0;  
}  