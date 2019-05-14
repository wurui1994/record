#include <stdio.h>
#include <windows.h>
#include <commdlg.h>
int main()
{
	OPENFILENAME ofn;
	TCHAR szOpenFileNames[80*MAX_PATH];
	TCHAR szPath[MAX_PATH];
	TCHAR szFileName[80*MAX_PATH];
	TCHAR* p;
	int nLen = 0;
	ZeroMemory( &ofn, sizeof(ofn) );
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szOpenFileNames;
	ofn.nMaxFile = sizeof(szOpenFileNames);
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = TEXT("All Files(*.*)\0*.*\0");
	if( GetOpenFileName( &ofn ) ) {
		//把第一个文件名前的复制到szPath,即:
		//如果只选了一个文件,就复制到最后一个'\'
		//如果选了多个文件,就复制到第一个NULL字符
		lstrcpyn(szPath, szOpenFileNames, ofn.nFileOffset );
		//当只选了一个文件时,下面这个NULL字符是必需的.
		//这里不区别对待选了一个和多个文件的情况
		szPath[ofn.nFileOffset ] = '\0';
		nLen = lstrlen(szPath);
		if( szPath[nLen-1] != '\\' ) { //如果选了多个文件,则必须加上'//'
			lstrcat(szPath, TEXT("\\"));
		}
		p = szOpenFileNames + ofn.nFileOffset; //把指针移到第一个文件
		ZeroMemory(szFileName, sizeof(szFileName));
		while( *p ) {
			lstrcat(szFileName, szPath);  //给文件名加上路径
			lstrcat(szFileName, p);    //加上文件名
			lstrcat(szFileName, TEXT("\n")); //换行
			p += lstrlen(p) +1;     //移至下一个文件
		}
		MessageBox(NULL, szFileName, TEXT("MultiSelect"), MB_OK);
	}
	return 0;
}