// tcc -run expat.c test2.xml
#include <stdio.h>
#include <expat.h>

#pragma comment(lib,"expat")
#pragma warning(disable:4996)
#define XML_FMT_INT_MOD "l"

static void XMLCALL startElement(void *userData, const char *name, const char **atts)
{
    int i;
    int *depthPtr = (int *)userData;
    for (i = 0; i < *depthPtr; i++)
        printf(" ");
    printf(name);
    *depthPtr += 1;
    for(i=0; atts[i]!=0; i+=2)
    {
        printf(" %s=%s",atts[i],atts[i+1]);
    }
    printf("\n");
}
static void XMLCALL endElement(void *userData, const char *name)
{
    int *depthPtr = (int *)userData;
    *depthPtr -= 1;
}
int main(int argc, char *argv[])
{
    char buf[BUFSIZ];
    XML_Parser parser = XML_ParserCreate(NULL);
    int done;
    int depth = 0;
    XML_SetUserData(parser, &depth);
    XML_SetElementHandler(parser, startElement,endElement);
    FILE* pFile= argc<2 ?stdin : fopen(argv[1],"rb");
    do
    {
        int len = (int)fread(buf, 1, sizeof(buf), pFile);
        done = len < sizeof(buf);
        if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR)
        {
            fprintf(stderr,"%s at line %"XML_FMT_INT_MOD "u\n",
                    XML_ErrorString(XML_GetErrorCode(parser)),
                    XML_GetCurrentLineNumber(parser));
            return 1;
        }
    }
    while (!done);
    XML_ParserFree(parser);
    fclose(pFile);
    return 0;
}