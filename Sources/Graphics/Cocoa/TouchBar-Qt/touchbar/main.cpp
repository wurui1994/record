#include "touchbar_mac.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    //
    QWidget widget;
    //
    QPushButton buttonOne("ButtonOne");

    QPushButton buttonTwo("ButtonTwo");

    QHBoxLayout* vLayout = new QHBoxLayout;
    vLayout->addWidget(&buttonOne);
    vLayout->addWidget(&buttonTwo);

    widget.setLayout(vLayout);

    //
    QAction action(&buttonOne);
    QObject::connect(&action,&QAction::triggered,[&]()
    {
        qDebug() << "hello";
    });
    //
    QAction actionClear(&buttonOne);
    QObject::connect(&actionClear,&QAction::triggered,[&]()
    {
        qDebug() << "clear";
        MacTouchBar::clear();
    });
    //
    QAction action2(&buttonTwo);
    QObject::connect(&action2,&QAction::triggered,[=]()
    {
        qDebug() << "world";
    });
    //
    MacTouchBar macTouchBar(&buttonOne);
    MacTouchBar macTouchBar2(&buttonTwo);

    QObject::connect(&buttonOne,&QPushButton::clicked,[&]()
    {
        qDebug() << "Click ButtonOne";
        MacTouchBar::clear();

        // 1
        Command command;
        macTouchBar.addItem(&command);
        // 2
        macTouchBar.addItem(new Command(0,"1",3,"ClearTouchBar",&actionClear));
        // 3
        macTouchBar.addItem(new Command(0,"2",2,"Hello",&action));
    });

    QObject::connect(&buttonTwo,&QPushButton::clicked,[&]()
    {
        qDebug() << "Click ButtonTwo";
        MacTouchBar::clear();

        macTouchBar2.addItem(new Command(0,"0",0,"World",&action2));
    });

    widget.show();

    return app.exec();
}

