// https://bugreports.qt.io/browse/QTBUG-63498
#include <QCoreApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	auto db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(":memory:");
	db.open();
	QSqlQuery query;
	qDebug() << query.exec("select 1 as a");
	qDebug() << query.next();
	qDebug() << query.value(0);
	qDebug() << query.exec("select json('{}')");
	qDebug() << query.next();
	qDebug() << query.value(0);
}