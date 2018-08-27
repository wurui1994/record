#include <QtWidgets/QtWidgets>

class MessageWidget :public QWidget {
public:
	MessageWidget(QWidget* parent = nullptr, const QString& text ="",const QSize& size = QSize(200,80),
		const QRect& rect = qApp->desktop()->availableGeometry(), int timeout = 3000)
		:QWidget(parent), m_label(nullptr)
	{
		m_timeout = timeout;
		m_rect = rect;
		m_size = size;

		setWindowOpacity(0.6);
		setWindowFlags(Qt::FramelessWindowHint);

		m_label =  new QLabel(this);
		m_label->setText(text);
		m_label->setAlignment(Qt::AlignCenter);
		m_label->setStyleSheet("QLabel {font-family:Consolas;color:white;"
			"background-color: black;border: 0.5px solid black; border-radius: 10px;}");	
		//
		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget(m_label);
		layout->setMargin(0);
		//
		setLayout(layout);
	}
	//
	void setText(const QString& text)
	{
		if (m_label)
		{
			m_label->setText(text);
		}
	}
	//
	void setSize(const QSize& size)
	{
		m_size = size;
	}
	//
	void setRect(const QRect& rect)
	{
		m_rect = rect;

	}
	//
	void setTimeOut(int timeout)
	{
		m_timeout = timeout;
	}
	//
	void show()
	{
		setGeometry(QStyle::alignedRect(Qt::LeftToRight,
			Qt::AlignCenter, m_size, m_rect));
		QTimer::singleShot(m_timeout, this, [this]() {hide(); });
		QWidget::show();
	}
private:
	QLabel* m_label;
	QRect m_rect;
	QSize m_size;
	int m_timeout;
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QMainWindow window;
	window.show();
	MessageWidget box;
	box.setRect(window.geometry());
	box.setSize(QSize(400, 80));
	box.setTimeOut(5000);
	box.setText("This is a message");
	box.show();
	return app.exec();
}
