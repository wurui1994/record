/***************************************************
*文件名：pthread_client.c
*文件描述：创建子线程来接收客户端的数据
***************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int sockfd;
	int len;
	struct sockaddr_inaddress;
	int result;
	int i, byte;
	char char_send[100] = {0};
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if (argc != 3)
	{
		printf("Usage:fileclient<address><port>/n"); //用法：文件名服务器IP地址服务器端口地址
		return0;
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("sock");
		exit(1);
	}
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &address.sin_addr);
	len = sizeof(address);
	if ((result = connect(sockfd, (struct sockaddr *)&address, len)) == -1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	for (;;)
	{
		scanf("%s", char_send); //输入发送数据
		fflush(stdin);			//清除输入缓存
		if (strcmp(char_send, "exit") == 0)
		{ //如果输入exit，跳出循环
			if ((byte = send(sockfd, char_send, 100, 0)) == -1)
			{
				perror("send");
				exit(EXIT_FAILURE);
			}
			break;
		}
		if ((byte = send(sockfd, char_send, 100, 0)) == -1)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
	}
	close(sockfd);
	exit(0);
}