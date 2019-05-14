#include <stdio.h>
#include <windows.h>
#define NAME_LEN 100

#pragma comment(lib, "user32")
#pragma comment(lib, "advapi32")

int main()
{
	HKEY hKey;
	// LPCTSTR lpSubKey="Environment";

	// if(RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_READ, &hKey)!= ERROR_SUCCESS) {
	// return ;
	// }
	LPCTSTR lpSubKey = "SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment";

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		return;
	}
	char szValueName[NAME_LEN];
	BYTE szValue[NAME_LEN];
	LONG status;
	DWORD dwIndex = 0;
	DWORD dwSizeValueName = 100;
	DWORD dwSizeofValue = 100;
	DWORD Type;
	dwSizeValueName = NAME_LEN;
	dwSizeofValue = NAME_LEN;
	do
	{
		status = RegEnumValue(hKey, dwIndex++, szValueName, &dwSizeValueName, NULL, &Type,
							  szValue, &dwSizeofValue);
		if ((status == ERROR_SUCCESS))
		{
			printf("%s=%s\n", szValueName, szValue);
		}
		//每读取一次dwSizeValueName和dwSizeofValue都会被修改
		//注意一定要重置,否则会出现很离奇的错误,本人就试过因没有重置,出现读不了COM大于10以上的串口
		dwSizeValueName = NAME_LEN;
		dwSizeofValue = NAME_LEN;
	} while ((status != ERROR_NO_MORE_ITEMS));
	RegCloseKey(hKey);
}