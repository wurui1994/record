
//tcc -lcairo-2 -run example.c
#include <stdio.h>
#include <cairo/cairo.h>
#include <windows.h>

#pragma comment(lib,"cairo")
#pragma comment(lib,"gdi32")

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

int main()
{
	RECT rcImg= {0,0,10000,8000};
	HDC hdc = CreateEnhMetaFile( NULL,"test.emf", &rcImg, (LPSTR)NULL);
	// DrawEMF(hdc);
    draw(hdc);
	HENHMETAFILE hemf= CloseEnhMetaFile(hdc);
	// OpenClipboard(0);
	// EmptyClipboard();
	// SetClipboardData(CF_ENHMETAFILE, hemf);
	// CloseClipboard();
	return 0;
}