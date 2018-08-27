//TransParent.c
#include<windows.h>

//导入msimg32.lib库
#pragma comment(lib, "msimg32")
void TransparentBlt2(
    HDC hdcDest,        // 目标DC
    int nXOriginDest,   // 目标X偏移
    int nYOriginDest,   // 目标Y偏移
    int nWidthDest,     // 目标宽度
    int nHeightDest,    // 目标高度
    HDC hdcSrc,         // 源DC
    int nXOriginSrc,    // 源X起点
    int nYOriginSrc,    // 源Y起点
    int nWidthSrc,      // 源宽度
    int nHeightSrc,     // 源高度
    UINT crTransparent  // 透明色,COLORREF类型,可以用GetPixel(hdc,0,0)得到
)
{
	int nDestDCState = SaveDC(hdcDest);
	HDC hImageDC = CreateCompatibleDC(hdcDest);
	int nImageDCState = SaveDC(hImageDC);
	HDC hMaskDC = CreateCompatibleDC(hdcDest);
	int nMaskDCState = SaveDC(hMaskDC);
	HBITMAP hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest); // 创建兼容位图
	HBITMAP hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);		  // 创建单色掩码位图
	SelectObject(hImageDC, hImageBMP);
	SelectObject(hMaskDC, hMaskBMP);

	//-- 0
	// 将源DC中的位图拷贝到临时DC中（因为可能会伸缩，所以用StretchBlt而不是BitBlt）
	StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	//-- 1
	// 设置透明色
	SetBkColor(hImageDC, crTransparent);
	// 此时掩码位图hMaskBMP：透明区域为白色(1)，显示区域为黑色(0)
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	//-- 2
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	// 这里有两步，首先：单色位图转换成彩色位图：1->BkColor ; 0->TextColor
	//             其次：第一步转出来的彩色位图 AND hImageBMP
	// 最终结果是：目标位图hImageBMP的透明区域为黑色(0)，显示区域保持不变
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	//-- 3
	SetBkColor(hdcDest, RGB(255,255,255));
	SetTextColor(hdcDest, RGB(0,0,0));
	// 也是两步，同上。
	// 最终结果是：hdcDest上被打了个洞，洞的大小正是目标位图显示区域大小，洞里的颜色是黑色(0)
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	//-- 4
	// OR运算，(hole in hdcDest) | (hImageBMP)
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	RestoreDC(hdcDest, nDestDCState);
	RestoreDC(hImageDC, nImageDCState);
	DeleteDC(hImageDC);
	RestoreDC(hMaskDC, nMaskDCState);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC	hdc, dstmem,srcmem;
	PAINTSTRUCT		ps;
	BITMAP 			bmp;
	static HBITMAP	hdstbmp,hsrcbmp;
	static SIZE		dstbmp,srcbmp;
	switch(message) {
	case WM_CREATE:
		//加载位图信息
		hdstbmp = (HBITMAP)LoadImage(0,"view.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
		hsrcbmp = (HBITMAP)LoadImage(0,"little.bmp",IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
		GetObject(hdstbmp, sizeof(BITMAP), &bmp);
		dstbmp.cx	= bmp.bmWidth;
		dstbmp.cy	= bmp.bmHeight;
		GetObject(hsrcbmp, sizeof(BITMAP), &bmp);
		srcbmp.cx	= bmp.bmWidth;
		srcbmp.cy	= bmp.bmHeight;
		return 0 ;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		dstmem = CreateCompatibleDC(hdc);
		srcmem = CreateCompatibleDC(hdc);
		SelectObject(dstmem,hdstbmp);
		SelectObject(srcmem, hsrcbmp);
		for(int i=0; i<5; i++)
			TransparentBlt(dstmem,100*i,100*i,srcbmp.cx,srcbmp.cy,
			               srcmem,0,0,srcbmp.cx,srcbmp.cy,GetPixel(srcmem,0,0));
		BitBlt(hdc,0,0,dstbmp.cx,dstbmp.cy,dstmem,0,0,SRCCOPY);
		DeleteDC(dstmem);
		DeleteDC(srcmem);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		if(hdstbmp)DeleteObject(hdstbmp);
		if(hsrcbmp)DeleteObject(hsrcbmp);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR szCmdLine,
                   int iCmdShow)
{
	static	TCHAR	szAppName[] = TEXT("TransParent");
	HWND			hwnd;
	MSG				msg;
	WNDCLASS		wndclass;
	int				cxScreen, cyScreen;
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= szAppName;
	if(!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
		           szAppName, MB_ICONERROR);
		return 0;
	}
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	hwnd = CreateWindow(szAppName,TEXT("TransParent Demo"),WS_OVERLAPPEDWINDOW,
	                    cxScreen / 4,cyScreen / 8,cxScreen / 2,cyScreen * 3 / 4,
	                    NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}