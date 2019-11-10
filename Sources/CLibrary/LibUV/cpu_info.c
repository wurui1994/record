#include <stdio.h>
#include <uv.h>

#pragma comment(lib, "uv")

int main()
{
	uv_cpu_info_t *info = NULL;
	int cpu_count = 0;
	uv_cpu_info(&info, &cpu_count);
	printf("CPU Number:%d\n", cpu_count);
	printf("Model:%s\n", info->model);
	printf("Speed:%dMHz\n", info->speed);
	uv_free_cpu_info(info, cpu_count);
	return 0;
}