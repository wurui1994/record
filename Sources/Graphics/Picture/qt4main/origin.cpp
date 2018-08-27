#include <QApplication>
#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QLabel label;
	//C++11
	//string path = R"(test.jpg)";
	//QPixmap pix(path.c_str()); 
	QPixmap pix(argv[1]); //图片路径
	label.setPixmap(pix);
	label.show();
	label.resize(640,480);
	return a.exec();
}