// ParseALargeFile - uses a progress bar to indicate the progress of a parsing operation.
//
// Returns TRUE if successful, or FALSE otherwise.
//
// hwndParent - parent window of the progress bar.
//
// lpszFileName - name of the file to parse.
//
// Global variable
//     g_hinst - instance handle.
//

HINSTANCE g_hinst;

BOOL ParseALargeFile(HWND hwndParent, LPTSTR lpszFileName)
{
	RECT rcClient;  // Client area of parent window.
	int cyVScroll;  // Height of scroll bar arrow.
	HWND hwndPB;    // Handle of progress bar.
	HANDLE hFile;   // Handle of file.
	DWORD cb;       // Size of file and count of bytes read.
	LPCH pch;       // Address of data read from file.
	LPCH pchTmp;    // Temporary pointer.

	// Ensure that the common control DLL is loaded, and create a progress bar
	// along the bottom of the client area of the parent window.
	//
	// Base the height of the progress bar on the height of a scroll bar arrow.

	InitCommonControls();

	GetClientRect(hwndParent, &rcClient);

	cyVScroll = GetSystemMetrics(SM_CYVSCROLL);

	hwndPB = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL,
	                        WS_CHILD | WS_VISIBLE, rcClient.left,
	                        rcClient.bottom - cyVScroll,
	                        rcClient.right, cyVScroll,
	                        hwndParent, (HMENU)0, g_hinst, NULL);

	// Open the file for reading, and retrieve the size of the file.

	hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ,
	                   (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING,
	                   FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

	if (hFile == (HANDLE)INVALID_HANDLE_VALUE)
		return FALSE;

	cb = GetFileSize(hFile, (LPDWORD)NULL);

	// Set the range and increment of the progress bar.

	SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, cb / 2048));

	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM)1, 0);

	// Parse the file.
	pch = (LPCH)LocalAlloc(LPTR, sizeof(char) * 2048);

	pchTmp = pch;

	do {
		ReadFile(hFile, pchTmp, sizeof(char) * 2048, &cb, (LPOVERLAPPED)NULL);

		// TODO: Write an error handler to check that all the
		// requested data was read.
		//
		// Include here any code that parses the
		// file.
		//
		//
		//
		// Advance the current position of the progress bar by the increment.

		SendMessage(hwndPB, PBM_STEPIT, 0, 0);

	} while (cb);

	CloseHandle((HANDLE)hFile);

	DestroyWindow(hwndPB);

	return TRUE;
}