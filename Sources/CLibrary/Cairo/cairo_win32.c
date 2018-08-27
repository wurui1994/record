//tcc -lcairo -run cairo_win32.c
#include <stdio.h>
#include <cairo/cairo.h>
#include <windows.h>

#pragma comment(lib,"cairo")

void draw(HDC hdc)
{
	cairo_surface_t *surface =cairo_win32_surface_create (hdc);
	// cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 120);
	cairo_t *cr = cairo_create (surface);
	cairo_select_font_face (cr, "Consolas", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, 90.0);
	cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
	cairo_move_to (cr, 20.0, 240.0);
	cairo_show_text (cr, "Hello,World!");
	// cairo_destroy (cr);
	// cairo_surface_write_to_png (surface, "hello.png");
	// cairo_surface_destroy (surface);
	// printf("Create hello.png file ok.\n");
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		draw(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	default:
		return DefWindowProc(hwnd, msg, w, l);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lp, int n)
{
	MSG msg;
	WNDCLASS wc = { sizeof(WNDCLASS) };
	char c[] = "theclass", t[] = "test";
	wc.style         = CS_HREDRAW | CS_VREDRAW ;
	wc.lpszClassName = c;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(c, t, WS_OVERLAPPEDWINDOW, 350, 120, 640, 480,0, 0, hInst, 0);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}