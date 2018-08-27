#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_PAGE_BUF_SIZE 1048576
int main(int argc, char *argv[])
{
	// printf("%d\n", argc);
	if (argc < 2)
	{
		puts("Need input.");
		return 0;
	}
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}
	char url[BUFSIZ];
	memcpy(url, argv[1], strlen(argv[1]) + 1);
	//char url[] = "http://www.baidu.com/";
	if (strlen(url) > 2000)
	{
		return -1;
	}

	const char *pos = strstr(url, "http://");
	// printf("pos:%s\n", pos);
	if (pos == NULL)
		pos = url;
	else
		pos += strlen("http://");
	if (strstr(pos, "/") == 0)
		strcat(url, "/");
	char host[100];
	char resource[2000];
	sscanf(pos, "%[^/]%s", host, resource);
	printf("Host:%s\n", host);
	printf("Resource:%s\n", resource);
	//建立socket
	struct hostent *hp = gethostbyname(host);
	if (hp == NULL)
	{
		puts("Can not find host address");
		return -1;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1 || sock == -2)
	{
		puts("Can not create sock.");
		return -1;
	}

	//建立服务器地址
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(80);
	memcpy(&sa.sin_addr, hp->h_addr, 4);

	//建立连接
	if (0 != connect(sock, (SOCKADDR *)&sa, sizeof(sa)))
	{
		printf("Can not connect: %s", url);
		closesocket(sock);
		return -1;
	};

	//准备发送数据
	char request[BUFSIZ] = "GET ";
	strcat(request, resource);
	strcat(request, " HTTP/1.1\r\nHost:");
	strcat(request, host);
	strcat(request, "\r\nConnection:Close\r\n\r\n");
	printf("\nThe Request:{\n\n%s}", request);
	//发送数据
	if (SOCKET_ERROR == send(sock, request, strlen(request), 0))
	{
		puts("send error");
		closesocket(sock);
		return -1;
	}

	//接收数据
	int Length = DEFAULT_PAGE_BUF_SIZE;
	char *buffer = (char *)malloc(Length);
	memset(buffer, 0, Length);

	int bytesRead = 0;
	int ret = 1;
	int ContentLength;
	ret = recv(sock, buffer, Length, 0);
	printf("\n\nRead: %dBytes\n", ret);
	char *poslen = strstr(buffer, "Content-Length");
	//计算HTTP信息头的偏移地址
	int offset = strstr(buffer, "\r\n\r\n") - buffer + 4;
	char *header = (char *)malloc(offset);
	memcpy(header, buffer, offset - 4);
	header[offset - 4] = '\0';
	printf("\nHTTP Header:{\n%s\n}", header);
	sscanf(poslen, "Content-Length: %d\r\n", &ContentLength);
	printf("\nContent-Length: %d\n", ContentLength);
	if (argc > 2)
	{
		buffer = (char *)realloc(buffer, ContentLength + offset);
		int rest = ContentLength + offset - ret;
		char *p = buffer + ret;
		if (!buffer)
			return 0;
		while (ret > 0)
		{
			ret = recv(sock, p + bytesRead, rest - bytesRead, 0);
			if (ret > 0)
				bytesRead += ret;
			printf(" %dBytes", ret);
		}
		printf("\n");

		FILE *fp = fopen(argv[2], "wb");
		fwrite(buffer + offset, 1, ContentLength, fp);
		fclose(fp);
	}
	//printf("%s\n", buffer);
	closesocket(sock);
	WSACleanup();
	return 0;
}