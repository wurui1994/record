PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE t(id int primary key,msg varchar(128));
INSERT INTO "t" VALUES(1,'Ady Liu');
INSERT INTO "t" VALUES(2,'John');
INSERT INTO "t" VALUES(3,'Tom');
INSERT INTO "t" VALUES(4,'Alice');
COMMIT;
