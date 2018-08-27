// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 TOOL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// TOOL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef TOOL_EXPORTS
#define TOOL_API  /**extern "C"*/ __declspec(dllexport)
#else
#define TOOL_API /**extern "C"*/ //__declspec(dllimport)
#endif

//删除tool.def文件，项目=》属性=》连接器=》输入=》模块定义文件
// 此类是从 tool.dll 导出的
class TOOL_API Ctool {
public:
	Ctool(void);
	
	//可以单独导出类中的函数,导出函数必须是public权限，才可以给其他程序访问
	/**TOOL_API*/ int sub(int a,int b);
	int div(int a,int b);
};

extern TOOL_API int ntool;

TOOL_API int /**_stdcall */ fntool(void);//这里可以修改调用约定，包括_stdcall(WINAPI),pascal,__cdecl __fastcall

TOOL_API int   add(int a,int b);

TOOL_API int mul(int a,int b);

extern "C" TOOL_API Ctool* GetCTool(); //获取类TestDll的对象
