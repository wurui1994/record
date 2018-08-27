#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
file_exists_p (const char *filename)
{
#ifdef HAVE_ACCESS
    return access (filename, F_OK) >= 0;
#else
    struct stat buf;
    return stat (filename, &buf) >= 0;
#endif
}

// char *
// strdupdelim (const char *beg, const char *end)
// {
// if (beg && beg <= end)
// {
// char *res = malloc (end - beg + 1);
// memcpy (res, beg, end - beg);
// res[end - beg] = '\0';
// return res;
// }

// return strdup("");
// }

/* Create DIRECTORY.  If some of the pathname components of DIRECTORY
   are missing, create them first.  In case any mkdir() call fails,
   return its error status.  Returns 0 on successful completion.

   The behaviour of this function should be identical to the behaviour
   of `mkdir -p' on systems where mkdir supports the `-p' option.  */
int
make_directory (const char *directory)
{
    int i, ret, quit = 0;
    char *dir;

    /* Make a copy of dir, to be able to write to it.  Otherwise, the
           function is unsafe if called with a read-only char *argument.  */
    dir = strdup(directory);

    /* If the first character of dir is '/', skip it (and thus enable
           creation of absolute-pathname directories.  */
    for (i = (*dir == '/'); 1; ++i)
    {
        for (; dir[i] && dir[i] != '/'; i++)
            ;
        if (!dir[i])
            quit = 1;
        dir[i] = '\0';
        /* Check whether the directory already exists.  Allow creation of
                   of intermediate directories to fail, as the initial path components
                   are not necessarily directories!  */
        if (!file_exists_p (dir))
            ret = mkdir (dir);
        else
            ret = 0;
        if (quit)
            break;
        else
            dir[i] = '/';
    }
    free(dir);
    return ret;
}

int
mkalldirs (const char *path)
{
    const char *p;
    char *t;
    struct stat st;
    int res;

    p = path + strlen (path);
    for (; *p != '/' && p != path; p--)
        ;

    /* Don't create if it's just a file.  */
    if ((p == path) && (*p != '/'))
        return 0;
    t = strdupdelim (path, p);

    /* Check whether the directory exists.  */
    if ((stat (t, &st) == 0))
    {
        if (S_ISDIR (st.st_mode))
        {
            free (t);
            return 0;
        }
        else
        {
            /* If the dir exists as a file name, remove it first.  This
                           is *only* for Wget to work with buggy old CERN http
                           servers.  Here is the scenario: When Wget tries to
                           retrieve a directory without a slash, e.g.
                           http://foo/bar (bar being a directory), CERN server will
                           not redirect it too http://foo/bar/ -- it will generate a
                           directory listing containing links to bar/file1,
                           bar/file2, etc.  Wget will lose because it saves this
                           HTML listing to a file `bar', so it cannot create the
                           directory.  To work around this, if the file of the same
                           name exists, we just remove it and create the directory
                           anyway.  */
            //DEBUGP (("Removing %s because of directory danger!\n", t));
            if (unlink (t))
                printf ("Failed to unlink %s (%d): %s\n",
                        t, errno, strerror(errno));
        }
    }
    res = make_directory (t);
    if (res != 0)
        printf ("%s: %s", t, strerror (errno));
    free (t);
    return res;
}

char* MakeDirsAndReturnPath(const char* url)
{
    //char url[BUFSIZ] = "http://www.meitulu.com/t/loli/";
    char *filename = malloc(BUFSIZ);
    char http[] = "http://";
    if(strncmp(url,http,strlen(http)))
        return NULL;
    char *path =  url + strlen(http);

    strcpy(filename,path);
    char c = url[strlen(url)-1];
    char htm[] = ".htm";
    char html[] = ".html";
    char aspx[] = ".aspx";
    if(c == '/')
    {
        strcat(filename,"index.html");
    }
    else
    {
        char *slash = strrchr(filename,'/');
        if(slash)
        {
            char dot = strchr(slash,'.');
            if(!dot)
            {
                strcat(filename,"/index.html");
            }
        }
    }
    mkalldirs(filename);
    return filename;
}
