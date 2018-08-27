#ifndef _DNS_H
#define _DNS_H

#include<event2/dns.h>
#include<event2/util.h>
#include<event2/event.h>
#include<map>
#include<string>
#include"url.h"

using namespace std;

extern map < string, string > host_ip_map;
extern pthread_mutex_t map_lock;

typedef struct {
	Url *uu;
	int *pp;
	struct event_base *bb;
} dns_cb_arg;

void dns_callback(int errcode, struct evutil_addrinfo *addr, void *ptr)
{
	dns_cb_arg *arg = (dns_cb_arg *) ptr;
	Url *myurl = arg->uu;
	//printf("DNS回调:%s\n",myurl->domain);
	if (errcode) {
		//printf("DNS解析时发现错误：%s -> %s\n", myurl->host, evutil_gai_strerror(errcode));
	} else {
		struct evutil_addrinfo *ai;
		for (ai = addr; ai->ai_next; ai = ai->ai_next) {
		}		/*取最后一个IP */
		char buf[128];
		const char *s = NULL;
		if (addr->ai_family == AF_INET) {
			struct sockaddr_in *sin =
			    (struct sockaddr_in *)ai->ai_addr;
			s = evutil_inet_ntop(AF_INET, &sin->sin_addr, buf, 128);	/*从套接口内部数据类型转换为点分十进制 */
		} else if (addr->ai_family == AF_INET6) {
			struct sockaddr_in6 *sin6 =
			    (struct sockaddr_in6 *)ai->ai_addr;
			s = evutil_inet_ntop(AF_INET6, &sin6->sin6_addr, buf,
					     128);
		}
		if (s) {
			//printf("给%s赋予IP:%s\n",myurl->domain,s);
			strcpy(myurl->ip, s);
			char *host = strdup(myurl->domain);
			char *ip = strdup(myurl->ip);
			pthread_mutex_lock(&map_lock);
			host_ip_map[host] = ip;
			pthread_mutex_unlock(&map_lock);
		}
		evutil_freeaddrinfo(addr);
	}
	//printf("DNS回调成功|%s||%s|\n",myurl->domain,myurl->ip);
	//freeURL(myurl);
	if (--(*(arg->pp)) == 0) {
		//printf("event_base循环将退出\n");
		event_base_loopexit(arg->bb, NULL);	/*不设置超时,退出循环检测 */
	}
}

void dnsParse(Url ** ptr, int count)
{
	struct event_base *base;
	struct evdns_base *dnsbase;
	//sleep(3);             //相比于下载内面，DNS解析太快。所以多让DNS休息一下，把CPU让给下载内面的程序
	//printf("开始批量DNS解析\n");
	int n_pending_requests = 0;
	base = event_base_new();	/*初始化event base */
	if (!base) {
		perror("event_base_new");
		return;
	}
	dnsbase = evdns_base_new(base, 1);	/*1表示根据你的操作系统进行默认的dns配置，0则不进行任何配置 */
	if (!dnsbase) {
		perror("evdns_base_new");
		return;
	}

	int i;
	for (i = 0; i < count; ++i) {
		struct evutil_addrinfo hints;
		struct evdns_getaddrinfo_request *req;
		memset(&hints, 0, sizeof(hints));

		hints.ai_family = AF_UNSPEC;	/*不具体指定地址簇，即AF_INET和AF_INET6都可以 */
		/*如果不设置socktype，对于每个地址我们将得到两个地址，一个是TCP的，一个是UDP的。当然这不是我们想要的 */
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		++n_pending_requests;
		dns_cb_arg *arg = (dns_cb_arg *) calloc(sizeof(dns_cb_arg), 1);
		arg->uu = ptr[i];
		arg->pp = &n_pending_requests;
		arg->bb = base;
		//printf("开始发送DNS请求%s\n",arg->uu->domain);
		req =
		    evdns_getaddrinfo(dnsbase, arg->uu->domain, NULL, &hints,
				      dns_callback, arg);
		if (req == NULL) {
			fprintf(stderr, "DNS请求：%s立即返回\n",
				ptr[i]->domain);
		}
	}
	if (n_pending_requests)
		event_base_dispatch(base);

	//printf("将释放event_base和dns_base\n");
	evdns_base_free(dnsbase, 0);
	event_base_free(base);
}

#endif
