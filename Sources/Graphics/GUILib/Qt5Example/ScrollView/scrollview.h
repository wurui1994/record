#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include <QWidget>

class ScrollView : public QWidget
{
    Q_OBJECT

public:
    ScrollView(QWidget *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~ScrollView();
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif//SCROLLVIEW_H
