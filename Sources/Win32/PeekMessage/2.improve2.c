// Another improved PeekMessage() loop

for (;;)
{

	for (;;)
	{
		if (IfBackgroundProcessingRequired())
		{
			if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				break;
		}
		else
			GetMessage(&msg, NULL, 0, 0, 0);

		if (msg.message == WM_QUIT)
			return TRUE;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	BackgroundProcessing(); //

}

