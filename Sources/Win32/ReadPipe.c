#include <windows.h>
#include <stdio.h>
int main()
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return;
	}
	char command[1024];				  //长达1K的命令行，够用了吧
	strcpy(command, "cmd /c dir /b"); //注意dir不是一个可执行文件
	// strcpy(command,"cmd /c dir /b");
	// strcat(command,para_sys);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;  //把创建进程的标准错误输出重定向到管道输入
	si.hStdOutput = hWrite; //把创建进程的标准输出重定向到管道输入
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//关键步骤，CreateProcess函数参数意义请查阅MSDN
	if (!CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		MessageBox(0, 0, "Feature Detection Failed!", 0);
		return;
	}
	CloseHandle(hWrite);
	char buffer[4096] = {0}; //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。
	DWORD bytesRead;
	while (1)
	{
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
			break;
		//buffer中就是执行的结果，可以保存到文本，也可以直接输出
		printf(buffer);
	}
	CloseHandle(hRead);
}