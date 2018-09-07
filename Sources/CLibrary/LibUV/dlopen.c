#include <uv.h>
#include <stdlib.h>
//
typedef double (*power_func)(double a, double b);
//
int main()
{
	uv_lib_t *lib = (uv_lib_t *)malloc(sizeof(uv_lib_t));
#ifdef _WIN32
	char lib_name[] = "msvcrt";
#else
	char lib_name[] = "libm-2.28.so";
#endif
	if (uv_dlopen(lib_name, lib))
	{
		fprintf(stderr, "Error: %s\n", uv_dlerror(lib));
		return;
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