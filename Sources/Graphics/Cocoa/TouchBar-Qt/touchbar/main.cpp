#include <QtWidgets>
#include "qmactouchbar.h"

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
    Command clear(0,"1",2,"ClearTouchBar");
    Command hello(0,"2",1,"Hello");
    Command world(0,"0",0,"World");

    Command scrubberText(0,"9",3,"scrubberText",Command::Scrubber);

    Command colorPickerColor(0,"3",4,"colorPickerColor",Command::ColorPickerColor);
    Command colorPickerText(0,"4",5,"colorPickerText",Command::ColorPickerText);
    Command colorPickerStroke(0,"5",6,"colorPickerStroke",Command::ColorPickerStroke);

    Command scrubber(0,"9",7,"scrubber",Command::Scrubber);
    Command sharingService(0,"7",8,"sharingService",Command::SharingService);


    QObject::connect(clear.action(),&QAction::triggered,[&]()
    {
        qDebug() << "clear";
        QMacTouchBar::clear();
    });
    //
    QObject::connect(world.action(),&QAction::triggered,[=]()
    {
        qDebug() << "world";
    });
    //
    QMacTouchBar macTouchBar(&buttonOne);
    QMacTouchBar macTouchBar2(&buttonTwo);

    QList<QString> stringList = {"1","2","3"};
    scrubberText.setScrubberTextList(stringList);
    scrubberText.setScrubberSize(QSize(20,30));

    QImage image = QMessageBox::standardIcon(QMessageBox::Question).toImage();
    QList<QImage> imageList = {image,image,image,image};
    scrubber.setScrubberImageList(imageList);
    scrubber.setScrubberSize(QSize(30,30));

    QObject::connect(scrubber.action(),&QAction::triggered,[&]
    {
        qDebug() << scrubber.scrubberResultIndex();
    });

    QObject::connect(&buttonOne,&QPushButton::clicked,[&]()
    {
        qDebug() << "Click ButtonOne";
        QMacTouchBar::clear();

        // 1
        Command command;
        macTouchBar.addItem(&command);
        // 2
        macTouchBar.addItem(&clear);
        // 3
        macTouchBar.addItem(&hello);

        macTouchBar.addItem(&scrubberText);

        macTouchBar.addItem(&colorPickerColor);
        macTouchBar.addItem(&colorPickerText);
        macTouchBar.addItem(&colorPickerStroke);
    });

    QObject::connect(&buttonTwo,&QPushButton::clicked,[&]()
    {
        qDebug() << "Click ButtonTwo";
        QMacTouchBar::clear();

        macTouchBar2.addItem(&world);
        macTouchBar2.addItem(&scrubber);
        macTouchBar2.addItem(&sharingService);
    });

    widget.show();

    return app.exec();
}

