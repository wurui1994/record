#include "titlebar.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    QMainWindow window;

    // 1.标题栏
    QWidget widget;
    QHBoxLayout* layout = new QHBoxLayout;
    QPushButton* button1 = new QPushButton("hello",&widget);
    QPushButton* button2 = new QPushButton("world",&widget);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->setContentsMargins(0,0,0,0);
    widget.setLayout(layout);
    widget.setWindowFlags(widget.windowFlags() | Qt::FramelessWindowHint);
    widget.setAttribute(Qt::WA_TranslucentBackground);
    widget.setVisible(true);

    customWindowTitleBar(&window,&widget);

    window.setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(&window, &QMainWindow::destroyed,[](){
        exit(0);
    });

    QObject::connect(button1, &QPushButton::clicked,[](bool){
        qDebug() << "Hello";
    });

    QObject::connect(button2, &QPushButton::clicked,[](){
        qDebug() << "World";
    });

    // 2.内容部分
    QWidget widget2;
    QHBoxLayout* layout2 = new QHBoxLayout;
    QPushButton* button3 = new QPushButton("hello2",&widget2);
    QPushButton* button4 = new QPushButton("world2",&widget2);
    layout2->addWidget(button3);
    layout2->addWidget(button4);
    widget2.setLayout(layout2);
    widget2.setAttribute(Qt::WA_TranslucentBackground);
    widget2.setAttribute(Qt::WA_NoBackground);

    QObject::connect(button3, &QPushButton::clicked,[&](bool){
        qDebug() << "Hello2";
        setTitlebarBackgrounColor(&window,Qt::transparent);
    });

    QObject::connect(button4, &QPushButton::clicked,[&](){
        qDebug() << "World2";
        setTitlebarBackgrounColor(&window,Qt::cyan);
    });

    window.setCentralWidget(&widget2);

    setWidgetVisualEffect(&widget2);

    // 3.消除分割线
    window.setUnifiedTitleAndToolBarOnMac(true);

    window.setMinimumSize(640,480);
    window.show();

    return app.exec();
}

