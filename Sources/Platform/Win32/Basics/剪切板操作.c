#include <Windows.h>
#include <stdio.h>

int main()
{
	HWND hwnd = FindWindow(0, 0);
	HGLOBAL hmem = NULL;
	if (!IsClipboardFormatAvailable(CF_TEXT)) return 0; //CF_UNICODETEX											
	if (!OpenClipboard(hwnd)) return 0;//二、 打开剪贴板
	hmem = GetClipboardData(CF_TEXT);//三、 获取剪贴板句柄
	if (!hmem) return 0;
	char* ps = (char*)GlobalLock(hmem);//四、 锁定全局内存获取缓冲区指针，
	size_t size = GlobalSize(hmem);
	char* ws =malloc(sizeof(char)*size);
	memcpy(ws, ps, size);
	puts(ws);
	CloseClipboard();//五、 关闭剪贴板，以使其它程序可以访问，释放掉内存锁
	GlobalUnlock(hmem);
	return 0;
}