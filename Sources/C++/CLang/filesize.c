#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int fileSize(char *filename)
{
	struct stat statbuf;
	stat(filename, &statbuf);
	int size = statbuf.st_size;
	return size;
}
int main(int argc, char *argv[])
{
	char* filename = argv[0];
	int size = fileSize(filename);
	printf("%d\n", size);
	char *buffer = (char *)malloc(size);
	FILE *fp = fopen(filename, "rb");
	fread(buffer, 1, size, fp);
	fwrite(buffer, 1, size, stdout);
	fclose(fp);
	return 0;
}