#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")
vector<string> vec;
int num = 0;
int GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
	UINT num = 0;  // number of image encoders
	UINT size = 0; // size of the image encoder array in bytes

	ImageCodecInfo *pImageCodecInfo = NULL;

	//2.获取GDI+支持的图像格式编码器种类数以及ImageCodecInfo数组的存放大小
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1; // Failure

	//3.为ImageCodecInfo数组分配足额空间
	pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1; // Failure

	//4.获取所有的图像编码器信息
	GetImageEncoders(num, size, pImageCodecInfo);

	//5.查找符合的图像编码器的Clsid
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j; // Success
		}
	}

	//6.释放步骤3分配的内存
	free(pImageCodecInfo);
	return -1; // Failure
}

wstring StringToWstring(string str)
{
	string temp = str;
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL, 0);
	wchar_t *wszUtf8 = new wchar_t[len + 1];
	wstring szDst,
		memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
	szDst = wszUtf8;
	return szDst;
}

void draw_image(const char *file)
{

	int width, height;
	size_t len = strlen(file) + 1;
	size_t converted = 0;
	wchar_t *WStr;
	string savename = file;
	savename += ".bmp";
	WStr = (wchar_t *)malloc(len * sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, len, file, _TRUNCATE);
	//加载图像
	Image image(WStr);
	//取得宽度和高度
	width = image.GetWidth();
	height = image.GetHeight();
	CLSID encoderClsid;
	GetEncoderClsid(L"image/bmp", &encoderClsid);
	wstring savename2 = StringToWstring(savename);
	image.Save(savename2.c_str(), &encoderClsid, NULL);
	//cout<<width<<" "<<height<<endl;
	return;
}
void encode(void)
{
	int len = vec.size();
	for (int i = 0; i < len; i++)
		draw_image(vec[i].c_str());
}
void calctime(void (*fun)(void))
{
	clock_t st, et;
	st = clock();
	fun();
	et = clock();
	cout << double(et - st) / CLOCKS_PER_SEC << endl;
}
void initiate()
{
	//
	ifstream ifs("test.txt");
	string temp;
	int tempr, tempt;
	while (!ifs.eof())
	{
		getline(ifs, temp);
		if (temp.length() > 4)
			vec.push_back(temp);
		//cout<<temp<<endl;
	}
	ifs.close();
}
int main()
{

	//GdiPlus初始化
	ULONG_PTR gdipludToken;
	GdiplusStartupInput gdiplusInput;
	GdiplusStartup(&gdipludToken, &gdiplusInput, NULL);
	//
	initiate();
	//
	calctime(encode);
	//GdiPlus 取消初始化
	GdiplusShutdown(gdipludToken);

	return 0;
}