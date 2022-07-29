// gcc or clang

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if __has_attribute(cleanup)
#define auto_free __attribute__((cleanup(free_ptr)))
#else
#define auto_free
#endif

void free_ptr(void *str)
{
    if (!str)
        return;
    free(*(void **)str);
    printf("auto release\n");
}

int main()
{
    auto_free char *tmp_str = calloc(100, 1);
    strcpy(tmp_str, "hello");
    printf("%s\n", tmp_str);
    return 0;
}