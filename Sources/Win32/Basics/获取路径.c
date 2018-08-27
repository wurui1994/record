#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[])
{
	char path[MAX_PATH];
	char szpath[MAX_PATH];
	char syspath[MAX_PATH];
	char winpath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,path);
	GetModuleFileName( NULL, szpath, MAX_PATH );
	GetSystemDirectory(syspath,MAX_PATH);
	GetWindowsDirectory(winpath,MAX_PATH);
	puts(syspath);
	puts(winpath);
	//puts(argv[1]);
	puts(path);
	puts(szpath);
	puts(argv[0]);
	return 0;
}
