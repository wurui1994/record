#include <windows.h>
#include <stdio.h>

#pragma comment(lib,"gdi32")
#pragma comment(lib,"user32")

int main()
{
	HDC hdc=GetDC(0);
	printf("%d\n",GetDeviceCaps(hdc,BITSPIXEL));
	printf("%d\n",GetDeviceCaps(hdc,PLANES));
	printf("%d\n",GetDeviceCaps(hdc,COLORRES));
	printf("%d\n",GetDeviceCaps(hdc,DESKTOPHORZRES));
	return 0;
}