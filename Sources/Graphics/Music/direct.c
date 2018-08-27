#include <windows.h>
#include <stdio.h>
//
#define Length(x) sizeof(x) / sizeof(x[0])
//
typedef unsigned char byte;
typedef struct
{
	byte high, quality, length;
} music;

int n[4] = {125, 250, 500, 1000};
//
int a[7] = {262, 294, 330, 349, 392, 440, 494};
int b[7] = {523, 587, 659, 698, 784, 880, 988};
int c[7] = {1047, 1175, 1319, 1397, 1568, 1760, 1979};
//
// int total[]= {
// 233,232,252,262,312,312,262,253,252,262,254,233,232,252,262,312,312,262,253,252,
// 262,254,233,232,252,262,312,312,262,253,252,262,254,233,232,252,262,312,312,262,
// 253,252,262,254,233,232,252,262,312,312,262,253,252,262,254,233,232,252,262,312,
// 312,262,253,252,262,254,233,232,252,262,312,312,262,253,252,262,254
// };

// void write()
// {
// char filename[64]="music.txt";
// FILE* fp=fopen(filename,"wb");
// int f,t;
// for(int i=0; i<Length(total); i++) {
// fprintf(fp,"%d ",total[i]);
// }
// fclose(fp);
// }
//
//
void decode(int total, int *freq, int *time)
{
	int three, two, one;
	three = total / 100;
	two = (total / 10) % 10;
	one = total % 10;
	switch (three)
	{
	case 1:
		*freq = a[two - 1];
		break;
	case 2:
		*freq = b[two - 1];
		break;
	case 3:
		*freq = c[two - 1];
		break;
	}
	*time = n[one - 1];
}
void read()
{
	char filename[64] = "music.txt";
	FILE *fp = fopen(filename, "rb");
	int freq, time, num;
	while (!feof(fp))
	{
		fscanf(fp, "%d ", &num);
		decode(num, &freq, &time);
		printf("(%d %d) ", freq, time);
		Beep(freq, time);
	}
	fclose(fp);
}

//
int main()
{
	//write();
	read();
	//decode();
}