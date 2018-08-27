#include <QApplication>
#include <QPainter>
#include <QWidget>
#include <QtMath>

class ShadowWidget:public QWidget
{
public:
    void paintEvent(QPaintEvent *event);
};

void ShadowWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10,10,this->width()-20,this->height()-20);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.fillPath(path,QBrush(Qt::white));
    QColor color(0,0,0,50);
    for(int i = 0 ; i < 10 ; ++i)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundRect(10-i,10-i,this->width()-(10-i)*2,this->height()-(10-i)*2,10,10);
        //path.addRect(10-i,10-i,this->width()-(10-i)*2,this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShadowWidget w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    //w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
    return a.exec();
}
