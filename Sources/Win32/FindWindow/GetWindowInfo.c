
#include <windows.h>

int main(int argc, char* argv[])
{
	WINDOWINFO info;
	HWND hCalc = FindWindow(L"Notepad",0);
	HWND hGetWindow = GetWindow(hCalc, GW_CHILD);
	GetWindowInfo(hCalc, &info);
	wprintf_s(L"=====================================\n");
	wprintf_s(L"===============START=================\n");
	wprintf_s(L"hGetWindow  =  %X\n", hGetWindow);
	wprintf_s(L"info.atomWindowType =  %X\n", info.atomWindowType);
	wprintf_s(L"info.cbSize  =  %X\n", info.cbSize);
	wprintf_s(L"info.cxWindowBorders  =  %X\n", info.cxWindowBorders);
	wprintf_s(L"info.cyWindowBorders  =  %X\n", info.cyWindowBorders);
	wprintf_s(L"info.dwExStyle  =  %X\n", info.dwExStyle);
	wprintf_s(L"info.dwStyle  =  %X\n", info.dwStyle);
	wprintf_s(L"info.dwWindowStatus  =  %X\n", info.dwWindowStatus);
	wprintf_s(L"info.rcClient  =  %X\n", info.rcClient);
	wprintf_s(L"info.rcWindow  =  %X\n", info.rcWindow);
	wprintf_s(L"info.wCreatorVersion  =  %x\n", info.wCreatorVersion);

	wprintf_s(L"===================================\n");
	wprintf_s(L"===============END=================\n");
	getchar();
	return 0;
}
