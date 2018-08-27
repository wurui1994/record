
#include <stdio.h>
#include <windows.h>

//********************************************************************************************************/
//** 函数名 ** SocketInit()
//**  输入  ** 无
//**  输出  ** 无
//**函数描述** 加载套接字
//********************************************************************************************************/
int SocketInit()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData); //返回0，成功，否则就是错误码

	if (err != 0)
	{
		printf("WinSock DLL版本不足要求n");
		return 0;
	}

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return 0;
	}

	return 1;
}

#define MaxSize BUFSIZ

#pragma comment(lib, "WS2_32.LIB")

const char *SeverIp = "0.0.0.0"; //"192.168.1.100";
HANDLE hMutex;

//------------------------------------------------------------------------------------
//函数名称:      Send(SOCKET sockClient)
/*函数功能:      发送数据
/*入口参数:      SOCKET sockClient
//出口参数:
//全局变量引用:
//调用模块:      无
//------------------------------------------------------------------------------------*/
void Send(SOCKET sockClient)
{
	char sendBuf[MaxSize];
	int byte = 0;

	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		gets(sendBuf);
		byte = send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		; //服务器从客户端接受数据
		if (byte <= 0)
		{
			break;
		}

		Sleep(1000);
		ReleaseMutex(hMutex);
	}
	closesocket(sockClient); //关闭socket,一次通信完毕
}
//------------------------------------------------------------------------------------
//函数名称:     Rec()
/*函数功能:     接收函数
/*入口参数:     SOCKET sockClient
//出口参数:
//全局变量引用:
//调用模块:      无
//------------------------------------------------------------------------------------*/
void Rec(SOCKET sockClient)
{

	char revBuf[MaxSize];
	int byte = 0;

	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);

		byte = recv(sockClient, revBuf, strlen(revBuf) + 1, 0); //服务器从客户端接受数据
		if (byte <= 0)
		{
			break;
		}

		printf("%s\n", revBuf);

		Sleep(1000);
		ReleaseMutex(hMutex);
	}
	closesocket(sockClient); //关闭socket,一次通信完毕
}

int main()
{

	if (SOCKET_ERROR == SocketInit())
	{
		return -1;
	}

	while (1)
	{
		SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr = inet_addr(SeverIp); //设定需要连接的服务器的ip地址
		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(6666);								 //设定需要连接的服务器的端口地址
		connect(sockClient, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR)); //与服务器进行连接

		HANDLE hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Rec, (LPVOID)sockClient, 0, 0);

		if (hThread1 != NULL)
		{
			CloseHandle(hThread1);
		}

		HANDLE hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Send, (LPVOID)sockClient, 0, 0);

		if (hThread2 != NULL)
		{
			CloseHandle(hThread2);
		}

		Sleep(1000);
	}
	getchar();

	WSACleanup();
	return -1;
}