//系统似乎有缓冲,第二次运行速度明显加快.
#include <time.h>
#include <stdio.h>
#include <windows.h>

int listPath(char *lpszPath,char* fileext)
{
	char szFilePath[MAX_PATH];       /* 遍历路径(正则表达式*.*) */
	char szAllPath[MAX_PATH];        /* 存储具体文件的绝对路径 */
	WIN32_FIND_DATA fdFileData;         /* 存储文件数据 */
	HANDLE hFindFile;                   /* 文件句柄 */
	static int count=0;
	sprintf(szFilePath,"%s\\%s", lpszPath,"*");
	if ((hFindFile = FindFirstFile(szFilePath, &fdFileData))
	        == INVALID_HANDLE_VALUE) {
		printf("Find file failed, Error code:%d\n", GetLastError());
		return 0;
	}
	do {
		sprintf(szAllPath,"%s\\%s", lpszPath, fdFileData.cFileName);
		//printf("%s\\%s\n", lpszPath, fdFileData.cFileName);
		if (!lstrcmp(fdFileData.cFileName,".")) continue;/* 找到的为当前目录. */
		if (!lstrcmp(fdFileData.cFileName, ".."))continue;/* 找到的为父目录.. */
		if (fdFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			listPath(szAllPath,fileext);
		} else {
			//count++;
			if(!stricmp(strchr(fdFileData.cFileName,'.'),fileext)) {
				count++;//puts(szAllPath);
				//system(szAllPath);
			}
		}
	} while (FindNextFile(hFindFile, &fdFileData));
	FindClose(hFindFile);
	return count;
}

int main(int argc, char* argv[])
{
	clock_t st,et;
	st=clock();
	int num=listPath("D:\\Software",".jpg");
	printf("%d\n",num);
	et=clock();
	printf("cost time=%f\n",(float)(et-st)/CLOCKS_PER_SEC);
	return 0;
}
