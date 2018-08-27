#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <hpdf.h>

#pragma comment(lib,"hpdf")

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler(HPDF_STATUS   error_no,
	HPDF_STATUS   detail_no,
	void         *user_data)
{
	printf("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
		(HPDF_UINT)detail_no);
	longjmp(env, 1);
}


int main(int argc, char **argv)
{
	const char *page_title = "Font Demo";
	HPDF_Doc  pdf;
	char fname[256];
	HPDF_Page page;
	HPDF_Font def_font;
	HPDF_REAL tw;
	HPDF_REAL height;
	HPDF_REAL width;
	HPDF_UINT i;

	strcpy(fname, "test");
	strcat(fname, ".pdf");

	pdf = HPDF_New(error_handler, NULL);
	if (!pdf) {
		printf("error: cannot create PdfDoc object\n");
		return 1;
	}

	if (setjmp(env)) {
		HPDF_Free(pdf);
		return 1;
	}

	/* Add a new page object. */
	page = HPDF_AddPage(pdf);

	height = HPDF_Page_GetHeight(page);
	width = HPDF_Page_GetWidth(page);


	HPDF_Page_BeginText(page);
	HPDF_Page_MoveTextPos(page, 60, height - 105);

	// const char* samp_text = "abcdefg叽里呱啦";
	HPDF_UseCNSFonts(pdf);
	HPDF_UseCNSEncodings(pdf);
	HPDF_Font font = HPDF_GetFont(pdf, "SimSun", "GBK-EUC-H");
	HPDF_Page_SetFontAndSize(page, font, 32);
	HPDF_Page_ShowText(page, "五月，迎来了热情似火的夏天");
	HPDF_Page_MoveTextPos(page, 0, -20);
	HPDF_Page_EndText(page);
	HPDF_SaveToFile(pdf, fname);

	/* clean up */
	HPDF_Free(pdf);
	system("test.pdf");
	return 0;
}

