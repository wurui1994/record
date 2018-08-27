#include <windows.h>
#include <windowsx.h>
#include <Vfw.h>
#include <stdio.h>

#pragma comment(lib, "vfw32")

CHAR gachBuffer[100]; // Global buffer.
DWORD gdwFrameNum = 0;

// FrameCallbackProc: frame callback function.
// hWnd:              capture window handle.
// lpVHdr:            pointer to structure containing captured
//                        frame information.
//
LRESULT PASCAL FrameCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	if (!hWnd)
		return FALSE;

	sprintf(gachBuffer, "Preview frame# %ld ", gdwFrameNum++);
	SetWindowTextA(hWnd, gachBuffer);

	capFileSaveDIB(hWnd, L"test.bmp");

	return (LRESULT)TRUE;
}

CHAR gachAppName[] = "Application Name"; // Application name.
//CHAR gachBuffer[100];  // Global buffer.

// StatusCallbackProc: status callback function.
// hWnd:               capture window handle.
// nID:                status code for the current status.
// lpStatusText:       status text string for the current status.
//
LRESULT PASCAL StatusCallbackProc(HWND hWnd, int nID,
								  LPTSTR lpStatusText)
{
	if (!hWnd)
		return FALSE;

	if (nID == 0)
	{
		// Clear old status messages.
		SetWindowTextA(hWnd, gachAppName);
		return (LRESULT)TRUE;
	}
	// Show the status ID and status text.
	sprintf(gachBuffer, "Status# %d: %s", nID, lpStatusText);

	SetWindowTextA(hWnd, gachBuffer);
	return (LRESULT)TRUE;
}

//CHAR gachBuffer[100]; // Global buffer.

// ErrorCallbackProc: error callback function.
// hWnd:              capture window handle.
// nErrID:            error code for the encountered error.
// lpErrorText:       error text string for the encountered error.
//
LRESULT PASCAL ErrorCallbackProc(HWND hWnd, int nErrID,
								 LPSTR lpErrorText)
{

	if (!hWnd)
		return FALSE;

	if (nErrID == 0) // Starting a new major function.
		return TRUE; // Clear out old errors.

	// Show the error identifier and text.
	sprintf(gachBuffer, "Error# %d", nErrID);

	MessageBoxA(hWnd, lpErrorText, gachBuffer,
				MB_OK | MB_ICONEXCLAMATION);

	return (LRESULT)TRUE;
}

WNDPROC OldProc;
//
LRESULT CALLBACK NewProc(HWND hwndParent, UINT message, WPARAM wParam, LPARAM lParam)
{

	//
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return CallWindowProc(OldProc, hwndParent, message, wParam, lParam);
	;
}

int main()
{
	HWND ghWndCap;

	int nID = 0;
	BOOL fOK;

	static TCHAR szAppName[] = TEXT("HelloWin");
	MSG msg;

	//hWnd = CreateWindow(szAppName, TEXT("RGB"), WS_OVERLAPPEDWINDOW,
	//	320, 120, 500, 500, NULL, NULL, hInstance, NULL);
	ghWndCap = capCreateCaptureWindow(
		TEXT("My Capture Window"), // window name if pop-up
		WS_OVERLAPPEDWINDOW,	   // window style
		320, 120, 640, 480,		   // window position and dimensions
		(HWND)0,
		(int)nID /* child ID */);

	//subclass

	OldProc = (WNDPROC)SetWindowLong(ghWndCap, GWL_WNDPROC, (LONG)NewProc);

	capSetCallbackOnError(ghWndCap, ErrorCallbackProc);

	// Register the status callback function using the
	// capSetCallbackOnStatus macro.
	capSetCallbackOnStatus(ghWndCap, StatusCallbackProc);

	// Register the video-stream callback function using the
	// capSetCallbackOnVideoStream macro.
	//capSetCallbackOnVideoStream(ghWndCap, VideoCallbackProc);

	// Register the frame callback function using the
	// capSetCallbackOnFrame macro.
	capSetCallbackOnFrame(ghWndCap, FrameCallbackProc);
	//ShowWindow(hWndC, SW_SHOW);
	fOK = capDriverConnect(ghWndCap, 0);

	CAPDRIVERCAPS CapDrvCaps;

	SendMessage(ghWndCap, WM_CAP_DRIVER_GET_CAPS,
				sizeof(CAPDRIVERCAPS), (LONG)(LPVOID)&CapDrvCaps);

	// Or, use the macro to retrieve the driver capabilities.
	// capDriverGetCaps(hWndC, &CapDrvCaps, sizeof (CAPDRIVERCAPS));

	CAPSTATUS CapStatus = {};

	capGetStatus(ghWndCap, &CapStatus, sizeof(CAPSTATUS));

	SetWindowPos(ghWndCap, NULL, 320, 120, CapStatus.uiImageWidth + 16,
				 CapStatus.uiImageHeight + 38, SWP_NOZORDER | SWP_NOMOVE);

	LPBITMAPINFO lpbi;
	DWORD dwSize;

	dwSize = capGetVideoFormatSize(ghWndCap);
	lpbi = (LPBITMAPINFO)GlobalAllocPtr(GHND, dwSize);
	capGetVideoFormat(ghWndCap, lpbi, dwSize);

	// Access the video format and then free the allocated memory.

	capPreviewRate(ghWndCap, 66); // rate, in milliseconds
	capPreview(ghWndCap, TRUE);   // starts preview

	//CAPDRIVERCAPS CapDrvCaps;

	capDriverGetCaps(ghWndCap, &CapDrvCaps, sizeof(CAPDRIVERCAPS));

	if (CapDrvCaps.fHasOverlay)
		capOverlay(ghWndCap, TRUE);

	//也可以放在此
	ShowWindow(ghWndCap, SW_SHOW);
	UpdateWindow(ghWndCap);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//capSetCallbackOnFrame(ghWndCap, NULL);
	//capDriverDisconnect(ghWndCap);
	return 0;
}
