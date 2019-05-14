#pragma warning(disable : 4786)
#include <windows.h>
#define ULONG_PTR void*
#include <GdiPlus.h>			/*用于显示BMP、JPG文件的库*/
#include <vector>
#include <string>
const int KEY_VALUE_B = 66;		/*B键值*/
const int KEY_VALUE_S = 83;		/*S键值*/
const int RANGE_MAX = 100;		/*滚动条范围*/
using namespace Gdiplus;
// Global Variables:
static int iAllBmpJpg = 0;				/*当前目录下所有BMP、JPG文件数*/
static int iCurBmpJpg = 0;				/*当前文件数*/
static double fMultiple = 1.0;			/*默认放大倍数为1*/
static const double fEnlarge = 1.2;		/*每次放大 20% */
// Foward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
int GetBmpJpg(std::vector<std::string>& oBJPicture);
wchar_t* ChrToWChr(const char* buffer);
/*
功能说明：		主函数，应用程序的入口点，初始化应用程序，显示主窗口，进入一个消息接收一发送循环
输如参数说明：
输出参数说明：
返回值说明：
备注：			
*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					PSTR szCmdLine, int iCmdShow)					
{
	static TCHAR szAppName [] = TEXT ("Bricks1") ;	
	HWND                         hwnd ;	
	MSG                           msg ;	
	WNDCLASS                      wndclass ;		
	wndclass.style                               = CS_HREDRAW | CS_VREDRAW ;	
	wndclass.lpfnWndProc                         = WndProc ;	
	wndclass.cbClsExtra                          = 0 ;	
	wndclass.cbWndExtra                          = 0 ;	
	wndclass.hInstance                           = hInstance ;	
	wndclass.hIcon                               = LoadIcon (NULL, IDI_APPLICATION) ;	
	wndclass.hCursor                             = LoadCursor (NULL, IDC_ARROW) ;	
	wndclass.hbrBackground						 = (HBRUSH) GetStockObject (WHITE_BRUSH) ;	
	wndclass.lpszMenuName					    = NULL ;	
	wndclass.lpszClassName					    = szAppName ;	
	if (!RegisterClass (&wndclass))        
	{       
		MessageBox (NULL, TEXT ("This program requires Windows NT!"),			
			szAppName, MB_ICONERROR) ;        
		return 0 ;        
    }
	hwnd = CreateWindow ( szAppName, TEXT ("LoadBitmap Demo"),        
		WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL,        
		CW_USEDEFAULT, CW_USEDEFAULT,        
		CW_USEDEFAULT, CW_USEDEFAULT,        
		NULL, NULL, hInstance, NULL);	
	iCmdShow = SW_SHOWMAXIMIZED;	/*默认最大化窗口*/
	ShowWindow (hwnd, iCmdShow);
	UpdateWindow (hwnd) ;
	while (GetMessage (&msg, NULL, 0, 0))        
	{        
		TranslateMessage (&msg) ;        
		DispatchMessage (&msg) ;        
	}
	return msg.wParam ;	
}
/*
功能说明：		Processes messages for the main window
				WM_PAINT	- Paint the main window
				WM_DESTROY	- post a quit message and return
输如参数说明：
输出参数说明：
返回值说明：
备注：			
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int iXSource = 0;						/*加载的图片宽*/
	int iYSource = 0;						/*加载的图片高*/
	char szCur[50] = {0};					/*存储整型iCurBmpJpg转换成的字符串*/
	char szAll[50] = {0};					/*存储整型iAllBmpJpg转换成的字符串*/
	std::string oShow;						/*显示图片信息*/
	std::vector<std::string> oPicture;		/*存放当前目录下BMP、JPG图片文件名*/
	SCROLLINFO si;
	static int iVertPos = 0;				/*垂直滚动条的位置*/
	static int iHorzPos = 0;				/*水平滚动条的位置*/
	switch (message) 
	{
		case WM_SIZE:						/*当然该窗口第一次显示时，将接收到该消息*/
		{
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE|SIF_POS;
			si.nPos = 0;
			si.nMin = 0;
			si.nMax = RANGE_MAX;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);	/*设置垂直滚动条的滚动范围和初始位置*/
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);	/*设置水平滚动条的滚动范围和初始位置*/
			break;
		}
		case WM_VSCROLL:			/*垂直滚动条的消息*/
		{
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_VERT, &si);
			iVertPos = si.nPos;
			switch(LOWORD(wParam))
			{
			case SB_TOP:
				si.nPos = si.nMin;
				break;
			case SB_BOTTOM:
				si.nPos = si.nMax;
				break;
			case SB_LINEUP:
				si.nPos -= 1;
				break;
			case SB_LINEDOWN:
				si.nPos += 1;
				break;
			case SB_THUMBTRACK:
				si.nPos = si.nTrackPos;
				break;
			default:
				break;
			}
			si.fMask = SIF_POS;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);	/*设置垂直滚动条新的位置*/
			GetScrollInfo(hWnd, SB_VERT, &si);
			if (si.nPos != iVertPos)		/*位置发生改变时重画*/
			{
				iVertPos = si.nPos;
				InvalidateRect(hWnd, NULL, FALSE);	
			}
			break;
		}
		case WM_HSCROLL:		/*水平滚动条的消息*/
		{
			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_HORZ, &si);
			iHorzPos = si.nPos;
			switch(LOWORD(wParam))
			{
			case SB_LEFT:
				si.nPos = si.nMin;
				break;
			case SB_RIGHT:
				si.nPos = si.nMax;
				break;
			case SB_LINELEFT:
				si.nPos -= 1;
				break;
			case SB_LINERIGHT:
				si.nPos += 1;
				break;
			case SB_THUMBTRACK:
				si.nPos = si.nTrackPos;
			default:
				break;
			}
			si.fMask = SIF_POS;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);	/*设置水平滚动条新的位置*/
			GetScrollInfo(hWnd, SB_HORZ, &si);
			if (iHorzPos != si.nPos)		/*位置发生改变时重画*/
			{
				iHorzPos = si.nPos;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		}
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			RECT rect;
			GetClientRect(hWnd, &rect);
