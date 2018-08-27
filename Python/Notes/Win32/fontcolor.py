import ctypes
import time, math, random
from random import randint
import win32gui, win32con, win32api

dx=10

def OnPaint(hwnd, msg, wp, lp):
	global dx
	font=win32gui.LOGFONT()
	font.lfFaceName="Consolas"
	font.lfHeight=48
	# font.lfWidth=font.lfHeight
	# font.lfWeight=150
	# font.lfItalic=1
	# font.lfUnderline=1
	hfont=win32gui.CreateFontIndirect(font)
	dc, ps=win32gui.BeginPaint(hwnd)
	win32gui.SetGraphicsMode(dc, win32con.GM_ADVANCED)
	l,t,r,b=win32gui.GetClientRect(hwnd)
	br=win32gui.CreateSolidBrush(win32api.RGB(0,0,255))
	bitmap=win32gui.CreateBitmap(20,5,4,1,None)
	win32gui.SelectObject(dc, bitmap)
	win32gui.SelectObject(dc, br)
	win32gui.SelectObject(dc, hfont)
	win32gui.SetTextColor(dc,win32api.RGB(randint(1,255),randint(1,255),randint(1,255)));
	win32gui.DrawText(dc,'hello',-1,(100,100,300,300),0)
	win32gui.FillRect(dc,(200+dx,200+dx,100+dx,100+dx),br)
	dx=(dx+10)%100
	win32gui.EndPaint(hwnd, ps)
	return 0

wc = win32gui.WNDCLASS()
wc.lpszClassName = 'win32'
wc.style = win32con.CS_VREDRAW | win32con.CS_HREDRAW
wc.hbrBackground = win32con.COLOR_WINDOW+1
wndproc={win32con.WM_PAINT:OnPaint}
wc.lpfnWndProc=wndproc
wc.hCursor = win32gui.LoadCursor (None, win32con.IDC_ARROW)
class_atom=win32gui.RegisterClass(wc)       
hwnd = win32gui.CreateWindow(class_atom,'hello',
	win32con.WS_OVERLAPPEDWINDOW|win32con.WS_VISIBLE,
	350,120,640,480, 0, 0, 0, None)
    
for _ in range(30):
	win32gui.InvalidateRect(hwnd,None,True)
	win32gui.PumpWaitingMessages()
	time.sleep(0.1)
    
win32gui.DestroyWindow(hwnd)
win32gui.UnregisterClass(class_atom,None)



