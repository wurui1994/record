#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char line[BUFSIZ];
	char *filename = argv[0];
	FILE *fp = fopen(filename, "rt");
	while (!feof(fp))
	{
		memset(line,0,BUFSIZ);
		fgets(line, BUFSIZ, fp);
		printf(line);
	}
}