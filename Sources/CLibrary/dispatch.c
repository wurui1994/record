// Linux: pacman -S libdispatch
// clang -fblocks -ldispatch -lBlocksRuntime dispatch.c
// Windows: https://github.com/gnustep/tools-windows-msvc
// C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\Llvm\x64\bin
// set PATH=%VS2022INSTALLDIR%\VC\Tools\Llvm\x64\bin;%cd%\x64\Debug\bin;%PATH%
// clang -fblocks -Ix64\Debug\include -Lx64\Debug\lib -lobjc -ldispatch dispatch.c
// macOS: clang dispatch.c
#include <stdio.h>
#include <stdlib.h>
#include <dispatch/dispatch.h>
#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char const *argv[])
{
    dispatch_queue_t dq = dispatch_queue_create("com.test", DISPATCH_QUEUE_SERIAL);
    printf("%p\n", dq);
    dispatch_async(dq, ^{
    #ifdef _WIN32
      Sleep(1000);
    #else
      usleep(1000 * 1000); // 线程休眠一秒
    #endif
      puts("hello");
      exit(0);
    });
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(500 * NSEC_PER_MSEC)), dispatch_get_main_queue(), ^{
      // dispatch_resume(dq);
      puts("world");
    });
    dispatch_main();
    return 0;
}
