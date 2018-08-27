//tcc -lxml2 -run libxml2.c test.xml
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#pragma comment(lib,"xml2")

int main(int argc, char **argv)
{
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    char *name = NULL;
    char *value = NULL;
    xmlKeepBlanksDefault(0);
    if (argc < 2)
    {
        printf("ERROR: argc must be 2 or above.\n");
        return -1;
    }
    //create Dom tree
    doc = xmlParseFile(argv[1]);
    if (doc == NULL)
    {
        printf("ERROR: Loading xml file failed.\n");
        exit(1);
    }
    // get root node
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL)
    {
        printf("ERROR: empty file\n");
        xmlFreeDoc(doc);
        exit(2);
    }
    //walk the tree
    cur = cur->xmlChildrenNode; //get sub node
    while (cur != NULL)
    {
        name = (char *)(cur->name);
        value = (char *)xmlNodeGetContent(cur);
        printf("name is: %s, value is: %s\n", name, value);
        // xmlFree(value);
        // tcc: error: undefined symbol 'xmlFree', missing __declspec(dllimport)?
        cur = cur->next;
    }
    // release resource of xml parser in libxml2
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}