#include <gdbm.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#define ISBN_MAX 13
#define AUTHOR_MAX 50
#define TITLE_MAX 50
#define DB_FILE_BLOCK "book_data"

typedef struct
{ /*定义图书结构体 */
	char isbn[ISBN_MAX + 1];
	char author[AUTHOR_MAX + 1];
	char title[TITLE_MAX + 1];
	int numb;
} book_entry;

int main()
{
	book_entry newbook; /*创建新的图书记录，并赋值 */
	memset(&newbook, '\0', sizeof(newbook));
	strncpy(newbook.isbn, "9787302184942", ISBN_MAX);
	strncpy(newbook.author, "Microsoft Research Asia", AUTHOR_MAX);
	strncpy(newbook.title, "Microsoft's Dream Works", TITLE_MAX);
	newbook.numb = 735;

	datum key, data;				 /*datum结构体有两个成员：dptr指向存储的数据，dsize记录数据的大小 */
	key.dptr = (char *)newbook.isbn; /*用ISBN作key */
	key.dsize = ISBN_MAX;
	data.dptr = (char *)&newbook; /*用整条数据记录作value */
	data.dsize = sizeof(newbook);

	GDBM_FILE dbm_ptr;
	/*打开数据库（跟打开文件很相似），返回数据库句柄 */
	dbm_ptr = gdbm_open(DB_FILE_BLOCK,	 /*文件名 */
						0,				   /*文件大小，设为0时GDBM将使用文件系统的统计块大小 */
						GDBM_WRCREAT,	  /*读写模式。WRCREAT读写，数据库文件不存在时创建；READER读；WRITER写 */
						S_IRUSR | S_IWUSR, /*权限标志位 */
						NULL			   /*出错时的空参数回调函数 */
	);
	/*把记录存入数据库 */
	gdbm_store(dbm_ptr,		/*数据库句柄 */
			   key,			/*key值 */
			   data,		/*value值 */
			   GDBM_REPLACE /*如果是GDBM_INSERT则插入重复记录会出错；GDBM——REPLACE则只是覆盖原先存在的相同记录 */
	);

	char isbnarr[ISBN_MAX + 1] = {0};
	char *isbn = isbnarr;
	puts("请输入你要查询图书的ISBN号:");
	scanf("%s", isbn);
	key.dptr = (char *)isbn;
	key.dsize = ISBN_MAX;
	/*数据库查询 */
	data = gdbm_fetch(dbm_ptr, key); /*参建：数据库句柄的key值 */
	if (data.dsize == 0)
		printf("查无结果\n");
	else
	{
		memset(&newbook, 0, sizeof(newbook));
		memcpy(&newbook, data.dptr, data.dsize); /*将从数据库读到的记录赋给book_entry结构体 */
		printf("%s\t%s\t%s\t%d\n", newbook.isbn, newbook.author,
			   newbook.title, newbook.numb);
	}

	/*关闭数据库 */
	gdbm_close(dbm_ptr);
}