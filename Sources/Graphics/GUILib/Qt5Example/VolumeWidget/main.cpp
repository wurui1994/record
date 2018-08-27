#include "VolumeWidget.h"
#include <QApplication>
#include <QSlider>
#include <QtWidgets/QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QMainWindow w;
    
	MusicVolumePopWidget* slider = new MusicVolumePopWidget;
	slider->resize(320, 240);
	//w.setCentralWidget(slider);
   // w.show();
	slider->show();
    return a.exec();
}
