// tcc -run parsehtml.c test.xml
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/HTMLparser.h>

#pragma comment(lib, "xml2")

void traverse_dom_trees(xmlNode *a_node)
{
    xmlNode *cur_node = NULL;

    if (NULL == a_node)
    {
        //printf("Invalid argument a_node %p\n", a_node);
        return;
    }

    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
        if (cur_node->type == XML_ELEMENT_NODE)
        {
            /* Check for if current node should be exclude or not */
            if (strcmp(cur_node->name, "div") == NULL)
            {
                char *str = xmlGetProp(cur_node, "class");
                if (str)
                {
                    if (strcmp(str, "gallery_wrapper") == NULL)
                    {
                        char *buf = xmlBufferCreate();

                        // dump the node
                        xmlNodeDump(buf, cur_node->doc, cur_node, 0 /* level of indentation */, 0 /* disable formatting */);

                        char *result = strdup((char *)xmlBufferContent(buf));

                        printf("%s", result);
                    }
                }
            }
        }
        else if (cur_node->type == XML_TEXT_NODE)
        {
            /* Process here text node, It is available in cpStr :TODO: */
            //printf("node type: Text, node content: %s,  content length %d\n", (char *)cur_node->content, strlen((char *)cur_node->content));
        }
        traverse_dom_trees(cur_node->children);
    }
}

int main(int argc, char **argv)
{
    htmlDocPtr doc;
    xmlNode *roo_element = NULL;

    if (argc != 2)
    {
        printf("\nInvalid argument\n");
        return (1);
    }

    /* Macro to check API for match with the DLL we are using */
    LIBXML_TEST_VERSION

    doc = htmlReadFile(argv[1], NULL, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
    if (doc == NULL)
    {
        fprintf(stderr, "Document not parsed successfully.\n");
        return 0;
    }

    roo_element = xmlDocGetRootElement(doc);

    if (roo_element == NULL)
    {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }

    printf("Root Node is %s\n", roo_element->name);
    traverse_dom_trees(roo_element);

    xmlFreeDoc(doc);    // free document
    xmlCleanupParser(); // Free globals
    return 0;
}