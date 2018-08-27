#include <windows.h>
#include <stdio.h>

DWORD WINAPI mainGUI(LPVOID lp)
{
	HMODULE hInstance = 0;
	hInstance = GetModuleHandle(NULL);
	HWND hWnd;
	MSG msg;
	//创建一个新的窗口
	hWnd = CreateWindow(
	           "EDIT",
	           "由main创建的消息",
	           WS_OVERLAPPEDWINDOW,
	           CW_USEDEFAULT,
	           CW_USEDEFAULT,
	           640,
	           480,
	           NULL, NULL,
	           hInstance,
	           NULL);
	if (!hWnd)
		return (1);
	//绑定hWnd与hWindow,向hWindow发送的消息由此线程处理
	*(HWND*)lp = hWnd;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

int main(int argc, char* argv[])
{
	DWORD ID;
	HWND hWindow;
	char szOutput[64];
	CreateThread(NULL, 0, mainGUI, &hWindow, NULL, &ID);
	printf("This console created the window above.\n ");
	while (1) {
		scanf("%s", szOutput);
		if (!strcmp(szOutput, "quit"))
			break;
		//发送WM_SETTEXT消息
		SendMessage(hWindow, WM_SETTEXT, strlen(szOutput), (LPARAM)szOutput);
	}
	return 0;
}