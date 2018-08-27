#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

//无BOM,MSVC2017对特定中文字符会报错
//加BOM后,MSVC2017使用libiconv不正常

int main(int argc, char **argv)
{
	/* 目的编码, TRANSLIT：遇到无法转换的字符就相近字符替换
遇到无法转换字符跳过*/
	//char *encTo = "UNICODE//TRANSLIT";
	char *encTo = "gb2312";
	/* 源编码 */
	char *encFrom = "UTF-8";

	/* 获得转换句柄
	*@param encTo 目标编码方式
	*@param encFrom 源编码方式
	*
	* */
	iconv_t cd = iconv_open(encTo, encFrom);
	if (cd == (iconv_t)-1)
	{
		perror("iconv_open");
	}

	/* 需要转换的字符串 */
	char inbuf[1024] = "abcdef哈哈哈哈";
	puts(inbuf);
	//return 0;
	size_t srclen = strlen(inbuf);
	/* 打印需要转换的字符串的长度 */
	printf("srclen=%d\n", srclen);

	/* 存放转换后的字符串 */
	size_t outlen = 1024;
	char* outbuf = (char*)malloc(outlen);
	memset(outbuf, 0, outlen);

	/* 由于iconv()函数会修改指针，所以要保存源指针 */
	char *srcstart = inbuf;
	char *tempoutbuf = outbuf;

	/* 进行转换
	*@param cd iconv_open()产生的句柄
	*@param srcstart 需要转换的字符串
	*@param srclen 存放还有多少字符没有转换
	*@param tempoutbuf 存放转换后的字符串
	*@param outlen 存放转换后,tempoutbuf剩余的空间
	*
	* */
	size_t ret = iconv(cd, &srcstart, &srclen, &tempoutbuf, &outlen);
	if (ret == -1)
	{
		perror("iconv");
	}
	printf("inbuf=%s, srclen=%d, outbuf=%s, outlen=%d\n", inbuf, srclen, outbuf, outlen);
	int i = 0;
	for (i = 0; i<strlen(outbuf); i++)
	{
		printf("%02X ", (unsigned char)outbuf[i]);
	}
	/* 关闭句柄 */
	iconv_close(cd);
	free(outbuf);
	return 0;
}