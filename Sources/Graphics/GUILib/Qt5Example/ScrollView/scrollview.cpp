
#include "scrollview.h"
#include "scrollcontroller.h"

#include <QPainter>

ScrollView::ScrollView( QWidget *parent, Qt::WindowFlags wFlags)
    : QWidget(parent, wFlags)
{
}

ScrollView::~ScrollView()
{
}


void ScrollView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter dc(this);
    dc.fillRect(rect(), QColor("#4C95C0"));
}
