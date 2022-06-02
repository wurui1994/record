#include <stdio.h>
#include <stdlib.h>

#include <libunwind.h>

void backtrace()
{
    unw_context_t context;
    unw_cursor_t cursor;
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    size_t rip, rsp;
    unw_word_t off;
    char buffer[BUFSIZ];
    do {
        const char* name = !unw_get_proc_name(&cursor, buffer, BUFSIZ, &off) ? buffer : "?";

        unw_get_reg(&cursor, UNW_REG_IP, &rip);
        unw_get_reg(&cursor, UNW_REG_SP, &rsp);

        printf("%s rip: %zx rsp: %zx\n", name, rip, rsp);
    } while (unw_step(&cursor) > 0);
}

void bar() {backtrace();}
void foo() {bar();}

int main()
{
    foo();
}