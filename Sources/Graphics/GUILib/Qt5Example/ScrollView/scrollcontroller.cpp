
#include "scrollcontroller.h"

#include "scrollview.h"

#include <QTime>
#include <QDebug>

ScrollController::ScrollController(QObject *parent)
    : QObject(parent)
    , wheelEnabled(true)
    , m_view(0)
    , m_timerId(0)
    , m_timerInterval(50)
    , m_timestamp(0)
    , m_scrollVelocity_y(0)
    , m_maximumScrollVelocity(50)
    , m_frictionFactor(0.85)
    , m_velocityThreshold(0.05)
    , m_movementThreshold(5)
    , m_isOvershoot(false)
    , m_offsetX(0)
    , m_offsetY(0)
{
    startScrollTimer();
}

ScrollController::~ScrollController()
{
}

bool ScrollController::updateOffset()
{
    if (!m_view)
        return false;

    qreal offset_x = this->offsetX();
    qreal offset_y = this->offsetY();
    qreal max = this->maximumOffset();

    bool cont = kineticUpdateOffset(&offset_x, &offset_y, max);
    qreal value_x = m_isOvershoot ? offset_x : qBound<qreal>(0, offset_x, max);
    qreal value_y = m_isOvershoot ? offset_y : qBound<qreal>(0, offset_y, max);

    this->setOffsetX(value_x);
    this->setOffsetY(value_y);

    return cont;
}

bool ScrollController::kineticUpdateOffset(qreal *offset_x,qreal *offset_y, qreal max)
{
    static const qreal k = -0.5; // overshoot spring constant

    *offset_y += m_scrollVelocity_y;
    *offset_x += m_scrollVelocity_x;

    // check for overshoot at the top
    if (*offset_y <= 0) {
        if (m_isOvershoot) {
            m_scrollVelocity_y = qMin(k * *offset_y, m_scrollVelocity_y + k * *offset_y);
        } else {
            *offset_y = 0;
            m_scrollVelocity_y = 0;
            return false;
        }
    }

    // check for overshoot at the bottom
    if (*offset_y >= max) {
        if (m_isOvershoot) {
            m_scrollVelocity_y = qMax(k * (*offset_y - max), m_scrollVelocity_y + k * (*offset_y - max));
        } else {
            m_scrollVelocity_y = 0;
            *offset_y = max;
            return false;
        }
    }

    // check for overshoot at the left
    if (*offset_x <= 0) {
        if (m_isOvershoot) {
            m_scrollVelocity_x = qMin(k * *offset_x, m_scrollVelocity_y + k * *offset_x);
        } else {
            *offset_x = 0;
            m_scrollVelocity_x = 0;
            return false;
        }
    }

    // check for overshoot at the right
    if (*offset_x >= max) {
        if (m_isOvershoot) {
            m_scrollVelocity_x = qMax(k * (*offset_x - max), m_scrollVelocity_x + k * (*offset_x - max));
        } else {
            m_scrollVelocity_x = 0;
            *offset_y = max;
            return false;
        }
    }

    // ### FIXME: this code may not work with small items
    // make sure that an item is at the center when we stop

    // apply friction
    m_scrollVelocity_y *= m_frictionFactor;
    m_scrollVelocity_x *= m_frictionFactor;
    if (qAbs<qreal>(m_scrollVelocity_y) < m_velocityThreshold
        && qAbs<qreal>(m_scrollVelocity_x) < m_velocityThreshold) {
        m_scrollVelocity_y = 0;
        m_scrollVelocity_x = 0;
        return false;
    }

    return true;
}

void ScrollController::startScrollTimer()
{
    if (m_timerId == 0)
        m_timerId = startTimer(m_timerInterval);
}

int ScrollController::currentTime()
{
    QTime t = QTime::currentTime();
    return t.hour() * 3600000 + t.minute() * 60000 + t.second() * 1000 + t.msec();
}

void ScrollController::setScrollVelocityX(qreal velocity_x)
{
    m_scrollVelocity_x = qMin(velocity_x, m_maximumScrollVelocity);
    startScrollTimer();
}

void ScrollController::setScrollVelocityY(qreal velocity_y)
{
    m_scrollVelocity_y = qMin(velocity_y, m_maximumScrollVelocity);
    startScrollTimer();
}

qreal ScrollController::scrollVelocityX() const
{
    return m_scrollVelocity_x;
}

qreal ScrollController::scrollVelocityY() const
{
    return m_scrollVelocity_y;
}

void ScrollController::setMaximumScrollVelocity(qreal velocity)
{
    m_maximumScrollVelocity = velocity;
}

qreal ScrollController::maximumScrollVelocity() const
{
    return m_maximumScrollVelocity;
}

void ScrollController::setOvershootEnabled(bool enabled)
{
    m_isOvershoot = enabled;
}

bool ScrollController::isOvershootEnabled() const
{
    return m_isOvershoot;
}

void ScrollController::stop()
{
    killTimer(m_timerId);
    m_timerId = 0;

    m_timestamp = currentTime();
    m_timeDelta = 0;
    m_movement_x = 0.;
    m_movement_y = 0.;

    m_scrollVelocity_x = 0;
    m_scrollVelocity_y = 0;
}

