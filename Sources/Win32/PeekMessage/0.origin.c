// 使系统无法进入IDLE模式，This PeekMessage loop will NOT let the system go idle.
for( ;; )
{
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return TRUE;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	BackgroundProcessing();//your process
}