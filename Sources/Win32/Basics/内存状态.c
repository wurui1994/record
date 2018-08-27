#include <windows.h>
#include <stdio.h>

int main()
{
	char buffer[BUFSIZ];
	int size;

	MEMORYSTATUSEX memStatex;
	memStatex.dwLength = sizeof(memStatex);
	if (GlobalMemoryStatusEx(&memStatex))
	{
		//
		const int nBufSize = 512;
		TCHAR chBuf[nBufSize];
		ZeroMemory(chBuf, nBufSize);
		//内存使用率。
		sprintf(chBuf, "内存使用率: %u%%", memStatex.dwMemoryLoad);
		puts(chBuf);
		//总共物理内存。
		sprintf(chBuf, "总共物理内存: %u", memStatex.ullTotalPhys);
		puts(chBuf);
		//可用物理内存。
		sprintf(chBuf, "可用物理内存: %u", memStatex.ullAvailPhys);
		puts(chBuf);
		//全部内存。
		sprintf(chBuf, "全部内存: %u", memStatex.ullTotalPageFile);
		puts(chBuf);
		//全部可用的内存。
		sprintf(chBuf, "全部可用的内存: %u", memStatex.ullAvailPageFile);
		puts(chBuf);
		//全部的虚拟内存。
		sprintf(chBuf, "全部的虚拟内存: %u", memStatex.ullTotalVirtual);
		puts(chBuf);
	}
	return 0;
}