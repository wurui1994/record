#include <QtWidgets/QtWidgets>
#include <CheckBoxHeader.h>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QTableWidget table;
	table.setRowCount(4);
	table.setColumnCount(3);

	CheckboxHeader *header = new CheckboxHeader(Qt::Horizontal, &table);
	table.setHorizontalHeader(header);
	table.show();
	return app.exec();
}