// gcc or clang

#include <stdio.h>
#include <stdlib.h>

#define auto_free __attribute__ (( cleanup(free_ptr) ))

__attribute__((always_inline))
inline void free_ptr(void* str) 
{
    if( !str ) return;
    free( *(void**)str );
    printf("auto release\n");
}

int main()
{
    auto_free char* tmp_str = calloc(100,1);
    return 0;
}