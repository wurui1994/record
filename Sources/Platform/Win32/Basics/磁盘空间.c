#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[])
{
	DWORD dwSectPerClust,dwBytesPerSect,dwFreeClusters,dwTotalClusters;
	GetDiskFreeSpace (NULL, &dwSectPerClust, &dwBytesPerSect,&dwFreeClusters,&dwTotalClusters);
	printf("磁盘一个簇内的扇区数=%d\n磁盘一个扇区内的字节数=%d\n磁盘的剩余簇数=%d\n磁盘总簇数=%d\n",
	       dwSectPerClust,dwBytesPerSect,dwFreeClusters,dwTotalClusters);
	double size=dwSectPerClust*dwBytesPerSect;//簇大小
	printf("簇大小=%e剩余字节数=%e\n总字节数=%e",size,dwFreeClusters*size,dwTotalClusters*size);
	return 0;
}
/*
磁盘一个簇内的扇区数=8
磁盘一个扇区内的字节数=512
磁盘的剩余簇数=54362767
磁盘总簇数=65537159
一个簇8*512=4k
*/