bool ScrollController::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    killTimer(m_timerId);
    m_timerId = 0;
    return true;
}

bool ScrollController::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (!m_view)
        return false;

    int oldTimestamp = m_timestamp;
    m_timestamp = currentTime();
    m_timeDelta = m_timestamp - oldTimestamp;

    m_movement_x = m_lastPos.x() - event->globalPos().x();
    m_movement_y = m_lastPos.y() - event->globalPos().y();


    qreal offset_x = this->offsetX() + m_movement_x;
    qreal offset_y = this->offsetY() + m_movement_y;
    qreal max = this->maximumOffset();
    this->setOffsetX(m_isOvershoot ? offset_x : qBound<qreal>(0, offset_x, max));
    this->setOffsetY(m_isOvershoot ? offset_y : qBound<qreal>(0, offset_y, max));

    m_lastPos = event->globalPos();

    return true;
}

bool ScrollController::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_scrollVelocity_y = 0;
    m_scrollVelocity_x = 0;

    killTimer(m_timerId);
    m_timerId = 0;

    m_timestamp = currentTime();
    m_timeDelta = 0;
    m_movement_x = 0.;
    m_movement_y = 0.;

    stop();

    m_lastPos = event->globalPos();

    return true;
}

bool ScrollController::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_view)
        return false;

    qreal dt = qreal(m_timeDelta) / qreal(m_timerInterval);
    QPointF dp = event->globalPos() - m_lastPos;
    qreal totalMovement = std::sqrt(dp.x()*dp.x() + dp.y()*dp.y());

    if (qAbs<qreal>(totalMovement) > m_movementThreshold) {
        setScrollVelocityX(m_movement_x / dt);
        setScrollVelocityY(m_movement_y / dt); // start kinetic scrolling
    } else {
        const qreal offset = this->offsetX();
        const qreal maximumOffset = this->maximumOffset();
        if (offset < 0 || offset > maximumOffset)
            startScrollTimer(); // start bounce-back
    }

    if (qAbs<qreal>(totalMovement) < m_movementThreshold)
    {
        return false;
    }

    return true;
}

bool ScrollController::resizeEvent(QResizeEvent *event)
{
    if (m_view)
        setOriginPosition(m_view->pos());
    return true;
}

bool ScrollController::wheelEvent(QWheelEvent *event)
{
    Q_ASSERT(event);
    if (m_view)
    {
        if (event->orientation() == Qt::Vertical)
        {
            setScrollVelocityY(m_scrollVelocity_y - event->delta() / 8.);
        }
        else
        {
            setScrollVelocityX(m_scrollVelocity_x - event->delta() / 8.);
        }
    }
    return true;
}

bool ScrollController::processEvent(QEvent *event)
{
    if (!event)
        return false;
    switch(event->type()) {
    case QEvent::MouseButtonPress:
        return mousePressEvent(static_cast<QMouseEvent*>(event));
    case QEvent::MouseMove:
        return mouseMoveEvent(static_cast<QMouseEvent*>(event));
    case QEvent::MouseButtonRelease:
        return mouseReleaseEvent(static_cast<QMouseEvent*>(event));
    case QEvent::Wheel:
        return wheelEvent(static_cast<QWheelEvent*>(event));
    case QEvent::Resize:
        return resizeEvent(static_cast<QResizeEvent*>(event));
    case QEvent::Hide:
        return hideEvent(static_cast<QHideEvent*>(event));
    default:
        break;
    }
    return false;
}


void ScrollController::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
    {
        // updateOffset();
        if (!updateOffset())
        {
            killTimer(m_timerId);
            m_timerId = 0;
        }
    }
}

bool ScrollController::eventFilter(QObject *o, QEvent *e)
{
    if (m_view == o)
    {
        if (processEvent(e))
        {
            e->accept();
            return true;
        }
    }
    return QObject::eventFilter(o, e);
}

QWidget * ScrollController::view() const
{
    return m_view;
}

void ScrollController::setView(QWidget *view)
{
    if (m_view == view)
        return;

    m_view = view;

    if (m_view)
    {
        m_view->installEventFilter(this);
    }
}

bool ScrollController::isWheelEnabled() const
{
    return wheelEnabled;
}

void ScrollController::setWheelEnabled(bool enable)
{
    wheelEnabled = enable;
}

void ScrollController::setOriginPosition(QPoint pos)
{
    m_originPosition = pos;
}

qreal ScrollController::maximumOffset() const
{
    return 0;
}

void ScrollController::updateViewOffset()
{
    if (m_view)
        m_view->move(m_originPosition.x() - m_offsetX, m_originPosition.y() - m_offsetY);
}

qreal ScrollController::offsetX() const
{
    return m_offsetX;
}

qreal ScrollController::offsetY() const
{
    return m_offsetY;
}

void ScrollController::setOffsetX(qreal offset)
{
    m_offsetX = offset;
    updateViewOffset();
}

void ScrollController::setOffsetY(qreal offset)
{
    m_offsetY = offset;
    updateViewOffset();
}
