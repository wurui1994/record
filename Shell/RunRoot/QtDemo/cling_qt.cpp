//cling -I/usr/include/qt -lQt5Core -fPIC cling_qt.cpp
#include <QtCore/QtCore>
#include <iostream>
using namespace std;
void cling_qt()
{
	QString s = "hello";
	qDebug()<<s.size();
	cout<<s.toStdString()<<endl;
}