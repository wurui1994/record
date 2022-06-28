#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

// only x64

#ifndef _WIN32
#define INTEL_SYNTAX 1

int add(int a, int b)
{
    return a + b;
}

#ifdef __arm64__
/*
0000000000000000 <_add2>:
       0: ff 43 00 d1   sub     sp, sp, #16
       4: e0 0f 00 b9   str     w0, [sp, #12]
       8: e1 0b 00 b9   str     w1, [sp, #8]
       c: e8 0f 40 b9   ldr     w8, [sp, #12]
      10: e9 0b 40 b9   ldr     w9, [sp, #8]
      14: 00 01 09 0b   add     w0, w8, w9
      18: ff 43 00 91   add     sp, sp, #16
      1c: c0 03 5f d6   ret
*/
asm(
    "_add2:\n"
    "sub sp, sp, #16\n"
    "str w0, [sp, #12]\n"
    "str w1, [sp, #8]\n"
    "ldr w8, [sp, #12]\n"
    "ldr w9, [sp, #8]\n"
    "add w0, w8, w9\n"
    "add sp, sp, #16\n"
    "ret\n");
#define test(name)            \
    int name(int, int);       \
    asm(                      \
        "_" #name ":\n"       \
        "sub sp, sp, #16\n"   \
        "str w0, [sp, #12]\n" \
        "str w1, [sp, #8]\n"  \
        "ldr w8, [sp, #12]\n" \
        "ldr w9, [sp, #8]\n"  \
        "add w0, w8, w9\n"    \
        "add sp, sp, #16\n"   \
        "ret\n");
#else

#if INTEL_SYNTAX
asm(".intel_syntax noprefix\n"
    "_add2:\n"
    "push rbp\n"
    "mov rbp, rsp\n"
    "mov dword ptr [rbp - 4], edi\n"
    "mov dword ptr [rbp - 8], esi\n"
    "mov eax, dword ptr [rbp - 4]\n"
    "add eax, dword ptr [rbp - 8]\n"
    "pop rbp\n"
    "ret");
#else
asm(
    "_add2:\n"
    "pushq   %rbp\n"
    "movq    %rsp, %rbp\n"
    "movl    %edi, -4(%rbp)\n"
    "movl    %esi, -8(%rbp)\n"
    "movl    -4(%rbp), %eax\n"
    "addl    -8(%rbp), %eax\n"
    "popq    %rbp\n"
    "retq");
#endif
#endif

#ifdef __arm64__
test(add3);
#endif

#endif

typedef int add4(int, int);

// shelcode string to ptr [arm64 shellcode has null-byte can't use strlen !]
void *execCode(char *shellcode, size_t len)
{
#ifdef _WIN32
    void *address_shellcode = VirtualAlloc(0, len + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(address_shellcode, shellcode, len);
    return address_shellcode;
#else
    void *ptr = mmap(0, 0x1000, PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE | MAP_JIT, -1, 0);
    if (ptr == MAP_FAILED)
        perror("mmap");
    void *dst = memcpy(ptr, shellcode, len);
    int status = mprotect(ptr, 0x1000, PROT_EXEC | PROT_READ);
    if (status == -1)
        perror("mprotect");
    return ptr;
#endif
}

#ifdef _WIN32
/*
0000000000000000 <add>:
0: 89 54 24 10                   movl    %edx, 16(%rsp)
4: 89 4c 24 08                   movl    %ecx, 8(%rsp)
8: 8b 44 24 10                   movl    16(%rsp), %eax
c: 8b 4c 24 08                   movl    8(%rsp), %ecx
10: 03 c8                        addl    %eax, %ecx
12: 8b c1                        movl    %ecx, %eax
14: c3                           retq
*/
char shellcode_string[] = "\x89\x54\x24\x10\x89\x4c\x24\x08\x8b\x44\x24\x10\x8b\x4c\x24\x08\x03\xc8\x8b\xc1\xc3";
#else
#ifdef __arm64__
// https://github.com/maxcompston/arm64_shellcode
// https://github.com/daem0nc0re/macOS_ARM64_Shellcode
// arm64 can only use System Call ???
// svc #1337
// arm64 shellcode has null-byte can't use strlen !
/*
0: ff 43 00 d1   sub     sp, sp, #16
4: e0 0f 00 b9   str     w0, [sp, #12]
8: e1 0b 00 b9   str     w1, [sp, #8]
c: e8 0f 40 b9   ldr     w8, [sp, #12]
10: e9 0b 40 b9   ldr     w9, [sp, #8]
14: 00 01 09 0b   add     w0, w8, w9
18: ff 43 00 91   add     sp, sp, #16
1c: c0 03 5f d6   ret
*/

char shellcode_string[] = "\xff\x43\x00\xd1\xe0\x0f\x00\xb9\xe1\x0b\x00\xb9\xe8\x0f\x40\xb9\xe9\x0b\x40\xb9\x00\x01\x09\x0b\xff\x43\x00\x91\xc0\x03\x5f\xd6";
#else
/*
0000000100003c10 <_add>:
100003c10: 55                           pushq   %rbp
100003c11: 48 89 e5                     movq    %rsp, %rbp
100003c14: 89 7d fc                     movl    %edi, -4(%rbp)
100003c17: 89 75 f8                     movl    %esi, -8(%rbp)
100003c1a: 8b 45 fc                     movl    -4(%rbp), %eax
100003c1d: 03 45 f8                     addl    -8(%rbp), %eax
100003c20: 5d                           popq    %rbp
100003c21: c3                           retq
100003c22: 66 2e 0f 1f 84 00 00 00 00 00        nopw    %cs:(%rax,%rax)
100003c2c: 0f 1f 40 00                  nopl    (%rax)
*/

char shellcode_string[] = "\x55\x48\x89\xe5\x89\x7d\xfc\x89\x75\xf8\x8b\x45\xfc\x03\x45\xf8\x5d\xc3\x00"; //\x2e\x66\x0f\x1f\x04\x00\x0f\x1f\x00";
#endif
#endif

int main()
{
#ifndef _WIN32
    int add2(int a, int b);
    puts("hello");

    int x = add2(1, 2);
    int y = add2(3, 4);
    printf("%d %d\n", x, y);

#ifdef __arm64__
    int z = add3(5, 8);
    printf("%d\n", z);
#endif
#endif

    void *ptr = execCode(shellcode_string, sizeof(shellcode_string));
    add4 *f = (add4 *)ptr;
    int r = f(7, 8);
    printf("%d\n", r);
}