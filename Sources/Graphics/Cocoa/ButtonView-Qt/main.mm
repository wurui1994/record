#include <QtWidgets>

#include <Cocoa/Cocoa.h>

#include "KWindowButtonView.h"

void adjustWindowButtons(QWidget *w)
{
    NSView *view = (NSView *)w->winId();
    NSWindow *window = [view window];

    KWindowButtonView* buttonView = [[KWindowButtonView alloc] initWithFrame:NSMakeRect(12,14,54,16)];
    [view addSubview:buttonView];
    [buttonView updateWindowRadiusButton];
    [buttonView autorelease];
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow window;

    QWidget* widget = new QWidget(&window);
    QHBoxLayout* layout = new QHBoxLayout;
    QPushButton* button = new QPushButton("hello",widget);
    QPushButton* button2 = new QPushButton("world",widget);
    layout->addWidget(button);
    layout->addWidget(button2);
    widget->setLayout(layout);
    window.setCentralWidget(widget);

    window.setWindowFlag(Qt::FramelessWindowHint, true);
    adjustWindowButtons(&window);

    window.show();

    return app.exec();
}
