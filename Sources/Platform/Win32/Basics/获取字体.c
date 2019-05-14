#include <stdio.h>
#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>
int main()
{
	CHOOSEFONT cf;            // common dialog box structure
	static LOGFONT lf;        // logical font structure
	static DWORD rgbCurrent;  // current text color
	HFONT hfont, hfontPrev;
	DWORD rgbPrev;

// Initialize CHOOSEFONT
	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof (cf);
	cf.hwndOwner = 0;
	cf.lpLogFont = &lf;
	cf.rgbColors = rgbCurrent;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

	if (ChooseFont(&cf)==TRUE) {
		puts("OK");
		printf("%s\n",lf.lfFaceName);
		printf("%d\n",lf.lfItalic);
	}
	return 0;
}