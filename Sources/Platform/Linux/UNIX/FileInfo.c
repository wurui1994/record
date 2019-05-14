//#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
//#include <windows.h>
#include <locale.h>

int
main(int argc, char *argv[])
{
	struct stat    buf;
	char buffer[BUFSIZ];
	setlocale(LC_TIME, "zh_CN.UTF-8");
	stat("E:\\", &buf);
	// printf("%d\n",buf.st_dev);
	// printf("%d\n",buf.st_ino);
	// printf("%d\n",buf.st_mode);
	unsigned short mode = buf.st_mode;
	int len = sizeof(mode)*8;
	while(--len)printf("%d",1&mode>>len);
	printf("\n%d\n",S_IRUSR&mode);
	printf("%o\n",mode);
	// printf("%d\n",buf.st_nlink);
	// printf("%d\n",buf.st_uid);
	// printf("%d\n",buf.st_gid);
	// printf("%c:\n",buf.st_rdev+'A');
	// printf("%d bytes\n",buf.st_size);
	// printf("%d\n",buf.st_blksize);
	// printf("%d\n",buf.st_blocks);
	// printf("%s\n",ctime(&buf.st_atime));
	// printf("%s\n",ctime(&buf.st_mtime));
	// printf("%s\n",ctime(&buf.st_ctime));
	strftime (buffer,BUFSIZ,"%c",localtime(&buf.st_atime));
	printf ("%s\n",buffer);
	strftime (buffer,BUFSIZ,"%c",localtime(&buf.st_mtime));
	printf ("%s\n",buffer);
	strftime (buffer,BUFSIZ,"%c",localtime(&buf.st_ctime));
	printf ("%s\n",buffer);
	return 0;
}