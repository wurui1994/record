#include <QtWidgets>
#include "kwindowbuttonview.h"

void adjustWindowButtons(QWidget *w)
{
    NSView *view = (NSView *)w->winId();

    KWindowButtonView* buttonView = [[KWindowButtonView alloc] initWithFrame:NSMakeRect(12,14,54,16)];
    [view addSubview:buttonView];
    [buttonView updateWindowRadiusButton];
    [buttonView autorelease];

    // use when without modified qt
    [buttonView adjustWindowState];
}


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
    QObject::connect(&buttonOne,&QPushButton::clicked, [=]()
    {
        qDebug() << "hello";
    });
    //
    widget.setWindowFlag(Qt::FramelessWindowHint, true);
    adjustWindowButtons(&widget);
    //
    widget.show();

    return app.exec();
}

