# import sqlite3
# db = sqlite3.connect('storage.db')
# db.execute("select name from sqlite_master").fetchall()
# db.execute("PRAGMA table_info('file_transfers')").fetchall()
import sqlite3
db = sqlite3.connect('storage.db')
for e in db.execute("select name from sqlite_master").fetchall():
	print(e[0])
	for record in db.execute("PRAGMA table_info('" + e[0] + "')").fetchall():
		print(record)

