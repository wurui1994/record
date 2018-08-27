#ifndef _BLOOM_H
#define _BLOOM_H

#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<math.h>
#include<string.h>
#include<rpc/des_crypt.h>	/*for ecd_crypt */
#include<limits.h>		/*for INT_MAX */
#include<errno.h>
#include<string>
using namespace std;

#define MAX_URLPATH_NUM	1000000	/*url path数目的上限(必须是1000的整倍数) */
#define MAX_URLDOMAIN_NUM	(MAX_URLPATH_NUM)/100	/*url domain数目的上限(必须是1000的整倍数) */

//extern int stat(const char *path,struct stat *buf);
int d_table[MAX_URLDOMAIN_NUM] = { 0 };
int p_table[MAX_URLPATH_NUM] = { 0 };

pthread_mutex_t dtlock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ptlock = PTHREAD_MUTEX_INITIALIZER;

int myEncrypt(char *str, char *key)
{
	assert(str != NULL);
	char *cipher = strdup(str);
	ecb_crypt(key, cipher, strlen(str), DES_ENCRYPT);	/*第一次映射函数采用ecb_crypt */
	int i;
	int var = 0;
	int len = strlen(cipher);
	for (i = 0; i < len; i++)
		var = (var * 7 + cipher[i]) % (int)INT_MAX;
	free(cipher);
	return var;
}

/*判断domain是否存在过，如果不存在就把它记入DomainBloomTable中*/
int bloomDomain(char *domain)
{
	//printf("调用bloomDomain\ndomain=%s\n",domain);
	int mod = 32 * MAX_URLDOMAIN_NUM;
	int flag = 0;
	string salt[] = { "Dm", "VB", "ui", "LK", "uj", "RD", "we", "fc" };
	int f[8] = { 0 };
	int g[8] = { 0 };
	int i;
	pthread_mutex_lock(&dtlock);
	for (i = 0; i < 8; i++) {
		char *key;
		key = strdup(salt[i].c_str());
		f[i] = myEncrypt(domain, key);
		free(key);
		srand(f[i]);
		g[i] = rand() % mod;	/*第一次映射函数采用rand */
		int index = g[i] / 32;
		int pos = g[i] % 32;
		if (d_table[index] & (0x80000000 >> pos))
			flag++;
		else
			d_table[index] |= (0x80000000 >> pos);
	}
	pthread_mutex_unlock(&dtlock);
	if (flag == 8)
		return 1;	//已存在则返回true
	return 0;
}

/*判断path是否存在过，如果不存在就把它记入PathBloomTable中*/
int bloomPath(char *path)
{
	//printf("调用bloomPath\npath=%s\n",path);
	int mod = 32 * MAX_URLPATH_NUM;
	int flag = 0;
	string salt[] = { "Dm", "VB", "ui", "LK", "uj", "RD", "we", "fc" };
	int f[8] = { 0 };
	int g[8] = { 0 };
	int i;
	pthread_mutex_lock(&ptlock);
	for (i = 0; i < 8; i++) {
		char *key;
		key = strdup(salt[i].c_str());
		f[i] = myEncrypt(path, key);
		free(key);
		srand(f[i]);
		g[i] = rand() % mod;	/*第一次映射函数采用rand */
		int index = g[i] / 32;
		int pos = g[i] % 32;
		if (p_table[index] & (0x80000000 >> pos))
			flag++;
		else
			p_table[index] |= (0x80000000 >> pos);
	}
	pthread_mutex_unlock(&ptlock);
	if (flag == 8)
		return 1;	//已存在则返回true
	return 0;
}

#endif
