#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024
BOOL GetDriverInfo(LPSTR szDrive);
//int WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nCmdShow)
int main(void)
{
	CHAR szLogicDriveStrings[BUFSIZE];
	PCHAR szDrive;

	ZeroMemory(szLogicDriveStrings, BUFSIZE);

	GetLogicalDriveStrings(BUFSIZE - 1, szLogicDriveStrings);
	szDrive = (PCHAR)szLogicDriveStrings;
	//puts(szDrive)

	do
	{
		puts(szDrive);
		if (!GetDriverInfo(szDrive))
		{
			printf("\nGet Volume Information Error:%d", GetLastError());
		}

		szDrive += (lstrlen(szDrive) + 1);
	} while (*szDrive != '\x00');

	//system("PAUSE");
	return 0;
}

BOOL GetDriverInfo(LPSTR szDrive)
{
	UINT uDriverType;
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximumComponentlength;
	DWORD dwFileSystemFlags;
	CHAR szFileSystemNameBuffer[BUFSIZE];
	CHAR szDriveName[MAX_PATH];

	printf("\n%s\n", szDrive);
	uDriverType = GetDriveType(szDrive);

	switch (uDriverType)
	{
	case DRIVE_UNKNOWN:
		printf("The driver type cannot be determined!");
		break;
	case DRIVE_NO_ROOT_DIR:
		printf("The root path is invalid,for example,no volume is mounted at the path");
		break;
	case DRIVE_REMOVABLE:
		printf("The drive is a type that has removable media,for example:a floppy drive or removable hard disk");
		break;
	case DRIVE_FIXED:
		printf("The drive is a type that cannot be removed, for example,a fixed hard drive");
		break;
	case DRIVE_REMOTE:
		printf("This drive is a remote(network) drive");
		break;
	case DRIVE_CDROM:
		printf("This drive is a CD-ROM drive.");
		break;
	case DRIVE_RAMDISK:
		printf("This drive is a RAM disk");
		break;
	default:
		break;
	}

	if (!(GetVolumeInformation(
			szDrive,
			szDriveName,
			MAX_PATH,
			&dwVolumeSerialNumber,
			&dwMaximumComponentlength,
			&dwFileSystemFlags,
			szFileSystemNameBuffer,
			BUFSIZE)))
	{
		return FALSE;
	}

	if (0 != lstrlen(szDriveName))
	{
		printf("\nDrive Name is %s.\n", szDriveName);
	}

	printf("\nVolume Serial is %u.", dwVolumeSerialNumber);
	printf("\nMaximum Component Length is %u.", dwMaximumComponentlength);
	printf("\nSystem Type is %s.\n", szFileSystemNameBuffer);

	if (dwFileSystemFlags & FILE_VOLUME_QUOTAS)
	{

		printf("The file system supports disk Quotas.\n");
	}

	if (dwFileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS)
	{
		printf("The file system does not support volume mount points.\n");
	}

	if (dwFileSystemFlags & FILE_CASE_SENSITIVE_SEARCH)
	{
		printf("The file system supports case-sentitive file name.\n");
	}

	printf("...\n");

	return TRUE;
}