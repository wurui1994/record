#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;
int main()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	cout << setw(20) << "处理器掩码: " << systemInfo.dwActiveProcessorMask << endl
	     << setw(20) << "处理器个数: " << systemInfo.dwNumberOfProcessors << endl
	     << setw(20) << "处理器分页大小: " << systemInfo.dwPageSize << endl
	     << setw(20) << "处理器类型: " << systemInfo.dwProcessorType << endl
	     << setw(20) << "最大寻址单元: " << systemInfo.lpMaximumApplicationAddress << endl
	     << setw(20) << "最小寻址单元: " << systemInfo.lpMinimumApplicationAddress << endl
	     << setw(20) << "处理器等级: " << systemInfo.wProcessorLevel << endl
	     << setw(20) << "处理器版本: " << systemInfo.wProcessorRevision << endl;
	return 0;
}