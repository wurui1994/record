#include "scrollcontroller.h"
#include "scrollview.h"

#include <QtWidgets/QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow widget;

    ScrollView view;

    ScrollController controller(&view);
    controller.setView(&view);
    controller.setOvershootEnabled(true);

    widget.setContentsMargins(40,40,40,40);
    widget.setCentralWidget(&view);
    widget.resize(640,480);
    widget.show();

    return app.exec();
}
