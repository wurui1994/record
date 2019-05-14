#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"user32")
#pragma comment(lib,"advapi32")

int main()
{
	char buffer[BUFSIZ];
	int size;
	GetComputerName(buffer, &size);
	puts(buffer);
	GetUserName(buffer, &size);
	puts(buffer);
	SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, buffer, 0);
	puts(buffer);
	return 0;
}