// g++ *.cpp -ldl && ./a.out
// clang++ *.cpp -framework CoreFoundation && ./a.out
// cl *.cpp /w /EHsc /nologo /Fe:main.exe && main.exe
#include <iostream>
#include "Core.h"

using namespace std;

#if defined(UNICODE) || defined(_UNICODE)
#define output wcout
#else
#define output cout
#endif

int main(int argc, Char *argv[])
{
	Core c;
	if(argc < 2)
	{
		c.Menu_File_Open_File(argv[0]);
	}
	else
	{
		c.Menu_File_Open_File(argv[1]);
	}
	c.Menu_View_Text();
	output << c.Inform_Get() << endl;
	return 0;
}
