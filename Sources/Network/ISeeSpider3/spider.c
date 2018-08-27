#include<pthread.h>
#include"bloom.h"
#include"url.h"
#include"dns.h"
#include"http.h"

#define MAX_QUEUE_SIZE 300

map < string, string > host_ip_map;
queue < Url * >url_queue;
struct epoll_event ev, events[10];	//ev用于注册事件，events数组用于回传要处理的事件
int epfd;
pthread_mutex_t map_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;

void putlinks2queue(char *links[], int count);
void addurl2queue(Url * url);
int CreateThread(void *(*start_routine) (void *), void *arg, pthread_t * thread,
		 pthread_attr_t * pAttr);

int main(int argc, char *argv[])
{
	int i, n;
	if (argc < 2) {
		printf
		    ("You should provide some entry urls in the command line\n"
		     "For example:%s www.sogou.com/ www.cnblogs.com/cate/c\n",
		     argv[0]);
		return 0;
	}
	chdir("downpage");
	putlinks2queue(argv + 1, argc - 1);	/*把用户命令行提供的link放入待爬取url队列 */

	epfd = epoll_create(50);	//生成用于处理accept的epoll专用文件描述符，最多监听256个事件
	n = url_queue.size() < 50 ? url_queue.size() : 50;	/*最多同时放出去50条socket连接 */
	for (i = 0; i < n; ++i) {
		pthread_mutex_lock(&queue_lock);
		Url *url = url_queue.front();
		url_queue.pop();
		pthread_mutex_unlock(&queue_lock);
		//printf("从url队列中读出：%s%s-->%s\n",url.domain,url.path,url.ip);
		int sockfd;
		//printf("将要发送连接请求\n");
		int rect = buildConnect(&sockfd, url->ip);	/*发出connect请求 */
		setnoblocking(sockfd);	/*设置sockfd非阻塞模式 */
		//printf("将要发送http request\n");
		rect = sendRequest(url, sockfd);	/*发送http request */
		Ev_arg *arg = (Ev_arg *) calloc(sizeof(Ev_arg), 1);
		arg->url = url;
		arg->fd = sockfd;
		ev.data.ptr = arg;
		ev.events = EPOLLIN | EPOLLET;	//设置要处理的事件类型。可读，边缘触发
		printf("将要把%d[%s%s]放入epoll\n", sockfd, url->domain,
		       url->path);
		epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);	//注册ev
	}

	while (1) {
		n = epoll_wait(epfd, events, 10, 2000);	/*等待sockfd可读，即等待http response */
		printf("有%d个sockfd准备就绪\n", n);
		for (i = 0; i < n; ++i) {
			Ev_arg *arg = (Ev_arg *) (events[i].data.ptr);
			//printf("%d准备就绪\n",arg->fd);
			CreateThread(recvResponse, arg, NULL, NULL);
		}
	}
	close(epfd);
}

/*把超链接放入待爬取url队列*/
void putlinks2queue(char *links[], int count)
{
	int i = 0, num = 0;
	Url **urls;
	urls = (Url **) calloc(count, sizeof(Url *));
	for (i = 0; i < count; ++i) {
		if (links[i] == NULL)
			continue;
		char *h = (char *)calloc(MAX_LINK_LEN, 1);
		char *r = (char *)calloc(MAX_LINK_LEN, 1);
		char *iipp = (char *)calloc(20, 1);
		pretreatLink(links[i]);
		if (links[i] == NULL)
			continue;
		getHRfromlink(links[i], h, r);
		//printf("h=%s\tr=%s\n",h,r);
		if (bloomDomain(h)) {	/*domain出现过 */
			if (bloomPath(r)) {	/*path出现过，则忽略此link */
				free(h);
				free(r);
				free(iipp);
				continue;
			} else {	/*path没有出现 */
				Url *tmp = (Url *) calloc(1, sizeof(Url));
				tmp->domain = h;
				tmp->path = r;

				map < string, string >::const_iterator itr;
				itr = host_ip_map.find(h);	/*查找domain在map是否有记录 */
				if (itr == host_ip_map.end()) {	/*domain不在map中 */
					tmp->ip = iipp;
					urls[num++] = tmp;	/*放入urls，等待批量DNS解析 */
					//printf("|%s||%s||%s|被放入DNS解析队列\n",urls[num-1]->domain,urls[num-1]->ip,urls[num-1]->path);
				} else {	/*domain在map中 */
					tmp->ip = strdup(host_ip_map[h].c_str());	/*直接从map取出与domain对应的ip */
					//printf("从map中直接取出ip后：%s\t%s\t%s\n",tmp->domain,tmp->ip,tmp->path);
					addurl2queue(tmp);	/*把url放入待爬取队列 */
					continue;
				}
			}
		} else {	/*domain没有出现过 */
			Url *tmp = (Url *) calloc(1, sizeof(Url));
			tmp->domain = h;
			tmp->path = r;
			tmp->ip = iipp;
			urls[num++] = tmp;	/*放入urls，等待批量DNS解析 */
			//printf("|%s||%s||%s|被放入DNS解析队列\n",urls[num-1]->domain,urls[num-1]->ip,urls[num-1]->path);
		}
	}

	dnsParse(urls, num);	/*批量DNS解析 */

	for (i = 0; i < num; ++i)	/*经DNS解析得到ip后，放入url队列 */
		addurl2queue(urls[i]);
	//printf("把links放入url_queue完毕\n");    
	//free(urls);
}

/*把url放入待爬取队列*/
void addurl2queue(Url * url)
{
	if (url == NULL || url->domain == NULL || strlen(url->domain) == 0
	    || url->path == NULL || strlen(url->path) == 0 || url->ip == NULL
	    || strlen(url->ip) == 0) {
		fprintf(stderr,
			"Url内容不完整。domain=%s\tpath=%s\tip=%s\n",
			url->domain, url->path, url->ip);
		exit(1);
	}
	//fprintf(stderr,"Url内容完整。domain=%s\tpath=%s\tip=%s\n",url->domain,url->path,url->ip);
	if (url_queue.size() >= MAX_QUEUE_SIZE)	/*如果队列已满，就忽略譔url */
		return;
	pthread_mutex_lock(&queue_lock);
	url_queue.push(url);
	pthread_mutex_unlock(&queue_lock);
	//printf("%s%s已放入待爬取队列\n",url->domain,url->path);
}

/*创建分离线程*/
int CreateThread(void *(*start_routine) (void *), void *arg, pthread_t * thread,
		 pthread_attr_t * pAttr)
{
	pthread_attr_t thr_attr;
	if (pAttr == NULL) {
		pAttr = &thr_attr;
		pthread_attr_init(pAttr);	/*初始化线程属性 */
		pthread_attr_setstacksize(pAttr, 1024 * 1024);	/*1 M的堆栈 */
		pthread_attr_setdetachstate(pAttr, PTHREAD_CREATE_DETACHED);	/*线程分离，主线程不需要等子线程结束 */
	}
	pthread_t tid;
	if (thread == NULL) {
		thread = &tid;
	}
	int r = pthread_create(thread, pAttr, start_routine, arg);
	pthread_attr_destroy(pAttr);	/*销毁线程属性 */
	return r;
}
