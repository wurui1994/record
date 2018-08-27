#include <stdio.h>
#include <time.h>

float fps(int n_frame, void(*render)(void))
{
	clock_t start, finish;
	int i;
	float fps;
	printf("Performing benchmark, please wait");
	start = clock();
	for (i = 0; i < n_frame; i++) {
		render();
	}
	printf("done\n");
	finish = clock();
	fps = 1.0*(n_frame) / (finish - start)*CLOCKS_PER_SEC;
	return fps;
}