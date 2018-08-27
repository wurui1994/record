#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "advapi32")

int main()
{
    HKEY hKey;
    LPCTSTR lpRun = "CLSID";
    DWORD state, dwtype, sizeBuff;
    long lRet;
    char reBuff[128] = {0};
    HKEY hSubKey;
    DWORD dwIndex = 0;
    long lResult;
    int i = 1;

    lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, lpRun, 0, KEY_READ, &hSubKey); // 打开注册表
    if (ERROR_SUCCESS == lResult)
    {
        TCHAR szKeyName[256] = {0};
        DWORD cbName = 256 * sizeof(TCHAR);

        lResult = RegEnumKeyEx(hSubKey, dwIndex, szKeyName, &cbName, 0, NULL, NULL, NULL); // 获取字段
        while (lResult == ERROR_SUCCESS && lResult != ERROR_MORE_DATA)
        {

            printf("%d %s\n", i, szKeyName);

            dwIndex = dwIndex + 1; // 改变dwIndex，循环获取下移字段
            cbName = 256 * sizeof(TCHAR);
            lResult = RegEnumKeyEx(hSubKey, dwIndex, szKeyName, &cbName, 0, NULL, NULL, NULL);

            i++;
        }
        printf("%d\n", i);
        RegCloseKey(hSubKey); // 关闭注册表
        return TRUE;
    }

    RegCloseKey(hSubKey);

    /*创建键***************************************************************************/
    ////创建键
    //lRet = RegCreateKeyEx(HKEY_CURRENT_USER,lpRun,0,NULL,0,0,NULL,&hKey,&state);
    //if(lRet == ERROR_SUCCESS)
    //{
    //    if(state == REG_CREATED_NEW_KEY)
    //        cout<<"表项创建成功"<<endl;
    //
    //    //关闭键
    //    RegCloseKey(hKey);
    //}

    /*打开/修改键值********************************************************************/
    ////打开键
    //lRet= RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey);
    //if(lRet == ERROR_SUCCESS)
    //{
    //    //创建或者修改键值
    //    RegSetValueEx(hKey, "test",0,REG_SZ,(BYTE *)"success",10);
    //
    //    //关闭键
    //    RegCloseKey(hKey);
    //}

    /*读取键值*************************************************************************/
    //打开键
    // lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_READ, &hKey);
    // if (lRet == ERROR_SUCCESS) {
    //     sizeBuff = sizeof(reBuff);

    //     //读取键值
    //     if (RegQueryValueEx(hKey, "Microsoft", 0, &dwtype, (BYTE*)reBuff, &sizeBuff) == ERROR_SUCCESS)
    //         cout << reBuff << endl;

    //     //关闭键
    //     RegCloseKey(hKey);
    // }

    /*删除键值************************************************************************/
    ////打开键
    //lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey);
    //if(lRet==ERROR_SUCCESS)
    //{
    //    //删除键
    //    RegDeleteValue(hKey,"test");
    //
    //    //关闭键
    //    RegCloseKey(hKey);
    //}

    /*删除键**************************************************************************/
    //RegDeleteKey(HKEY_CURRENT_USER, lpRun);

    //system("pause");
    return 0;
}