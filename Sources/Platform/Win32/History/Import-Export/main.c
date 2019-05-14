#include <stdio.h>
#include <string.h>
#include <windows.h>


void GetImportDllList(void)
{
	IMAGE_IMPORT_DESCRIPTOR* importEntry = 0;
	IMAGE_SECTION_HEADER* sectionHeader = 0;
	char* filename = "E:\\import.exe";
	//打开文件
	HANDLE hfile = CreateFileA(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if (hfile == INVALID_HANDLE_VALUE) {
		printf("%s","文件打开失败！");
		return;
	}
	//创建内存映射
	HANDLE hmap = CreateFileMapping(hfile,NULL,PAGE_READONLY,0,0,NULL);
	if (hmap == 0) {
		printf("%s","创建内存映射失败！");
		return;
	}
	//映射到当前进程，pBaseAddress是基址
	HANDLE pBaseAddress = MapViewOfFile(hmap,FILE_MAP_READ,0,0,0);
	if (!pBaseAddress) {
		printf("%s","获取地址失败！");
		return;
	}
	//获取Dos信息头部结构数据
	IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)pBaseAddress;
	//判断Dos标识
	if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		printf("%s","不可识别的文件格式！");
		return;
	}
	//获取NT信息头部结构数据，IsBadReadPtr判断指针是否可读，ntHeader->Signature是NT标识
	IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)((DWORD)pBaseAddress+dosHeader->e_lfanew);
	if (ntHeader->Signature != IMAGE_NT_SIGNATURE) {
		printf("%s","不是有效地Win32程序！");
		return;
	}
	//定位到第一个节的地址
	sectionHeader = (IMAGE_SECTION_HEADER*)((DWORD)ntHeader+sizeof(IMAGE_NT_HEADERS));
	//ntHeader->FileHeader.NumberOfSections为节的数量，此处循环，找到引入表的节
	for (int i=0; i<ntHeader->FileHeader.NumberOfSections; i++) {
		//IMAGE_DIRECTORY_ENTRY_IMPORT，引入表
		if (sectionHeader->VirtualAddress == ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress) {
			break;
		}
		//没找到，那么增加SizeOf(IMAGE_SECTION_HEADER)字节数，指向下一个节
		sectionHeader++;
	}
	//引入表入口
	importEntry = (IMAGE_IMPORT_DESCRIPTOR*)((DWORD)pBaseAddress+sectionHeader->PointerToRawData);
	printf("下面是%s的引入文件\n",filename);
	//加载的DLL的名称，这里是RVA地址，需要转换成文件偏移地址，因为我们不是通过PE加载器加载，而是映射到内存
	while (importEntry->Name != 0) {
		DWORD offset = (DWORD)pBaseAddress+importEntry->Name-(sectionHeader->VirtualAddress - sectionHeader->PointerToRawData);
		char* s = (char*)offset;
		printf("%s\n",s);
		//继续读取
		importEntry++;
	}
	UnmapViewOfFile(pBaseAddress);
	CloseHandle(hmap);
	CloseHandle(hfile);
}

int main()
{
	GetImportDllList();
	return 0;
}