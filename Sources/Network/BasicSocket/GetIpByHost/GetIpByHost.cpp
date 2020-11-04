#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>
#include <conio.h>
#include <fstream>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
#define LEN_BUFF 512

using namespace std; // Esta linea sirve para poder usar la libreria iostream

int main(int argc, char *argv[])
{
	ofstream archivo;
	SOCKET sockfd;
	int Recv;
	WSADATA wsaData;
	struct hostent *hp;
	unsigned long addr = 0;
	struct sockaddr_in client;
	char Buffer[LEN_BUFF];
	memset(Buffer, '\0', sizeof(Buffer));
	int wsaret = WSAStartup(0x101, &wsaData);
	if (wsaret != 0)
	{
		printf("%s: Ha ocurrido un error en WSAStartup()\n", argv[0]);
		return 0;
	}
	// Valores de la estructura
	memset((char *)&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons((u_short)80);
	// Se requiere comprobar si el nombre del servidore est�� en formato X.X.X.X o DNS.
	if (inet_addr(argv[1]) == INADDR_NONE)
	{
		hp = gethostbyname(argv[1]); // NO est�� en formato X.X.X.X
	}
	else
	{
		addr = inet_addr(argv[1]); // SI est�� en formato X.X.X.X
		hp = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
	}
	if (hp == NULL)
	{
		printf("%s: Host %s desconocido\n", argv[0], argv[1]);
		return 0;
	} // Al final se quiere trabajar con host
	// Si el host antes estaba con nombre DNS se hace gethostbyname
	// Si el host antes estaba con IP se hace gethostbyaddr
	memcpy((char *)&client.sin_addr, hp->h_addr, hp->h_length);
	//Comienza la conexi��n
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("%s: Ha ocurrido un error en socket()\n", argv[0]);
		return 0;
	}
	if (connect(sockfd, (struct sockaddr *)&client, sizeof(client)) < 0)
	{
		printf("%s: Ha ocurrido un error en connect()\n", argv[0]);
		return 0;
	}
	memset(Buffer, '\0', sizeof(Buffer));
	sprintf(Buffer, "GET %s\r\n\r\n", argv[2]);
	send(sockfd, Buffer, strlen(Buffer), 0);
	archivo.open("file.JPG");
	if (archivo.fail())
	{
		cerr << "Error al abrir el archivo" << endl;
		exit(1);
	}
	while (Recv = recv(sockfd, Buffer, sizeof(Buffer), 0))
	{
		archivo.write(Buffer, Recv);
	}
	archivo.close();
	cout << "new message: " << Buffer << " -- Total: " << strlen(Buffer) << " bytes\r\n";
	closesocket(sockfd);
	WSACleanup();
	return 0;
}