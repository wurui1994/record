#include <stdio.h>
#include <windows.h>
#include <commdlg.h>
int main()
{
	static CHOOSECOLOR cc;
	static COLORREF crCustColors[16];
	cc.lStructSize=sizeof(cc);
	cc.hwndOwner=0;//父窗口 可为空
	cc.lpCustColors=crCustColors;
	cc.Flags=CC_ANYCOLOR;
	cc.hInstance=0;
	cc.lpTemplateName=0;
	cc.lpfnHook=0;
	cc.rgbResult=0;

	if(ChooseColor(&cc)){
		puts("OK");
		printf("%06X\n",cc.rgbResult);
	}
	return 0;
}