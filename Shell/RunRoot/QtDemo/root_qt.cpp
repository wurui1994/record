//root -e ".include /usr/include/qt" -e ".L /usr/lib/libQt5Core.so" -e "#include <QtCore/QtCore>" -l -q -b root_qt.cpp
//root -e ".include /usr/include/qt" -e ".L /usr/lib/libQt5Core.so" -l -q -b root_qt.cpp
//root -l
//.include /usr/include/qt
//.L /usr/lib/libQt5Core.so
#include <QtCore/QtCore>
void root_qt()
{
	QString s="hello";
	qDebug()<<s.size();
	cout<<s.toStdString()<<endl;
}

// test();