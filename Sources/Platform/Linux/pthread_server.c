/***************************************************
*文件名：pthread_server.c
*文件描述：创建子线程来接收客户端的数据
***************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
void *rec_data(void *fd);
int main(intargc, char *argv[])
{
	int server_sockfd;
	int *client_sockfd;
	int server_len, client_len;
	struct sockaddr_inserver_address;
	struct sockaddr_inclient_address;
	struct sockaddr_intempaddr;
	int i, byte;
	char char_recv, char_send;
	socklen_t templen;
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0); //创建套接字
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len); //绑定套接字
	templen = sizeof(struct sockaddr);
	printf("server waiting forconnect/n");
	while (1)
	{
		pthread_t thread; //创建不同的子线程以区别不同的客户端
		client_sockfd = (int *)malloc(sizeof(int));
		client_len = sizeof(client_address);
		*client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, (socklen_t *)&client_len);
		if (-1 == *client_sockfd)
		{
			perror("accept");
			continue;
		}
		if (pthread_create(&thread, NULL, rec_data, client_sockfd) != 0)
		{ //创建子线程
			perror("pthread_create");
			break;
		}
	}
	shutdown(*client_sockfd, 2);
	shutdown(server_sockfd, 2);
}
/*****************************************
*函数名称：rec_data
*功能描述：接受客户端的数据
*参数列表：fd——连接套接字
*返回结果：void
*****************************************/
void *rec_data(void *fd)
{
	int client_sockfd;
	int i, byte;
	char char_recv[100]; //存放数据
	client_sockfd = *((int *)fd);
	for (;;)
	{
		if ((byte = recv(client_sockfd, char_recv, 100, 0)) == -1)
		{
			perror("recv");
			exit(EXIT_FAILURE);
		}
		if (strcmp(char_recv, "exit") == 0) //接受到exit时，跳出循环
			break;
		printf("receivefromclientis%s\n", char_recv); //打印收到的数据
	}
	free(fd);
	close(client_sockfd);
	pthread_exit(NULL);
}