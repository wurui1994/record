#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main()
{
   
   int len;
   char *pmbnull  = NULL;
   char *pmb = "我们";
   // char *pmb = (char *)malloc( MB_CUR_MAX );
   // wchar_t *pwc = L"转";
   wchar_t *pwcs = (wchar_t *)malloc( sizeof( wchar_t ));

   // printf("转换为多字节字符串\n");
   
   // len = wcstombs( pmb, pwc, MB_CUR_MAX);
   // printf("被转换的字符 %d\n", len);
   // printf("%s\n", pmb);
   // printf("第一个多字节字符的十六进制值：%#.4x\n", pmb);
   
   // printf("转换回宽字符字符串\n");
   setlocale(LC_ALL, "C");
   len = mbstowcs( pwcs, pmb, MB_CUR_MAX);
   printf("被转换的字符 %d\n", len);
   setlocale(LC_ALL, "chs");
   printf("%ws\n", pwcs);
   printf("第一个宽字符的十六进制值：%#.4x\n\n", pwcs);
   
   return(0);
}