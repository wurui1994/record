#include <QtWidgets>

#include "kpopoverwidget.h"

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
    window.show();

    QPushButton* button3 = new QPushButton("test",widget);

    KPopoverWidget popover;
    popover.setupWindow(button3);
    popover.setShowWidget(button);
    popover.updatePosition();
    popover.showNormal();
    return app.exec();
}
