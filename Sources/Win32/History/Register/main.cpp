#include <Windows.h>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <string>
#include <stack>

typedef void (__stdcall *P_WALK_DIR_CALLBACK)(const std::string &In_strFilePath);

int WalkDir(const char *In_pcRoot, P_WALK_DIR_CALLBACK In_pfunCallBack)
{
	int         iRetVal = 0;
	std::string strRoot;
	std::stack<std::string> stkDirs;

	if (In_pcRoot == NULL || In_pfunCallBack == NULL) {
		iRetVal = -1;
		goto fun_ret;
	}

	strRoot = In_pcRoot;
	if (strRoot.empty()) {
		iRetVal = -2;
		goto fun_ret;
	}

	if (strRoot.back() != '\\' && strRoot.back() != '/')
		strRoot += '\\';
	stkDirs.push(strRoot);

	while (!stkDirs.empty()) {
		std::string         strDirForWalk;
		WIN32_FIND_DATAA    Win32FindData   = {0};
		HANDLE              hFindHandle     = NULL;

		strDirForWalk = stkDirs.top();
		stkDirs.pop();
		hFindHandle = FindFirstFileA((strDirForWalk + "*").c_str(), &Win32FindData);
		if (hFindHandle == INVALID_HANDLE_VALUE)
			continue;

		if (!(strlen(Win32FindData.cFileName) == 1 && strncmp(Win32FindData.cFileName, ".", 1) == 0)
		        && !(strlen(Win32FindData.cFileName) == 2 && strncmp(Win32FindData.cFileName, "..", 2) == 0)) {
			if (Win32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				stkDirs.push(strDirForWalk + Win32FindData.cFileName + "\\");
			else
				In_pfunCallBack(strDirForWalk + Win32FindData.cFileName);
		}
		while (FindNextFileA(hFindHandle, &Win32FindData)) {
			if (!(strlen(Win32FindData.cFileName) == 1 && strncmp(Win32FindData.cFileName, ".", 1) == 0)
			        && !(strlen(Win32FindData.cFileName) == 2 && strncmp(Win32FindData.cFileName, "..", 2) == 0)) {
				if (Win32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					stkDirs.push(strDirForWalk + Win32FindData.cFileName + "\\");
				else
					In_pfunCallBack(strDirForWalk + Win32FindData.cFileName);
			}
		}

		if (hFindHandle != INVALID_HANDLE_VALUE)
			FindClose(hFindHandle);
	}

fun_ret:
	return iRetVal;
}

void inline __stdcall WalkDirCallBack(const std::string &In_strFilePath)
{
	//printf("%s\n", In_strFilePath.c_str());
	return;
}

int main(int argc, char **argv)
{
	
	clock_t st,et;
	st=clock();
	WalkDir("E:", WalkDirCallBack);
	et=clock();
	printf("cost time=%f\n",(float)(et-st)/CLOCKS_PER_SEC);
	return 0;
}