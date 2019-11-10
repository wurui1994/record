
#include <stdio.h>
#include <stdlib.h>

#include <uv.h>

#pragma comment(lib, "uv")
//
typedef double (*power_func)(double a, double b);
//
int main()
{
	uv_lib_t *lib = (uv_lib_t *)malloc(sizeof(uv_lib_t));
#ifdef __APPLE__
	char lib_name[] = "libm.dylib";
#elif defined(_WIN32)
	char lib_name[] = "msvcrt";
#else
	char lib_name[] = "libm.so";
#endif
	puts(lib_name);
	if (uv_dlopen(lib_name, lib))
	{
		fprintf(stderr, "Error: %s\n", uv_dlerror(lib));
		return -1;
	}
	power_func power;
	if (uv_dlsym(lib, "pow", (void **)&power))
	{
		fprintf(stderr, "dlsym error: %s\n", uv_dlerror(lib));
	}
	else
	{
		printf("%f\n", power(2, 3));
	}
	uv_dlclose(lib);
	return 0;
}