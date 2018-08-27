#include <QApplication>
#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QLabel label;
	//C++11
	//string path = R"(D:\Software\MSYS2\home\wurui\python\guotu56\www.guotu56.com\uploads\allimg\150427\1-15042H20343-50.jpg)";
	//QPixmap pix(path.c_str()); 
	QPixmap pix(argv[1]); //图片路径
	label.setPixmap(pix);
	label.show();
	label.resize(640,480);
	return a.exec();
}