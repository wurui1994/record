#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 50

int main()
{
   size_t ret;
   char *MB = (char *)malloc( BUFFER_SIZE );
   wchar_t *WC = L"http://www.w3cschool.cc";

   /* ×ª»»¿í×Ö·û×Ö·û´® */
   ret = wcstombs(MB, WC, BUFFER_SIZE);
   
   printf("Òª×ª»»µÄ×Ö·ûÊý = %u\n", ret);
   printf("¶à×Ö½Ú×Ö·û = %s\n\n", MB);
   
   return(0);
}