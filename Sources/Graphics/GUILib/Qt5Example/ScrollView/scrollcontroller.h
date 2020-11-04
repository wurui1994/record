#ifndef SCROLLCONTROLLER_H
#define SCROLLCONTROLLER_H

#include <QWheelEvent>

class ScrollView;

class ScrollController : public QObject
{
    Q_OBJECT

public:
    QWidget *view() const;
    void setView(QWidget *view);

    bool isWheelEnabled() const;
    void setWheelEnabled(bool enable);

    virtual bool mousePressEvent(QMouseEvent *event);
    virtual bool mouseMoveEvent(QMouseEvent *event);
    virtual bool mouseReleaseEvent(QMouseEvent *event);
    virtual bool resizeEvent(QResizeEvent *event);

    virtual bool wheelEvent(QWheelEvent *event);
    virtual bool processEvent(QEvent *event);

public:
    ScrollController(QObject *parent = 0);
    virtual ~ScrollController();

    bool updateOffset();
    bool kineticUpdateOffset(qreal *offset_x, qreal *offset_y, qreal max);

    void startScrollTimer();
    int currentTime();

    void setScrollVelocityX(qreal velocity_x);
    void setScrollVelocityY(qreal velocity_y);
    qreal scrollVelocityX() const;
    qreal scrollVelocityY() const;

    void setMaximumScrollVelocity(qreal velocity);
    qreal maximumScrollVelocity() const;

    void setOvershootEnabled(bool enable);
    bool isOvershootEnabled() const;

public Q_SLOTS:
    void stop();

protected:
    bool hideEvent(QHideEvent *event);
    void timerEvent(QTimerEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
private:
    bool wheelEnabled;
    QWidget *m_view;

    QPoint m_lastPos;
    // kinetic scrolling
    int m_timerId;
    int m_timerInterval;
    int m_timestamp;
    qreal m_scrollVelocity_x;
    qreal m_scrollVelocity_y;
    qreal m_maximumScrollVelocity;
    qreal m_frictionFactor;
    qreal m_velocityThreshold;
    // user movement
    int m_timeDelta;
    qreal m_movement_x;
    qreal m_movement_y;
    qreal m_movementThreshold;
    // bounceback
    bool m_isOvershoot;
public:
    qreal offsetX() const;
    qreal offsetY() const;
    qreal maximumOffset() const;
    void updateViewOffset();

public Q_SLOTS:
    void setOffsetX(qreal offset);
    void setOffsetY(qreal offset);
    void setOriginPosition(QPoint pos);
private:
    QPoint m_originPosition;
    qreal m_offsetX;
    qreal m_offsetY;
};

#endif // SCROLLCONTROLLER_H
