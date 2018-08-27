#include <QtWidgets/QtWidgets>

#define MENU 0

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
#if MENU
	QMenu menu;
	QAction exit("exit");
	QObject::connect(&exit, &QAction::triggered, [&]() {a.exit(); });
	//QObject::connect(&menu, &QMenu::aboutToHide, [&] {menu.setHidden(false); });
	menu.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	menu.addAction("open");
	menu.addAction("test");
	menu.addAction(&exit);
	menu.setTearOffEnabled(true);
	//menu.setStyleSheet("background-color:pink;");
	menu.show();
#else
	QComboBox cbox;
	cbox.addItem("hello");
	cbox.addItem("word");
	cbox.view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	cbox.show();
#endif
	return a.exec();
}
