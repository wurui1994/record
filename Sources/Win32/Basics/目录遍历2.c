#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// typedef struct {
	// int length;
	// char** strs;
// }vecstr;

int listPath(char *lpszPath, char* fileext)
{
	char szFilePath[MAX_PATH];       /* 遍历路径(正则表达式*.*) */
	char szAllPath[MAX_PATH];        /* 存储具体文件的绝对路径 */
	WIN32_FIND_DATA fdFileData;         /* 存储文件数据 */
	HANDLE hFindFile;                   /* 文件句柄 */
	//static int count = 0;
	//static vecstr vs = { 0,0 };
	sprintf(szFilePath, "%s\\%s", lpszPath, "*");
	if ((hFindFile = FindFirstFile(szFilePath, &fdFileData))
		== INVALID_HANDLE_VALUE) {
		//printf("%s Find file failed, Error code:%d\n", szFilePath, GetLastError());
		return 0;
	}
	do {
		sprintf(szAllPath, "%s\\%s", lpszPath, fdFileData.cFileName);
		//printf("%s\\%s\n", lpszPath, fdFileData.cFileName);
		if (!lstrcmp(fdFileData.cFileName, ".")) continue;/* 找到的为当前目录. */
		if (!lstrcmp(fdFileData.cFileName, ".."))continue;/* 找到的为父目录.. */
		if (fdFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			listPath(szAllPath, fileext);
		}
		else {
			//count++;
			//puts(szAllPath);
			char* pdot;
			if ((pdot= strchr(fdFileData.cFileName, '.'))&&
				stricmp(pdot, fileext)==0) {
			//count++;
			//puts(szAllPath);
						//system(szAllPath);
			// vs.strs = (char**)realloc(vs.strs, ++(vs.length) * sizeof(char*));
			// char* line = (char*)malloc(BUFSIZ);
			// memcpy(line, szAllPath, strlen(szAllPath) + 1);
			// vs.strs[vs.length - 1] = line;
			}
		}
	} while (FindNextFile(hFindFile, &fdFileData));
	FindClose(hFindFile);
	return 0;
}

int main(int argc, char* argv[])
{
	CHAR	szDrive[BUFSIZ];
	DWORD	iLength;
	INT		iSub;
	ZeroMemory(szDrive, BUFSIZ);
	iLength = GetLogicalDriveStringsA(BUFSIZ-1, szDrive);
	//
	clock_t st, et;
	st = clock();
	//freopen("test.txt", "wt",stdout);
	//vecstr v= 
	// listPath("C:", " ");
	listPath("D:", " ");
	// listPath("E:", " ");
	// listPath("F:", " ");
	//Only list fixed drive.
	//for(iSub=0; iSub<iLength; iSub+=4) {
	//	if(GetDriveType(szDrive+iSub)==DRIVE_FIXED)
	//		listPath(szDrive+iSub,".jpg");
			//printf("%s\n", szDrive+iSub);
	//}
	//printf("\n");
	//fclose(stdout);
	//freopen("CON","w",stdout);
	//printf("%d\n", v.length);
	et = clock();
	printf("cost time=%fsecond\n", (float)(et - st) / CLOCKS_PER_SEC);
	//for (int i = 0; i < v.length; i++) {
		//printf("%s\n", v.strs[i]);
	//}
	return 0;
}
