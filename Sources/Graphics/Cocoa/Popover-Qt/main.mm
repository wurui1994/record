#include <QtWidgets>

#include <Cocoa/Cocoa.h>
void showPopover(QWidget* parent,QWidget* content)
{
#if 0
    content->setWindowFlags(content->windowFlags() | Qt::Popup);
#else
    content->setWindowFlags(content->windowFlags() | Qt::Tool | Qt::FramelessWindowHint);
#endif
    content->showMinimized();
    // 
    NSView *parentView = (__bridge NSView *)reinterpret_cast<void *>(parent->winId()); 
    NSView *popoverView = (__bridge NSView *)reinterpret_cast<void *>(content->winId());
    NSViewController* viewController = [[NSViewController alloc] init];
    viewController.view =  popoverView;
    //
    NSPopover *popover =[[NSPopover alloc] init];
    [popover setContentViewController:viewController];
    [popover showRelativeToRect:CGRectMake(0,0,0,0) ofView:parentView preferredEdge:NSMaxYEdge]; 
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);    
    QMainWindow window;   
    window.show();
    QWidget widget(&window);      
    QHBoxLayout* layout = new QHBoxLayout;
    QPushButton* button = new QPushButton("hello",&widget);
    QPushButton* button2 = new QPushButton("world",&widget);
    layout->addWidget(button);
    layout->addWidget(button2);
    widget.setLayout(layout);  
    showPopover(&window,&widget);
    return app.exec();
}
