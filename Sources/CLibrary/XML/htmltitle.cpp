/*
g++ -Wall -I/opt/curl/include -I/opt/libxml/include/libxml2 htmltitle.cpp \
-o htmltitle -L/opt/curl/lib -L/opt/libxml/lib -lcurl -lxml2
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>

#include <locale.h>

//
//  Case-insensitive string comparison
//

#ifdef _MSC_VER
#define COMPARE(a, b) (!_stricmp((a), (b)))
#else
#define COMPARE(a, b) (!strcasecmp((a), (b)))
#endif

//
//  libxml callback context structure
//

struct Context
{
	Context() : addTitle(false) { }

	bool addTitle;
	std::string title;
};

//
//  libcurl variables for error strings and returned data

static char errorBuffer[CURL_ERROR_SIZE];
static std::string buffer;

//
//  libcurl write callback function
//

static int writer(char *data, size_t size, size_t nmemb,
	std::string *writerData)
{
	if (writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);

	return size * nmemb;
}

//
//  libcurl connection initialization
//

static bool init(CURL *&conn, char *url)
{
	CURLcode code;

	conn = curl_easy_init();

	if (conn == NULL) {
		fprintf(stderr, "Failed to create CURL connection\n");
		exit(EXIT_FAILURE);
	}

	code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
	if (code != CURLE_OK) {
		fprintf(stderr, "Failed to set error buffer [%d]\n", code);
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_URL, url);
	if (code != CURLE_OK) {
		fprintf(stderr, "Failed to set URL [%s]\n", errorBuffer);
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
	if (code != CURLE_OK) {
		fprintf(stderr, "Failed to set redirect option [%s]\n", errorBuffer);
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
	if (code != CURLE_OK) {
		fprintf(stderr, "Failed to set writer [%s]\n", errorBuffer);
		return false;
	}

	code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &buffer);
	if (code != CURLE_OK) {
		fprintf(stderr, "Failed to set write data [%s]\n", errorBuffer);
		return false;
	}

	return true;
}

//
//  libxml start element callback function
//

static void StartElement(void *voidContext,
	const xmlChar *name,
	const xmlChar **attributes)
{
	Context *context = (Context *)voidContext;

	if (COMPARE((char *)name, "TITLE")) {
		context->title = "";
		context->addTitle = true;
	}
	(void)attributes;
}

//
//  libxml end element callback function
//

static void EndElement(void *voidContext,
	const xmlChar *name)
{
	Context *context = (Context *)voidContext;

	if (COMPARE((char *)name, "TITLE"))
		context->addTitle = false;
}

//
//  Text handling helper function
//

static void handleCharacters(Context *context,
	const xmlChar *chars,
	int length)
{
	if (context->addTitle)
		context->title.append((char *)chars, length);
}

//
//  libxml PCDATA callback function
//

static void Characters(void *voidContext,
	const xmlChar *chars,
	int length)
{
	Context *context = (Context *)voidContext;

	handleCharacters(context, chars, length);
}

//
//  libxml CDATA callback function
//

static void cdata(void *voidContext,
	const xmlChar *chars,
	int length)
{
	Context *context = (Context *)voidContext;

	handleCharacters(context, chars, length);
}

//
//  libxml SAX callback structure
//

static htmlSAXHandler saxHandler =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	StartElement,
	EndElement,
	NULL,
	Characters,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	cdata,
	NULL
};

//
//  Parse given (assumed to be) HTML text and return the title
//

static void parseHtml(const std::string &html,
	std::string &title)
{
	/*cout << html << endl;*/
	htmlParserCtxtPtr ctxt;
	Context context;

	ctxt = htmlCreatePushParserCtxt(&saxHandler, &context, "", 0, "",
		XML_CHAR_ENCODING_NONE);

	htmlParseChunk(ctxt, html.c_str(), html.size(), 0);
	htmlParseChunk(ctxt, "", 0, 1);

	htmlFreeParserCtxt(ctxt);
	//puts(context.title.c_str());
	title = context.title;
}

std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";  
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");
	return result;
}

// 1、将GBK转换成UTF8

std::string GBKToUTF8(const std::string& strGBK)
{
	std::string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

// 2、将UTF8转换成GBK

std::string UTF8ToGBK(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	wchar_t * wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPSTR)strUTF8.c_str(), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	//strUTF8 = szGBK;
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}

int main(int argc, char *argv[])
{
	CURL *conn = NULL;
	CURLcode code;
	std::string title;

	// Ensure one argument is given

	//if (argc != 2) {
	//	fprintf(stderr, "Usage: %s <url>\n", argv[0]);
	//	exit(EXIT_FAILURE);
	//}

	curl_global_init(CURL_GLOBAL_DEFAULT);

	// Initialize CURL connection
	argv[1] = "www.baidu.com";
	if (!init(conn, argv[1])) {
		fprintf(stderr, "Connection initializion failed\n");
		exit(EXIT_FAILURE);
	}

	// Retrieve content for the URL

	code = curl_easy_perform(conn);
	curl_easy_cleanup(conn);

	if (code != CURLE_OK) {
		fprintf(stderr, "Failed to get '%s' [%s]\n", argv[1], errorBuffer);
		exit(EXIT_FAILURE);
	}

	// Parse the (assumed) HTML code
	parseHtml(buffer, title);

	//setlocale(LC_ALL, "zh_CN");
	//setlocale(LC_ALL, "zh_CN.UTF-8");
	// Display the extracted title
	printf("%s\n", UTF8ToGBK(title).c_str());
	//MessageBoxW(0,s2ws(title).c_str(), 0, 0);

	return EXIT_SUCCESS;
}
