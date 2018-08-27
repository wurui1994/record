//uv和curl的下载器修改版
//参考来源：https://curl.haxx.se/libcurl/c/multi-uv.html
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <curl/curl.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int MAX_HANDLE = 32;
int offset = 0;
int active = 0;

using namespace std;


vector<string> vec;

uv_loop_t *loop;
CURLM *curl_handle;
uv_timer_t timeout;

typedef struct curl_context_s {
	uv_poll_t poll_handle;
	curl_socket_t sockfd;
} curl_context_t;

#include <sys/stat.h>
int exist(const char *name)
{
  struct stat   buffer;
  return (stat (name, &buffer) == 0);
}

static curl_context_t* create_curl_context(curl_socket_t sockfd)
{
	curl_context_t *context;

	context = (curl_context_t *)malloc(sizeof *context);

	context->sockfd = sockfd;

	uv_poll_init_socket(loop, &context->poll_handle, sockfd);
	context->poll_handle.data = context;

	return context;
}

static void curl_close_cb(uv_handle_t *handle)
{
	curl_context_t *context = (curl_context_t *)handle->data;
	free(context);
}

static void destroy_curl_context(curl_context_t *context)
{
	uv_close((uv_handle_t *)&context->poll_handle, curl_close_cb);
}

static void add_download(const char *url, int num)
{
	//    struct FtpFile *ftpfile = (struct FtpFile *)calloc(1,sizeof(struct FtpFile));
	FILE *file;
	CURL *handle;

	char filename[BUFSIZ];
	snprintf(filename, BUFSIZ, "%d.data", num);

	if(exist(filename)) return;
    
	file = fopen(filename, "wb");
	if (!file) {
		fprintf(stderr, "Error opening %s\n", filename);
		return;
	}

	handle = curl_easy_init();

	//curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(handle, CURLOPT_PRIVATE, file);
	curl_easy_setopt(handle, CURLOPT_URL, url);

	curl_multi_add_handle(curl_handle, handle);
	fprintf(stderr, "Added download %s -> %s\n", url, filename);
}

static void check_multi_info(void)
{
	char *done_url;
	CURLMsg *message;
	int pending;
	CURL *easy_handle;
	FILE* file;

	while ((message = curl_multi_info_read(curl_handle, &pending))) {
		switch (message->msg) {
		case CURLMSG_DONE:
			/* Do not use message data after calling curl_multi_remove_handle() and
			curl_easy_cleanup(). As per curl_multi_info_read() docs:
			"WARNING: The data the returned pointer points to will not survive
			calling curl_multi_cleanup, curl_multi_remove_handle or
			curl_easy_cleanup." */
			easy_handle = message->easy_handle;

			curl_easy_getinfo(easy_handle, CURLINFO_EFFECTIVE_URL, &done_url);
			curl_easy_getinfo(easy_handle, CURLINFO_PRIVATE, &file);
			printf("%s DONE\n", done_url);

			curl_multi_remove_handle(curl_handle, easy_handle);
			curl_easy_cleanup(easy_handle);
			if (file) {
				fclose(file);
				active--;
				if (offset < vec.size() && active<MAX_HANDLE)
				{
					add_download(vec[offset].c_str(), offset);
					offset++;
					active++;
				}
			}
			break;

		default:
			fprintf(stderr, "CURLMSG default\n");
			break;
		}
	}
}

static void curl_perform(uv_poll_t *req, int status, int events)
{
	int running_handles;
	int flags = 0;
	curl_context_t *context;

	if (events & UV_READABLE)
		flags |= CURL_CSELECT_IN;
	if (events & UV_WRITABLE)
		flags |= CURL_CSELECT_OUT;

	context = (curl_context_t *)req->data;

	curl_multi_socket_action(curl_handle, context->sockfd, flags,
		&running_handles);

	check_multi_info();
}

static void on_timeout(uv_timer_t *req)
{
	int running_handles;
	curl_multi_socket_action(curl_handle, CURL_SOCKET_TIMEOUT, 0,
		&running_handles);
	check_multi_info();
}

static int start_timeout(CURLM *multi, long timeout_ms, void *userp)
{
	if (timeout_ms < 0 && offset == vec.size()) {
		uv_timer_stop(&timeout);
	}
	else {
		if (timeout_ms == 0)
			timeout_ms = 1; /* 0 means directly call socket_action, but we'll do it
							in a bit */
		uv_timer_start(&timeout, on_timeout, timeout_ms, 0);
	}
	return 0;
}

static int handle_socket(CURL *easy, curl_socket_t s, int action, void *userp,
	void *socketp)
{
	curl_context_t *curl_context;
	int events = 0;

	switch (action) {
	case CURL_POLL_IN:
	case CURL_POLL_OUT:
	case CURL_POLL_INOUT:
		curl_context = socketp ?
			(curl_context_t *)socketp : create_curl_context(s);

		curl_multi_assign(curl_handle, s, (void *)curl_context);

		if (action != CURL_POLL_IN)
			events |= UV_WRITABLE;
		if (action != CURL_POLL_OUT)
			events |= UV_READABLE;

		uv_poll_start(&curl_context->poll_handle, events, curl_perform);
		break;
	case CURL_POLL_REMOVE:
		if (socketp) {
			uv_poll_stop(&((curl_context_t*)socketp)->poll_handle);
			destroy_curl_context((curl_context_t*)socketp);
			curl_multi_assign(curl_handle, s, NULL);
		}
		break;
	default:
		abort();
	}

	return 0;
}


int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		printf("%Usage:%s <urls_files>.\n", argv[0]);
		return 0;
	}
	ifstream ifs(argv[1]);
	string s;

	while (getline(ifs, s))
	{
		// s.pop_back();
		vec.push_back(s);
	}
	ifs.close();

	int base = 0;

label:
	loop = uv_default_loop();

	if (curl_global_init(CURL_GLOBAL_ALL)) {
		fprintf(stderr, "Could not init curl\n");
		return 1;
	}

	uv_timer_init(loop, &timeout);

	curl_handle = curl_multi_init();
	curl_multi_setopt(curl_handle, CURLMOPT_SOCKETFUNCTION, handle_socket);
	curl_multi_setopt(curl_handle, CURLMOPT_TIMERFUNCTION, start_timeout);

	if (vec.size() < MAX_HANDLE)
	{
		MAX_HANDLE = vec.size();
	}
	for (int i = 0; i<MAX_HANDLE; i++)
	{
		add_download(vec[base + i].c_str(), base + i);
		offset++;
		active++;
	}

	base = offset;

	uv_run(loop, UV_RUN_DEFAULT);

	curl_multi_cleanup(curl_handle);

	//如果没有下完,回到开头继续下载
	if(offset < vec.size()) goto label;

	return 0;
}
