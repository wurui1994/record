#include <stdio.h>
#include <windows.h>
int main()
{
	HKEY hKey;
	DWORD dwtype, BufferSize;
	char *buffer;
	int len;
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_READ|KEY_WRITE, &hKey);
	char* string="D:\\Program\\msys2\\mingw32\\share\\qt5\\plugins";
	len=strlen(string);
	char* Variable="QT_PLUGIN_PATH";
	RegSetValueEx(hKey, Variable,0,REG_EXPAND_SZ,(BYTE *)string,len);
	//long lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment", 0, KEY_READ, &hKey);
	// char* string="C:\\ProgramData\\Oracle\\Java\\javapath;%SystemRoot%\\system32;%SystemRoot%;%SystemRoot%\\System32\\Wbem;%SYSTEMROOT%\\System32\\WindowsPowerShell\\v1.0\\;%USERPROFILE%\\.dnx\\bin;C:\\Program Files\\Microsoft DNX\\Dnvm\\;C:\\Program Files (x86)\\Windows Kits\\8.1\\Windows Performance Toolkit\\;C:\\Program Files (x86)\\Microsoft SQL Server\\120\\Tools\\Binn\\;C:\\Program Files (x86)\\Microsoft SQL Server\\130\\Tools\\Binn\\;C:\\Program Files (x86)\\Microsoft Emulator Manager\\1.0\\;C:\\Program Files (x86)\\nodejs\\;C:\\Program Files\\Git\\cmd";
	// len=strlen(string);
	// printf("%d\n",len);
	// lRet=RegSetValueEx(hKey, "Path",0,REG_EXPAND_SZ,(BYTE *)string,len);
	if (lRet == ERROR_SUCCESS) {
	//读取键值
	RegQueryValueEx(hKey, Variable, 0, &dwtype, (BYTE*)buffer, &BufferSize);//第一次获取长度
	printf("%d\n",BufferSize);
	buffer=(char*)malloc(BufferSize);//分配内存
	if(RegQueryValueEx(hKey, Variable, 0, &dwtype, (BYTE*)buffer, &BufferSize)==ERROR_SUCCESS)//第一次获取值
		printf("%s\n",buffer);
	//关闭键
	RegCloseKey(hKey);
	}
}