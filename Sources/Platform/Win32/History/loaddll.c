#include <windows.h>
int main()
{
	HMODULE hm = LoadLibrary("user32.dll");
	if (hm)
	{
		//printf("Hello");
		FARPROC fm = GetProcAddress(hm, "MessageBoxA");
		fm(0, "h", "w", 0);
	}
	return 0;
}