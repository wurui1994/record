for(;;)
{

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return TRUE;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (IfBackgroundProcessingRequired())//是否需要运行
		BackgroundProcessing();
	else
		WaitMessage(); // 等待消息， Will not return until a message is posted.

}