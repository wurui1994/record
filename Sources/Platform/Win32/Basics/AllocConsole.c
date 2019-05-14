#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HINSTANCE g_hInstance = 0;
HANDLE g_hOutput = 0;
void OnKeyDown( HWND hWnd, WPARAM wParam )
{
	CHAR szText[256] = { 0 };
	sprintf( szText, "WM_KEYDOWN:%08X\n", wParam );
	WriteConsole( g_hOutput, szText, strlen(szText),
	              NULL, NULL );
}
void OnKeyUp( HWND hWnd, WPARAM wParam )
{
	CHAR szText[256] = { 0 };
	sprintf( szText, "WM_KEYUP:%08X\n", wParam );
	WriteConsole( g_hOutput, szText, strlen(szText),
	              NULL, NULL );
}
//窗口处理函数
LRESULT CALLBACK WndProc( HWND hWnd, UINT nMsg,
                          WPARAM wParam, LPARAM lParam )
{
	switch( nMsg ) {
	case WM_KEYDOWN:
		OnKeyDown( hWnd, wParam );
		break;
	case WM_KEYUP:
		OnKeyUp( hWnd, wParam );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}
	return DefWindowProc( hWnd, nMsg, wParam, lParam );
}
//注册窗口类
BOOL Register( LPSTR lpClassName, WNDPROC wndProc )
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof( wce );
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = g_hInstance;
	wce.lpfnWndProc = wndProc;
	wce.lpszClassName = lpClassName;
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx( &wce );
	if( nAtom == 0 )
		return FALSE;
	return TRUE;
}
//创建主窗口
HWND CreateMain( LPSTR lpClassName, LPSTR lpWndName )
{
	HWND hWnd = CreateWindowEx( 0, lpClassName, lpWndName,
	                            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
	                            CW_USEDEFAULT, CW_USEDEFAULT,
	                            CW_USEDEFAULT, NULL, NULL, g_hInstance,
	                            NULL );
	return hWnd;
}
//显示窗口
void Display( HWND hWnd )
{
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
}
//消息循环
void Message( )
{
	MSG nMsg = { 0 };
	while( GetMessage( &nMsg, NULL, 0, 0 ) ) {
		TranslateMessage( &nMsg );
		DispatchMessage( &nMsg );
	}
}
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR	 lpCmdLine,
                     int	   nCmdShow)
{
	AllocConsole( );
	g_hOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	g_hInstance = hInstance;
	if( !Register( "Main", WndProc ) ) {
		MessageBox( NULL, "注册失败", "Infor", MB_OK );
		return 0;
	}
	HWND hWnd = CreateMain( "Main", "window" );
	Display( hWnd );
	Message( );
	return 0;
}