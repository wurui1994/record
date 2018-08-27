#ifndef _URL_H
#define _URL_H

#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<regex.h>

#define MAX_LINK_LEN 128	/*长度大于MAX_LINK_LEN的超链接忽略 */

typedef struct {
	char *domain;
	char *ip;
	char *path;
} Url;

extern void putlinks2queue(char *links[], int count);

void freeUrl(Url * url)
{
	free(url->domain);
	free(url->ip);
	free(url->path);
	//free(url);
}

/*去掉开头的http[s]，如果是以“/”开头的，就把它接在domain后面*/
char *patchlink(char *link, char *domain)
{
	int len1 = strlen(link);
	int len2 = strlen(domain);
	char *rect;
	int i;
	if (strncmp(link, "http", 4) == 0) {
		int llen;
		if (strncmp(link, "https", 5) == 0)
			llen = 8;
		else
			llen = 7;
		rect = (char *)malloc(len1 - llen + 1);
		for (i = 0; i < len1 - llen; ++i)
			rect[i] = link[i + llen];
		rect[len1 - llen] = '\0';
	} else if (strncmp(link, "/", 1) == 0) {
		rect = (char *)malloc(len1 + len2 + 1);
		for (i = 0; i < len2; ++i)
			rect[i] = domain[i];
		for (i = 0; i < len1; ++i)
			rect[i + len2] = link[i];
		rect[len1 + len2] = '\0';
		//printf("在函数中补全之后的超接：|%s|\n",rect);
	} else {		/*既不是以http[s]开头，也不是以“/”开头，则返回NULL */
		return NULL;
	}

	return rect;
}

/*把超链接末尾的/去掉,长度大于MAX_LINK_LEN的超链接不爬取，把link设为NULL*/
void pretreatLink(char *link)
{
	if (link == NULL)
		return;
	//printf("预处理之前link=%s\n",link);
	int len = strlen(link);
	if (link[len - 1] == '/')	/*把超链接末尾的/去掉 */
		link[len - 1] = '\0';
	if (strlen(link) > MAX_LINK_LEN) {	/*长度大于128的超链接不爬取，把link设为NULL */
		free(link);
		link = NULL;
	}
	//printf("预处理之后link=%s\n",link);
}

/*获取超链接中资源的路径深度*/
int getDepth(char *link)
{
	int depth = 0;
	int len = strlen(link);
	int i;
	for (i = 0; i < len; ++i) {
		if (link[i] == '/')
			depth++;
	}
	return depth;
}

/*从link中获取host和resource*/
void getHRfromlink(char *link, char *host, char *resource)
{
	//printf("link=%s\n",link);
	char *p = index(link, '/');
	//printf("p=%s\n",p);
	if (p == NULL) {
		strcpy(host, link);
		resource[0] = '/';
		resource[1] = '\0';
	} else {
		int dlen = p - link;
		int plen = strlen(link) - dlen;
		strncpy(host, link, dlen);
		host[dlen] = '\0';
		strcpy(resource, p);
		resource[plen] = '\0';
	}
	//printf("从link得到host=%s\tresource=%s\n",host,resource);
}

/*以url作为文件名，斜线转换为下划线*/
char *link2fn(Url * arg)
{
	int l1 = strlen(arg->domain);
	int l2 = strlen(arg->path);
	char *filename;
	filename = (char *)calloc(l1 + l2 + 1, sizeof(char));
	int i = 0;
	for (; i < l1; ++i)
		filename[i] = arg->domain[i];
	for (i = 0; i < l2; ++i)
		filename[i + l1] = (arg->path[i] == '/' ? '_' : arg->path[i]);
	filename[l1 + l2] = '\0';
	return filename;
}

/*字符串向左平移，直到最后一个空格移到首位为止，返回字符串中还剩多少字符*/
int leftshift(char *buf)
{
	char *p = rindex(buf, ' ');
	if (p == NULL) {	/*空格没有出现，则清空buf，返回0 */
		memset(buf, 0x00, strlen(buf));
		return 0;
	} else {
		int leftlen = p - buf;
		int rightlen = strlen(buf) - leftlen;
		char *tmp = (char *)malloc(rightlen);
		strncpy(tmp, p, rightlen);
		memset(buf, 0x00, strlen(buf));
		strncpy(buf, tmp, rightlen);
		free(tmp);
		return rightlen;
	}
}

/*从字符串中抽取所有的超链接，移除左侧包含所有超链接的最短子串，返回剩余子串的长度*/
int extractLink(char *buf, char *domain)
{
	const char *regex = "href=\"[^ >]*\"";
	regex_t preg;
	const size_t nmatch = 10;
	regmatch_t pm[nmatch];
	if (regcomp(&preg, regex, 0) != 0) {	/*编译正则表达式失败 */
		perror("regcomp");
		exit(1);
	}
	int z, i;
	z = regexec(&preg, buf, nmatch, pm, 0);
	if (z == REG_NOMATCH) {	/*无匹配项 */
		return leftshift(buf);
	} else {		/*有匹配的超链接 */
		char **links = (char **)calloc(nmatch, sizeof(char *));
		for (i = 0; i < nmatch && pm[i].rm_so != -1; ++i) {	/*把超链接都提取出来 */
			int bpos = pm[i].rm_so + 6;
			int epos = pm[i].rm_eo - 2;
			int len = epos - bpos + 1;
			char *tmp;
			tmp = (char *)calloc(len + 1, 1);
			strncpy(tmp, buf + bpos, len);
			tmp[len] = '\0';
			//printf("直接读出的超接：|%s|\n",tmp);
			char *link = patchlink(tmp, domain);
			free(tmp);
			//printf("补全之后的超接：|%s|\n",link);
			links[i] = link;
		}
		putlinks2queue(links, nmatch);
		//free(links);
		return leftshift(buf + pm[nmatch - 1].rm_eo);
	}
}

#endif
