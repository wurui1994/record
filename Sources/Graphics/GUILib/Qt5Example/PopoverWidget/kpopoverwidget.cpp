#include "kpopoverwidget.h"

KPopoverWidget::KPopoverWidget(QWidget *parent)
    : QWidget(parent)
    , m_position(Position::Right)
    , m_triangleHeight(8)
    , m_rectRadius(4)
    , m_backgrounColor(Qt::white)
    , m_borderColor(Qt::transparent)
    , m_hasTriangle(true)
    , m_offset(0, 0)
    , m_triangleRate(0.5)
    , m_showWidget(nullptr)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);

    onSkinChanged();
    connect(qApp, SIGNAL(notifyAppSkinChange(QString)), this, SLOT(onSkinChanged()));
}

KPopoverWidget::~KPopoverWidget()
{

}

void KPopoverWidget::setPosition(KPopoverWidget::Position position)
{
    m_position = position;
}

void KPopoverWidget::setShowWidget(QWidget* widget)
{
    if (m_showWidget)
    {
        if (m_showWidget != widget)
        {
            // 容易崩溃, 先屏蔽掉
#if 0
            m_showWidget->removeEventFilter(this);
#endif
            m_showWidget = widget;
#if 0
            m_showWidget->installEventFilter(this);
#endif
        }
        updatePosition();
    }
    else
    {
        m_showWidget = widget;
        if (m_showWidget)
        {
#if 0
            m_showWidget->installEventFilter(this);
#endif
            updatePosition();
        }
    }
}

void KPopoverWidget::setTriangleHeight(int height)
{
    m_triangleHeight = height;
}

void KPopoverWidget::setRectRadius(int radius)
{
    m_rectRadius = radius;
}

void KPopoverWidget::setBackgroundColor(QColor color)
{
    m_backgrounColor = color;
}

void KPopoverWidget::setBorderColor(QColor color)
{
    m_borderColor = color;
}

void KPopoverWidget::setHasTriangle(bool hasTriangle)
{
    m_hasTriangle = hasTriangle;
}

void KPopoverWidget::setXYOffset(QPointF offset)
{
    m_offset = offset;
}

void KPopoverWidget::setTriangleRate(qreal rate)
{
    m_triangleRate = rate;
}

void KPopoverWidget::updatePosition()
{
    QRect rc = m_showWidget->rect();
    QPoint pointCenter = m_showWidget->mapToGlobal(rc.center());

    int w = rc.width();
    int h = rc.height();

    int p_w = this->width();
    int p_h = this->height();

    QPointF point;
    if (m_position == Position::Left)
    {
        point = QPointF(pointCenter.x() - w / 2 - p_w, pointCenter.y() - p_h / 2);
        point -= QPointF(0.0, p_h * (m_triangleRate - 0.5));
    }
    else if (m_position == Position::Right)
    {
        point = QPointF(pointCenter.x() + w / 2 , pointCenter.y() - p_h / 2);
        point -= QPointF(0.0, p_h * (m_triangleRate - 0.5));
    }
    else if (m_position == Position::Top)
    {
        point = QPointF(pointCenter.x() - p_w / 2 , pointCenter.y() - p_h - h/2);
        point -= QPointF( p_w * (m_triangleRate - 0.5), 0.0);
    }
    else if (m_position == Position::Bottom)
    {
        point = QPointF(pointCenter.x() - p_w / 2, pointCenter.y() + h / 2);
        point -= QPointF( p_w * (m_triangleRate - 0.5), 0.0);
    }
    point += m_offset;
    this->move(point.x(), point.y());
}

void KPopoverWidget::setupWindow(QWidget* widget, QSize size)
{
    setFixedSize(size);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->setContentsMargins(4, 4, 4, 4);
    mainLayout->addWidget(widget);

    this->setLayout(mainLayout);
}

