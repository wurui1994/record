#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
// #include <unistd.h>  
// #include <fcntl.h>  
#include <sys/stat.h>  
#include <locale.h>  
  
/** 
 * DESCRIPTION: 实现由utf8编码到gbk编码的转换 
 * 
 * Input: gbkStr,转换后的字符串;  srcStr,待转换的字符串; maxGbkStrlen, gbkStr的最 
 大长度 
 * Output: gbkStr 
 * Returns: -1,fail;>0,success 
 * 
 */  
int utf82gbk(char *gbkStr, const char *srcStr, int maxGbkStrlen) {  
    if (NULL == srcStr) {  
        printf("Bad Parameter1\n");  
        return -1;  
    }  
  
    //首先先将utf8编码转换为unicode编码  
    if (NULL == setlocale(LC_ALL, ".936")) //设置转换为unicode前的码,当前为utf8编码  
    {  
        printf("Bad Parameter2\n");  
        return -1;  
    }  
  
    int unicodeLen = mbstowcs(NULL, srcStr, 0); //计算转换后的长度  
    if (unicodeLen <= 0) {  
        printf("Can not Transfer!!!\n");  
        return -1;  
    }  
    wchar_t *unicodeStr = (wchar_t *) calloc(sizeof(wchar_t), unicodeLen + 1);  
    mbstowcs(unicodeStr, srcStr, strlen(srcStr)); //将utf8转换为unicode  
    
    printf("%s\n",unicodeStr);
  
    //将unicode编码转换为gbk编码  
    if (NULL == setlocale(LC_ALL, "chs")) //设置unicode转换后的码,当前为gbk  
    {  
        printf("Bad Parameter3\n");  
        return -1;  
    }  
    int gbkLen = wcstombs(NULL, unicodeStr, 0); //计算转换后的长度  
    if (gbkLen <= 0) {  
        printf("Can not Transfer!!!\n");  
        return -1;  
    } else if (gbkLen >= maxGbkStrlen) //判断空间是否足够  
            {  
        printf("Dst Str memory not enough\n");  
        return -1;  
    }  
    wcstombs(gbkStr, unicodeStr, gbkLen);  
    gbkStr[gbkLen] = 0; //添加结束符  
    free(unicodeStr);  
    return gbkLen;  
}  
  
int main(void) 
{  
    char *s = "中国";  
    // int fd = open("test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);  
    char buf[10];  
    utf82gbk(buf, s, sizeof(buf)); 
    printf("%s\n",buf);
    // write(fd, buf, strlen(buf));  
    // close(fd);  
  
    return 1;  
}  