// tcc -run mycat.c < mycat.c > test.txt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int n;
	char buf[BUFSIZ];
	while ((n = read(0, buf, BUFSIZ)) > 0)
		if (write(1, buf, n) != n)
			fprintf(stderr, "write error");
	if (n < 0)
		fprintf(stderr, "read error");

	exit(0);
}