void KPopoverWidget::paintEvent(QPaintEvent *e)
{
    if (this->isHidden())
        return;

    QPainter painter(this);

    QRect rc(rect());

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(m_borderColor);
    painter.setBrush(m_backgrounColor);

    //
    int x = rc.x();
    int y = rc.y();
    int w = rc.width();
    int h = rc.height();

    if (m_hasTriangle)
    {
        QPainterPath drawPath;
        QPolygonF trianglePolygon;

        QPointF startPoint;
        QPointF endPoint;
        QPointF mediumPoint;

        // 小三角区域;
        if (m_position == Position::Left)
        {
            // Right triangle
            mediumPoint =  QPointF(x + w, y + h * m_triangleRate);
            startPoint =  QPointF(x + w - m_triangleHeight, y + h * m_triangleRate - m_triangleHeight);
            endPoint = QPointF(x + w - m_triangleHeight, y + h * m_triangleRate + m_triangleHeight);

            trianglePolygon <<  startPoint << mediumPoint << endPoint;

            drawPath.addRoundedRect(QRect(x, y,
                                          w - m_triangleHeight, h), m_rectRadius, m_rectRadius);

            startPoint += QPoint(0,1);
            endPoint += QPoint(0,-1);
        }
        else if (m_position == Position::Right)
        {
            // Left triangle
            mediumPoint =  QPointF(x, y + h * m_triangleRate);
            startPoint =  QPointF(x + m_triangleHeight, y + h * m_triangleRate - m_triangleHeight);
            endPoint = QPointF(x + m_triangleHeight, y + h * m_triangleRate  + m_triangleHeight);

            trianglePolygon <<  startPoint << mediumPoint << endPoint;

            drawPath.addRoundedRect(QRect(x + m_triangleHeight, y,
                                          w - m_triangleHeight, h), m_rectRadius, m_rectRadius);

            startPoint += QPoint(0,1);
            endPoint += QPoint(0,-1);
        }
        else if (m_position == Position::Top)
        {
            // Bottom triangle
            mediumPoint =  QPointF(x + w * m_triangleRate , y + h);
            startPoint =  QPointF(x + w * m_triangleRate - m_triangleHeight, y + h - m_triangleHeight);
            endPoint = QPointF(x + w * m_triangleRate + m_triangleHeight, y + h - m_triangleHeight);

            trianglePolygon <<  startPoint << mediumPoint << endPoint;

            drawPath.addRoundedRect(QRect(x, y,
                                          w , h - m_triangleHeight), m_rectRadius, m_rectRadius);

            startPoint += QPoint(1,0);
            endPoint += QPoint(-1,0);
        }
        else if (m_position == Position::Bottom)
        {
            // Top triangle
            mediumPoint =  QPointF(x + w * m_triangleRate , y);
            startPoint =  QPointF(x + w * m_triangleRate - m_triangleHeight, y + m_triangleHeight);
            endPoint = QPointF(x + w * m_triangleRate + m_triangleHeight, y + m_triangleHeight);

            trianglePolygon  << startPoint << mediumPoint << endPoint;

            drawPath.addRoundedRect(QRect(x, y + m_triangleHeight,
                                          w , h - m_triangleHeight), m_rectRadius, m_rectRadius);

            startPoint += QPoint(1,0);
            endPoint += QPoint(-1,0);
        }

        // Rect + Triangle;
        drawPath.addPolygon(trianglePolygon);

        painter.drawPath(drawPath);

        painter.setPen(m_backgrounColor);
        painter.drawLine(startPoint, endPoint);

    }
    else
    {
        painter.drawRoundedRect(QRect(x, y , w, h), m_rectRadius, m_rectRadius);
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
}

bool KPopoverWidget::eventFilter(QObject *o, QEvent *e)
{
#if 0
    if (o == m_showWidget)
    {
        if (e->type() == QEvent::Move)
        {
            if (isVisible())
            {
                updatePosition();
            }
        }
    }
#endif
    return QWidget::eventFilter(o, e);
}

void KPopoverWidget::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::WindowStateChange)
    {
        const bool wasMinimized = static_cast<const QWindowStateChangeEvent *>(e)->oldState() & Qt::WindowMinimized;
        if ((!(this->windowState() & Qt::WindowMinimized)) && wasMinimized)
        {
            emit notifyClosedHelpWidget();
        }
    }
    QWidget::changeEvent(e);
}

void KPopoverWidget::mousePressEvent(QMouseEvent *ev)
{
    emit notifyMousePressed();
    QWidget::mousePressEvent(ev);
}


void KPopoverWidget::onSkinChanged()
{
    if (qApp->applicationIsInDarkMode())
    {
        setBackgroundColor(QColor("#2D2E30"));
        setBorderColor(QColor("#33FFFFFF"));
    }
    else
    {
        setBackgroundColor(Qt::white);
        setBorderColor(QColor("#3336425A"));
    }
}
