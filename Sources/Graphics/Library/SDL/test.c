#include <stdio.h>
#include <string.h>
typedef struct
{
    int length;
    char **strs;
} vecstr;
vecstr vs;
void initiate()
{
    char filename[FILENAME_MAX] = "test.txt";
    vs.length = 0;
    vs.strs = NULL;
    FILE *fp = fopen(filename, "rb");
    while (!feof(fp))
    {
        char *line = (char *)malloc(BUFSIZ);
        memset(line, 0, BUFSIZ);
        fgets(line, BUFSIZ, fp);
        //printf("%d ",strlen(line));
        line[strlen(line) - 2] = '\0'; //去除\n
        //puts(line);
        vs.strs = (char **)realloc(vs.strs, ++(vs.length) * sizeof(char *));
        vs.strs[vs.length - 1] = line;
        //while(*line!=0)printf("%d ",*line),line++;
    }
    //printf("%d\n",vs.length);
}
int main()
{
    initiate();
    for (int i = 0; i < vs.length; i++)
    {
        printf("%s %d", vs.strs[i], i);
    }
    char *line = vs.strs[159];
    while (*line != 0)
        printf("%d ", *line), line++;
}