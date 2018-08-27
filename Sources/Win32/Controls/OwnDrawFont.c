/*---------------------------------------------
OWNDRAW.C -- Owner-Draw Button Demo Program
(c) Charles Petzold, 1998
---------------------------------------------*/

#include <windows.h>

#define ID_SMALLER      1
#define ID_LARGER       2

#define BTN_WIDTH        (8 * cxChar)
#define BTN_HEIGHT       (4 * cyChar)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

static HWND      hwndSmaller, hwndLarger;
WNDPROC OldWindowProc;



LRESULT NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static BOOL m_bMouseTracking = FALSE;
    static BOOL isHover = FALSE;
    LPDRAWITEMSTRUCT pdis;
    RECT rt;
    switch (message)
    {
    case WM_MOUSEMOVE:
    {
        if (!m_bMouseTracking)
        {
            TRACKMOUSEEVENT Tme;
            Tme.cbSize = sizeof(Tme);
            Tme.hwndTrack = hWnd;
            Tme.dwFlags = TME_LEAVE | TME_HOVER;
            Tme.dwHoverTime = 1;
            TrackMouseEvent(&Tme);

            m_bMouseTracking = TRUE;
        }
    }
    break;

    case WM_MOUSEHOVER:
        m_bMouseTracking = FALSE;
        if (!isHover)
        {
            GetClientRect(hWnd, &rt);
            InvertRect(GetDC(hWnd), &rt);
            /*FillRect(GetDC(hWnd), &rt,
                (HBRUSH)GetStockObject(BLACK_BRUSH));*/
            isHover = TRUE;
        }
        break;
    case WM_MOUSELEAVE:
        m_bMouseTracking = FALSE;
        GetClientRect(hWnd, &rt);
        InvalidateRect(hWnd, &rt, TRUE);
        isHover = FALSE;
        /*GetClientRect(hWnd, &rt);
        FillRect(GetDC(hWnd), &rt,
        (HBRUSH)GetStockObject(WHITE_BRUSH));
        FrameRect(GetDC(hWnd), &rt,
        (HBRUSH)GetStockObject(BLACK_BRUSH));*/

        break;
    }
    return CallWindowProc(OldWindowProc, hWnd, message, wParam, lParam);//不处理的交给旧的PROC
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{

    static TCHAR szAppName[] = TEXT("OwnDraw");
    MSG          msg;
    HWND         hwnd;
    WNDCLASS     wndclass;

    hInst = hInstance;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = szAppName;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("Owner-Draw Button Demo"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void Triangle(HDC hdc, POINT pt[])
{
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    Polygon(hdc, pt, 3);
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
}





LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static int       cxClient, cyClient, cxChar, cyChar;
    int              cx, cy;
    LPDRAWITEMSTRUCT pdis;
    POINT            pt[3];
    RECT             rc, rt;

    switch (message)
    {
    case WM_CREATE:
        cxChar = LOWORD(GetDialogBaseUnits());
        cyChar = HIWORD(GetDialogBaseUnits());

        // Create the owner-draw pushbuttons

        hwndSmaller = CreateWindow(TEXT("button"), TEXT("test"),
            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            0, 0, BTN_WIDTH, BTN_HEIGHT,
            hwnd, (HMENU)ID_SMALLER, hInst, NULL);

        OldWindowProc = (WNDPROC)GetWindowLong(hwndSmaller, GWL_WNDPROC);
        SetWindowLong(hwndSmaller, GWL_WNDPROC, NewWndProc);

        //SendMessage(hwndSmaller, WM_MOUSELEAVE, 0, 0);
        hwndLarger = CreateWindow(TEXT("button"), TEXT(""),
            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
            0, 0, BTN_WIDTH, BTN_HEIGHT,
            hwnd, (HMENU)ID_LARGER, hInst, NULL);
        return 0;

    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        // Move the buttons to the new center

        MoveWindow(hwndSmaller, cxClient / 2 - 3 * BTN_WIDTH / 2,
            cyClient / 2 - BTN_HEIGHT / 2,
            BTN_WIDTH, BTN_HEIGHT, TRUE);

        MoveWindow(hwndLarger, cxClient / 2 + BTN_WIDTH / 2,
            cyClient / 2 - BTN_HEIGHT / 2,
            BTN_WIDTH, BTN_HEIGHT, TRUE);
        return 0;

    case WM_COMMAND:
        GetWindowRect(hwnd, &rc);

        // Make the window 10% smaller or larger

        switch (wParam)
        {
        case ID_SMALLER:
            rc.left += cxClient / 20;
            rc.right -= cxClient / 20;
            rc.top += cyClient / 20;
            rc.bottom -= cyClient / 20;
            break;

        case ID_LARGER:
            rc.left -= cxClient / 20;
            rc.right += cxClient / 20;
            rc.top -= cyClient / 20;
            rc.bottom += cyClient / 20;
            break;
        }

        MoveWindow(hwnd, rc.left, rc.top, rc.right - rc.left,
            rc.bottom - rc.top, TRUE);
        return 0;
    case WM_DRAWITEM:
        pdis = (LPDRAWITEMSTRUCT)lParam;

        // Fill area with white and frame it black

        FillRect(pdis->hDC, &pdis->rcItem,
            (HBRUSH)GetStockObject(WHITE_BRUSH));

        FrameRect(pdis->hDC, &pdis->rcItem,
            (HBRUSH)GetStockObject(BLACK_BRUSH));

        // Draw inward and outward black triangles

        cx = pdis->rcItem.right - pdis->rcItem.left;
        cy = pdis->rcItem.bottom - pdis->rcItem.top;

        switch (pdis->CtlID)
        {
        case ID_SMALLER:
            /*pt[0].x = 3 * cx / 8;  pt[0].y = 1 * cy / 8;
            pt[1].x = 5 * cx / 8;  pt[1].y = 1 * cy / 8;
            pt[2].x = 4 * cx / 8;  pt[2].y = 3 * cy / 8;

            Triangle(pdis->hDC, pt);

            pt[0].x = 7 * cx / 8;  pt[0].y = 3 * cy / 8;
            pt[1].x = 7 * cx / 8;  pt[1].y = 5 * cy / 8;
            pt[2].x = 5 * cx / 8;  pt[2].y = 4 * cy / 8;

            Triangle(pdis->hDC, pt);

            pt[0].x = 5 * cx / 8;  pt[0].y = 7 * cy / 8;
            pt[1].x = 3 * cx / 8;  pt[1].y = 7 * cy / 8;
            pt[2].x = 4 * cx / 8;  pt[2].y = 5 * cy / 8;

            Triangle(pdis->hDC, pt);

            pt[0].x = 1 * cx / 8;  pt[0].y = 5 * cy / 8;
            pt[1].x = 1 * cx / 8;  pt[1].y = 3 * cy / 8;
            pt[2].x = 3 * cx / 8;  pt[2].y = 4 * cy / 8;

            Triangle(pdis->hDC, pt);*/
            //SetBkMode(pdis->hDC, TRANSPARENT);
            SetBkColor(pdis->hDC, RGB(255, 0, 0));
            SetTextColor(pdis->hDC, RGB(0, 255, 0));
            static HFONT hFont;
            hFont = CreateFont(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, "Consolas");
            SelectObject(pdis->hDC, hFont);
            DrawText(pdis->hDC, "hello", sizeof("hello")-1, &pdis->rcItem, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
            break;

        case ID_LARGER:
            pt[0].x = 5 * cx / 8;  pt[0].y = 3 * cy / 8;
            pt[1].x = 3 * cx / 8;  pt[1].y = 3 * cy / 8;
            pt[2].x = 4 * cx / 8;  pt[2].y = 1 * cy / 8;

            Triangle(pdis->hDC, pt);

            pt[0].x = 5 * cx / 8;  pt[0].y = 5 * cy / 8;
            pt[1].x = 5 * cx / 8;  pt[1].y = 3 * cy / 8;
            pt[2].x = 7 * cx / 8;  pt[2].y = 4 * cy / 8;

            Triangle(pdis->hDC, pt);

            pt[0].x = 3 * cx / 8;  pt[0].y = 5 * cy / 8;
            pt[1].x = 5 * cx / 8;  pt[1].y = 5 * cy / 8;
            pt[2].x = 4 * cx / 8;  pt[2].y = 7 * cy / 8;

            Triangle(pdis->hDC, pt);

            pt[0].x = 3 * cx / 8;  pt[0].y = 3 * cy / 8;
            pt[1].x = 3 * cx / 8;  pt[1].y = 5 * cy / 8;
            pt[2].x = 1 * cx / 8;  pt[2].y = 4 * cy / 8;

            Triangle(pdis->hDC, pt);
            break;
        }

        // Invert the rectangle if the button is selected

        if (pdis->itemState & ODS_SELECTED)
            InvertRect(pdis->hDC, &pdis->rcItem);
        // Draw a focus rectangle if the button has the focus

        if (pdis->itemState & ODS_FOCUS)
        {
            pdis->rcItem.left += cx / 16;
            pdis->rcItem.top += cy / 16;
            pdis->rcItem.right -= cx / 16;
            pdis->rcItem.bottom -= cy / 16;

            DrawFocusRect(pdis->hDC, &pdis->rcItem);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}