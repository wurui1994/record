/*
* =====================================================================================
*
* Filename: pthread1.c
*
* Description: A Simple program of showing What pthread is
*
* Version: 1.0
* Created: 03/10/2009 08:53:48 PM
* Revision: none
* Compiler: gcc
*
* Author: Futuredaemon (BUPT), gnuhpc@gmail.com
* Company: BUPT_UNITED
*
* =====================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *threadid)
{
	int tid;
	tid = (int)threadid;
	printf("Hello World! It's me, thread #%d!/n", tid);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t id;
	void *ret;
	int i, retv;
	int t = 123;
	retv = pthread_create(&id, NULL, (void *)thread, (void *)t);
	if (retv != 0)
	{
		printf("Create pthread error!\n");
		return 1;
	}
	for (i = 0; i < 3; i++)
		printf("This is the main process.\n");
	pthread_join(id, &ret);
	printf("The thread return value is%d\n", (int)ret);
	return 0;
}