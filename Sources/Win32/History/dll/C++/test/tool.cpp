// tool.cpp : 定义 DLL 应用程序的导出函数。
//

#include "tool.h"


// 这是导出变量的一个示例
TOOL_API int ntool=0;

// 这是导出函数的一个示例。
TOOL_API int fntool(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 tool.h
Ctool::Ctool()
{
	return;
}
int Ctool::sub(int a,int b)
{

	return a-b;
}
int Ctool::div(int a,int b)
{

	return a/b;
}

TOOL_API int add(int a,int b)
{

	return a+b;
}

TOOL_API int mul(int a,int b)
{

	return a*b;
}
//常规的dll是不支持类的导出的.只支持c风格的函数的导出.要弄MFC DLL工程才行
extern "C" TOOL_API Ctool *GetCTool()
{

	return new Ctool();
}