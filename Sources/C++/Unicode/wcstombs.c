#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

int main()
{
   size_t ret;
   char *MB = (char *)malloc( BUFFER_SIZE );
   wchar_t *WC = L"http://www.w3cschool.cc";

   /* 转换宽字符字符串 */
   ret = wcstombs(MB, WC, BUFFER_SIZE);
   
   printf("要转换的字符数 = %u\n", ret);
   printf("多字节字符 = %s\n\n", MB);
   
   return(0);
}