#include "titlebar.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    QMainWindow window;

    QWidget widget;
    QHBoxLayout* layout = new QHBoxLayout;
    QPushButton* button = new QPushButton("hello",&widget);
    QPushButton* button2 = new QPushButton("world",&widget);
    layout->addWidget(button);
    layout->addWidget(button2);
    layout->setContentsMargins(0,0,0,0);
    widget.setLayout(layout);
    widget.setWindowFlags(widget.windowFlags() | Qt::FramelessWindowHint);
    widget.setAttribute(Qt::WA_TranslucentBackground);  
    // widget.setAttribute(Qt::WA_TransparentForMouseEvents);
    widget.setVisible(true);

    customWindowTitleBar(&window,&widget);
    window.setMinimumSize(640,480);
    window.show();

    window.setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(&window, &QMainWindow::destroyed,[](){
        exit(0);
    });

    QObject::connect(button, &QPushButton::clicked,[](bool){
        qDebug() << "Hello";
    });

    QObject::connect(button2, &QPushButton::clicked,[](){
        qDebug() << "World";
    });

    return app.exec();
}