#if 0		/*本程序用的是GDI+双缓冲*/
			/*GDI 双缓冲*/
			hdcMem = CreateCompatibleDC(hdc);
			hMemBitMap = CreateCompatibleBitmap(hdcMem,rect.right-rect.left,rect.bottom-rect.top);
			SelectObject(hdcMem, hMemBitMap);
			/*填充内存背景位图为白色*/
			hBrush = CreateSolidBrush(RGB(0xff,0xff,0x00));
			FillRect(hdcMem, &rect, hBrush);
			//SetBkColor(hdcMem, RGB(0xff, 0x00, 0xff));
#endif
			/*得到当前目录下所有BMP、JPG文件*/
			iAllBmpJpg = GetBmpJpg(oPicture);
			if (iAllBmpJpg == 0)
			{
				MessageBox(NULL, "there are not bmp jpg picture!", NULL, MB_OK);
				exit(0);
			}
			/*使oShow包含这些显示信息：iCurBmpJpg、iBmpJpg、当前文件名*/
			itoa(iCurBmpJpg + 1, szCur, 10);
			itoa(iAllBmpJpg, szAll, 10);
			oShow += szCur;
			oShow += "/";
			oShow += szAll;
			oShow += "\n";
			oShow += oPicture[iCurBmpJpg];
			/*把当前图片文件名char型转换成WCHAR型*/
			wchar_t *pwFileName = NULL;
			pwFileName = ChrToWChr(oPicture[iCurBmpJpg].c_str());
			if (NULL == pwFileName)
			{
				MessageBox(NULL, "pwFileName is NULL!", NULL, MB_OK);
				exit(0);
			}
			/*加载图片*/
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			ULONG_PTR gdiplusToken;
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
			Gdiplus::Image *pImage = Gdiplus::Image::FromFile(pwFileName);
			iXSource = pImage->GetWidth();
			iYSource = pImage->GetHeight();
			/*图片未超过窗口时隐藏滚动条*/
			if (iXSource * fMultiple < rect.right - rect.left)		/*图片水平方向未超过窗口时，隐藏水平滚动条*/
			{
				si.cbSize = sizeof(SCROLLINFO);
				si.fMask = SIF_PAGE;
				si.nPage = si.nMax;		/*页面大小大于等于滚动条范围，Windows通常隐藏滚动条*/
				SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			}
			else													/*图片水平方向超过窗口时，显示水平滚动条*/
			{
				si.cbSize = sizeof(SCROLLINFO);
				si.fMask = SIF_PAGE;
				si.nPage = 0;			/*页面大小小于滚动条范围，显示滚动条*/
				SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			}
			if (iYSource * fMultiple < rect.bottom - rect.top)		/*图片垂直方向未超过窗口时，隐藏垂直滚动条*/
			{
				si.cbSize = sizeof(SCROLLINFO);
				si.fMask = SIF_PAGE;
				si.nPage = si.nMax;	
				SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
			}
			else													/*图片垂直方向超过窗口时，显示垂直滚动条*/
			{
				si.cbSize = sizeof(SCROLLINFO);
				si.fMask = SIF_PAGE;		
				si.nPage = 0;
				SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
			}
			/*创建内存位图,用于双缓冲*/
			Bitmap *pMemBitmap= new Bitmap(rect.right - rect.left, rect.bottom - rect.top);
			if (NULL == pMemBitmap)
			{
				exit(1);
			}
			Graphics graphicsMemBitmap(pMemBitmap);
			/*设置内存位图的背景为白色*/
			graphicsMemBitmap.Clear(Color.White);
			/*将加载的图片画到内存位图，画在中间，当图片很大时，可以实现滚动条看图*/
			RectF rectMap(long((iXSource * fMultiple > rect.right - rect.left) ? rect.left : (rect.right - rect.left - iXSource * fMultiple)/2),
						long((iYSource * fMultiple > rect.bottom - rect.top) ? rect.top : (rect.bottom - rect.top - iYSource * fMultiple)/2),
						long((iXSource * fMultiple > rect.right - rect.left) 
							? rect.right - rect.left : iXSource * fMultiple),
						long((iYSource * fMultiple > rect.bottom - rect.top) 
							? rect.bottom - rect.top : iYSource * fMultiple));
			graphicsMemBitmap.DrawImage(pImage,	
							//int((rect.right - rect.left - iXSource * fMultiple) > 0 ? (rect.right - rect.left - iXSource * fMultiple)/2 : 0), 
							//int((rect.bottom - rect.top - iYSource * fMultiple) > 0 ? (rect.bottom - rect.top - iYSource * fMultiple)/2 : 0), 
							rectMap,
							int((iXSource * fMultiple > rect.right - rect.left) 
								? (float(iHorzPos)/RANGE_MAX * (iXSource * fMultiple - (rect.right - rect.left))) / fMultiple : 0),
							int((iYSource * fMultiple > rect.bottom - rect.top) 
								? (float(iVertPos)/RANGE_MAX * (iYSource * fMultiple - (rect.bottom - rect.top))) / fMultiple : 0),
							int((iXSource * fMultiple > rect.right - rect.left) ? (rect.right - rect.left) / fMultiple : iXSource), 
							int((iYSource * fMultiple > rect.bottom - rect.top) ? (rect.bottom - rect.top) / fMultiple : iYSource),
							UnitPixel);
			/*通过多画一块内存位图实现滚动，效率不如上一种高*/
