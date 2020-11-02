#ifndef POPOVERWIDGET_H
#define POPOVERWIDGET_H

#include <QtWidgets/QtWidgets>

class KPopoverWidget : public QWidget
{
    Q_OBJECT
public:
    enum Position {Left, Right, Top, Bottom};
public:
    explicit KPopoverWidget(QWidget *parent = nullptr);
    ~KPopoverWidget() override;
public:
    void setupWindow(QWidget* widget, QSize size = QSize(300, 150));
    void setPosition(Position position);
    void setShowWidget(QWidget* widget);
    void setTriangleHeight(int height);
    void setRectRadius(int radius);
    void setBackgroundColor(QColor color);
    void setBorderColor(QColor color);
    void setHasTriangle(bool hasTriangle);
    void setXYOffset(QPointF offset);
    // 0.0 < rate < 1.0
    void setTriangleRate(qreal rate);
    //
    void updatePosition();
signals:
    void notifyClosedHelpWidget();
    void notifyMousePressed();
public slots:
    void onSkinChanged();
protected:
    virtual void changeEvent(QEvent *) override;
    virtual void paintEvent(QPaintEvent *e) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
private:
    QLabel *m_label;
    QColor m_backgrounColor;
    QColor m_borderColor;
    Position m_position;
    int m_triangleHeight;
    int m_rectRadius;
    bool m_hasTriangle;
    QPointF m_offset;
    qreal m_triangleRate;
    QWidget* m_showWidget;
};

#endif // POPOVERWIDGET_H
