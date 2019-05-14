#include <Windows.h>
#include <stdio.h>

int main(void)
{
	CHAR szDrive[BUFSIZ];
	DWORD iLength;
	INT iSub;

	ZeroMemory(szDrive, BUFSIZ);
	iLength = GetLogicalDriveStringsA(BUFSIZ - 1, szDrive);
	for (iSub = 0; iSub < iLength; iSub += 4)
	{
		if (GetDriveType(szDrive + iSub) == DRIVE_FIXED)
			printf("%s\n", szDrive + iSub);
	}
	//printf("\n");
	return 0;
}