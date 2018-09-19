#include <QtWidgets/QtWidgets>
//
class Widget : public QWidget
{
public:
	explicit Widget(QWidget *parent = 0)
		: QWidget(parent)
	{
		setWindowFlag(Qt::FramelessWindowHint, true);
	}
	//
	~Widget()
	{
	}
protected:
	void mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_lastGlobalPos = event->globalPos();
		}
		QWidget::mousePressEvent(event);
	}
	void mouseMoveEvent(QMouseEvent *event)
	{
		if (event->buttons() & Qt::LeftButton)
		{
			QPoint curGlobalPos = event->globalPos();
			QPoint nextPos = curGlobalPos - m_lastGlobalPos + pos();
			m_lastGlobalPos = curGlobalPos;
			move(nextPos);
			//
			event->accept();
		}
		QWidget::mouseMoveEvent(event);
	}
private:
	QPoint m_lastGlobalPos;
};
//
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Widget widget;
	widget.show();
	return app.exec();
}