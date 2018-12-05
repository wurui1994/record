#include <QtWidgets>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    //
    QWidget widget;
    //
    QString s = "hello";
    //
    QPushButton buttonOne("ButtonOne");

    QPushButton buttonTwo("ButtonTwo");

    QHBoxLayout* vLayout = new QHBoxLayout;
    vLayout->addWidget(&buttonOne);
    vLayout->addWidget(&buttonTwo);
    vLayout->addWidget(new QTextEdit);

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
        QMacTouchBar::clear();
    });
    //
    QAction action2(&buttonTwo);
    QObject::connect(&action2,&QAction::triggered,[=]()
    {
        qDebug() << "world";
    });
    //
    QMacTouchBar macTouchBar(&buttonOne);
    QMacTouchBar macTouchBar2(&buttonTwo);

    QObject::connect(&buttonOne,&QPushButton::clicked,[&]()
    {
        qDebug() << "Click ButtonOne";
        QMacTouchBar::clear();

        // 1
//        Command command;
//        macTouchBar.addItem(&command);
        // 2
        macTouchBar.addItem(new Command(0,"1",3,"ClearTouchBar",&actionClear));
        // 3
        macTouchBar.addItem(new Command(0,"2",2,"Hello",&action));
        macTouchBar.addItem(new Command(0,"3",4,"Color",0,Command::ColorPickerColor));
        macTouchBar.addItem(new Command(0,"4",5,"Color",0,Command::ColorPickerText));
        macTouchBar.addItem(new Command(0,"5",6,"Color",0,Command::ColorPickerStroke));
//        macTouchBar.addItem(new Command(0,"6",7,"Color",0,Command::CandidateList));
        macTouchBar.addItem(new Command(0,"7",8,"Color",0,Command::SharingService));
    });

    QObject::connect(&buttonTwo,&QPushButton::clicked,[&]()
    {
        qDebug() << "Click ButtonTwo";
        QMacTouchBar::clear();

        macTouchBar2.addItem(new Command(0,"0",0,"World",&action2));
    });

    widget.show();

    return app.exec();
}

