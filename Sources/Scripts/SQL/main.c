#include <stdio.h>
#include <sqlite3.h>

int main(int argc,char *argv[])
{
	const char *sql_create_table="create table t(id int primary key,msg varchar(128))";
	char *errmsg = 0;
	int ret = 0;

	sqlite3 *db = 0;
	ret = sqlite3_open("./sqlite3-demo.db",&db);
	if(ret != SQLITE_OK) {
		fprintf(stderr,"Cannot open db: %s\n",sqlite3_errmsg(db));
		return 1;
	}
	printf("Open database\n");

	// ret = sqlite3_exec(db,sql_create_table,NULL,NULL,&errmsg);
	// if(ret != SQLITE_OK) {
		// fprintf(stderr,"create table fail: %s\n",errmsg);
	// }
	//
	ret = sqlite3_exec(db,"insert into t(id,msg) values(1,'Ady Liu')",NULL,NULL,&errmsg);
	ret = sqlite3_exec(db,"insert into t(id,msg) values(2,'John')",NULL,NULL,&errmsg);
	ret = sqlite3_exec(db,"insert into t(id,msg) values(3,'Tom')",NULL,NULL,&errmsg);
    printf("Insert a record %s\n",ret == SQLITE_OK ? "OK":"FAIL");
	char **dbresult;
	int i,j,nrow,ncolumn,index;
	//select table
	ret = sqlite3_get_table(db,"select * from t",&dbresult,&nrow,&ncolumn,&errmsg);
	if(ret == SQLITE_OK) {
		printf("query %i records.\n",nrow);
		index=ncolumn;
		for(i=0; i<nrow; i++) {
			printf("[%2i]",i);
			for(j=0; j<ncolumn; j++) {
				printf(" %X ",dbresult[index]);
				printf(" %s",dbresult[index]);
				index++;
			}
			printf("\n");
		}
	}
	sqlite3_free_table(dbresult);
	sqlite3_free(errmsg);
	sqlite3_close(db);

	printf("Close database\n");

	return 0;
}