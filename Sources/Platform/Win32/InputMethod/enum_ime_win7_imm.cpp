#include <windows.h>
#include <imm.h>
#include <stdio.h>

#pragma comment(lib,"Imm32")

HKL g_hklRPC = NULL;


int main()
{
	// Find RPC hkl
	UINT nMaxHklCnt = GetKeyboardLayoutList(0, NULL);

	HKL* p_hklList = (HKL*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, nMaxHklCnt * sizeof(HKL));

	UINT nHklCnt = GetKeyboardLayoutList(nMaxHklCnt, p_hklList);

	LPSTR buffer;
	buffer = new char[255];
	memset(buffer, 0, 255);
	for (UINT i = 0; i < nHklCnt; i++) {
		if (LOWORD(p_hklList[i]) == 0x0804) {
			g_hklRPC = p_hklList[i];
			ImmGetDescriptionA(g_hklRPC, buffer, 255);
			puts(buffer);
			//break;
		}
	}

	HeapFree(GetProcessHeap(), NULL, p_hklList);

	//return (g_hklRPC == NULL) ? FALSE : TRUE;
	
	return 0;

}