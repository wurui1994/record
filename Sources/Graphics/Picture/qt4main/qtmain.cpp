#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <QApplication>
#include <QWidget>
#include <QPainter>

using namespace std;
vector<string> vec;
int num = 0;
void initiate()
{
	//
	ifstream ifs("test.txt");
	string temp;
	int tempr, tempt;
	while (!ifs.eof()) {
		getline(ifs, temp);
		if (temp.length()>4)
			vec.push_back(temp);
		//cout<<temp<<endl;
	}
	ifs.close();
	//cout<<vec.size()<<endl;
}
class PaintedWidget : public QWidget
{
public:
	PaintedWidget();

protected:
	void paintEvent(QPaintEvent *event);
	//void repaint(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);
};
PaintedWidget::PaintedWidget()
{
	this->resize(640, 480);
	this->startTimer(0);
	this->setWindowTitle(tr("Paint Demo"));
}
void PaintedWidget::timerEvent(QTimerEvent *event) {
	
	//this->repaint();
	this->update();
}

void PaintedWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	if (num == vec.size())exit(0);
	QPixmap pixmap(vec[num++].c_str());
	painter.drawPixmap(QPoint(0, 0), pixmap);
}


int main(int argc, char *argv[])
{
	initiate();
	QApplication app(argc, argv);
	PaintedWidget w;
	w.show();
	return app.exec();
}
