#define EVENT_TIMER 0
#define EVENT_RENDER 1
#define EVENT_TOTAL 2
static HANDLE g_event[EVENT_TOTAL]; /* 初始化 */
g_event[EVENT_TIMER]=CreateWaitableTimer(NULL,FALSE,NULL);
g_event[EVENT_RENDER]=CreateEvent(NULL,FALSE,FALSE,NULL);
/* 主循环 */
for (;;)
{
	DWORD result=MsgWaitForMultipleObjects( EVENT_TOTAL,g_event,FALSE,INFINITE,QS_ALLEVENTS);
	switch (result-WAIT_OBJECT_0)
	{
	case EVENT_TIMER: /* 处理 timer */
		process_timer();
		break;
	case EVENT_RENDER:
		render_frame();
		break;
	case EVENT_TOTAL:
	{
		MSG msg;
		while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				goto _quit;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		break;
	}
	}
}
_quit: