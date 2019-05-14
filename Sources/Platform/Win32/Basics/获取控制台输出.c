#include <Windows.h>
#define max 500

int main(int argc, char* argv[])
{

	SECURITY_ATTRIBUTES saPipe;
	saPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPipe.lpSecurityDescriptor = NULL;
	saPipe.bInheritHandle = TRUE;

	HANDLE hReadPipe, hWritePipe;
	BOOL bSuccess = CreatePipe(&hReadPipe,
	                           &hWritePipe,
	                           &saPipe,
	                           0);
	if(!bSuccess)
		return 0;

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si,0,sizeof(si));
	si.hStdInput=hReadPipe;
	si.hStdOutput=hWritePipe;
	si.dwFlags=STARTF_USESTDHANDLES;
	si.cb=sizeof(si);
	char cmd_line[100] = {"cmd /c dir /b"};

	if(CreateProcess(NULL,cmd_line,NULL,NULL,TRUE,0,NULL,NULL,&si,&pi)) {
		CloseHandle(pi.hThread);
		
		char buf[max] = {0};
		DWORD dw;

		while(ReadFile(hReadPipe,buf,max-1,&dw,NULL)) {
			puts(buf);
			ZeroMemory(buf,max);
		}

		CloseHandle(pi.hProcess);
	}

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);

	return 0;
}