/*			Bitmap *pTmpBitmap = new Bitmap(iXSource * fMultiple, iYSource * fMultiple);
			if (NULL == pTmpBitmap)
			{
				exit(1);
			}
			Graphics graphicsTmpBitmap(pTmpBitmap);
			graphicsTmpBitmap.Clear(Color.White);
			graphicsTmpBitmap.DrawImage(pImage,
										int(0), 
										int(0), 
										int(iXSource * fMultiple), 
										int(iYSource * fMultiple));
			graphicsMemBitmap.DrawImage(pTmpBitmap,
										int((iXSource * fMultiple > rect.right - rect.left) ? 0 : (rect.right - rect.left - iXSource * fMultiple)/2), 
										int((iYSource * fMultiple > rect.bottom - rect.top) ? 0 : (rect.bottom - rect.top - iYSource * fMultiple)/2), 
										int((iXSource * fMultiple > rect.right - rect.left) 
											? double(iHorzPos)/RANGE_MAX * (iXSource * fMultiple - (rect.right - rect.left)) : 0),
										int((iYSource * fMultiple > rect.bottom - rect.top)
											? double(iVertPos)/RANGE_MAX * (iYSource * fMultiple - (rect.bottom - rect.top)) : 0),
										int((iXSource * fMultiple > rect.right - rect.left) ? (rect.right - rect.left) : (iXSource * fMultiple)), 
										int((iYSource * fMultiple > rect.bottom - rect.top) ? (rect.bottom - rect.top) : (iYSource * fMultiple)),
										UnitPixel);
*/
			/*在内存位图上画当前文件数、总文件数和文件名*/
			SolidBrush solidBrush(Color(255, 0, 0, 0));
			FontFamily fontFamily(L"宋体");
			Font font(&fontFamily, 12, FontStyleRegular, UnitPoint);
			PointF pointF((rect.right - rect.left)/2, 0);
			wchar_t *pwShow = NULL;
			pwShow = ChrToWChr(oShow.c_str());
			graphicsMemBitmap.DrawString(pwShow, MultiByteToWideChar(CP_ACP, 0, oShow.c_str(), -1, NULL, 0), &font, pointF, &solidBrush);
			/*将内存位图画到设备DC*/
			Graphics graphics(hdc);
			graphics.DrawImage(pMemBitmap, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
/*			if (NULL != pTmpBitmap)
			{
				delete pTmpBitmap;
				pTmpBitmap = NULL;
			}
*/
			if (NULL != pwFileName)
			{
				delete[] pwFileName;
				pwFileName = NULL;
			}
			if (NULL != pwShow)
			{
				delete[] pwShow;
				pwShow = NULL;
			}
			//delete &font;
			delete &solidBrush;
			if (NULL != pImage)
			{
				delete pImage;
				pImage = NULL;
			}
			if (NULL != pMemBitmap)
			{
				delete pMemBitmap;
				pMemBitmap = NULL;
			}
			//Gdiplus::GdiplusShutdown(gdiplusToken);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_LBUTTONDOWN:	/*左键消息，下一张*/
			{
				if (iCurBmpJpg < iAllBmpJpg - 1)
				{
					iCurBmpJpg++;
				}
				else if (iCurBmpJpg == iAllBmpJpg - 1)		/*最后一张图片，循环，跳到第一张*/
				{
					iCurBmpJpg = 0;
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
		case WM_RBUTTONDOWN:	/*右键消息，上一张*/
			{
				if (iCurBmpJpg > 0)
				{
					iCurBmpJpg--;
				}
				else if (iCurBmpJpg == 0)		/*第一张，循环，跳到最后一张*/
				{
					iCurBmpJpg = iAllBmpJpg - 1;
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
		case WM_KEYDOWN:		/*键盘消息*/
			{
				if (wParam == KEY_VALUE_B)	/*B键*/
				{
					if (fMultiple < 10.0)	/*最多放大十倍*/
					{
						fMultiple *= fEnlarge;
					}
				}
				else if (wParam == KEY_VALUE_S)	/*S键*/
				{
					if (fMultiple > 0.1)	/*最多缩小十倍*/
					{
						fMultiple /= fEnlarge;
					}
				}
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
		case WM_ERASEBKGND:
			{
				break;
			}
		default:
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
   }
   return 0;
}
/*
功能说明：		得到当前目录下所有的BMP、JPG文件名
输入参数说明：	
输出参数说明：	oBJPicture：存储BMP、JPG文件名
返回值说明：	所有的BMP、JPG文件个数
备注：			
*/
int GetBmpJpg(std::vector<std::string>& oBJPicture)
{
	int iRet = 0;
	HANDLE	hFile;
	WIN32_FIND_DATA oFindDate;
#if 1
	/*寻找.jpg文件*/
	hFile = FindFirstFile("*.jpg", &oFindDate);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, "FindFirstFile() failed!", NULL, MB_OK);
		//return 0;
		iRet = 0;
	}
	else
	{
		iRet = 1;
	}
	while (iRet)
	{
		oBJPicture.push_back(oFindDate.cFileName);
		iRet = FindNextFile(hFile, &oFindDate);
	}
#endif
	/*寻找.bmp文件*/
	hFile = FindFirstFile("*.bmp", &oFindDate);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, "FindFirstFile() failed!", NULL, MB_OK);
		//return 0;
		iRet = 0;
	}
	else
	{
		iRet = 1;
	}
	while (iRet)
	{
		oBJPicture.push_back(oFindDate.cFileName);
		iRet = FindNextFile(hFile, &oFindDate);
	}
	/*寻找完毕，释放句柄*/
	FindClose(hFile);
#if 0
	/*调试用*/
	char szBJSize[10] = {0};
	itoa(oBJPicture.size(), szBJSize, 10);
	MessageBox(NULL, szBJSize, NULL, NULL);
	for (int i = 0; i < oBJPicture.size(); i++)
	{
		MessageBox(NULL, oBJPicture[i].c_str(), NULL, NULL);
	}
#endif
	/*返回找到的BMP、JPG文件个数*/
	return oBJPicture.size();
}
/*
功能说明：		把char字符串转换成WCHAR字符串
输入参数说明：	buffer:字符串指针
输出参数说明：	
返回值说明：	WCHAR字符串指针
备注：			
*/
wchar_t* ChrToWChr(const char* pBuffer)
{
	if (NULL == pBuffer)
	{
		return NULL;
	}
	//size_t ilen = strlen(pBuffer) + 1;
	wchar_t* pwBuf;
	size_t iwlen = MultiByteToWideChar(CP_ACP, 0, (const char*)pBuffer, -1, NULL, 0);
	pwBuf = new wchar_t[iwlen];
	MultiByteToWideChar(CP_ACP, 0, (const char*)pBuffer, -1, pwBuf, int(iwlen));
	return pwBuf;
}