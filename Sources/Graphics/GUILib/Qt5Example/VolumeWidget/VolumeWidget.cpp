#include "VolumeWidget.h"
#include <QApplication>

namespace MusicUIObject
{


	const QString MSliderStyle02 = " \
            QSlider::groove:vertical{ \
            background: #FFFEA1; width:3px; border-radius:1px;} \
            QSlider::sub-page:vertical{ background:#4E4F4F;} \
            QSlider::add-page:vertical{ background:#FFFEA1;} \
            QSlider::handle:vertical{ background:#FFFEA1; \
            height:9px; margin-left:-3px; margin-right:-3px; border-radius:4px;}";

	const QString MSliderStyle03 = " \
            QSlider::groove:vertical{ background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \
            stop:0 #B5B4B4, stop:1 #FCFCFC); width:3px;} \
            QSlider::handle:vertical{ border-image:url(:/control/lb_slider_handle_normal); \
            height:21px; margin-left:-8px; margin-right:-8px;} \
            QSlider::handle:vertical:disabled{ border-image:url(:/control/lb_slider_disable);} \
            QSlider::handle:vertical:hover{ border-image:url(:/control/lb_slider_handle_hover); border:none;}";

}

namespace MusicUIObject
{
	const QString MMenuStyle01 = " \
            QMenu{ padding:5px;} \
            QMenu::icon{ margin-left:10px;} \
            QMenu::right-arrow{ background: url(:/tiny/lb_arrow_up_normal);} \
            QMenu::item{ color:#666666; padding:6px 30px 6px 30px; border:1px solid transparent;} \
            QMenu::item:disabled{ color:#AAAAAA;} \
            QMenu::item:selected{ color:white; background: rgb(22, 154, 243);} \
            QMenu::separator{ height:1px; background:#DDDDDD; margin-top:5px; margin-bottom:5px;}";

	const QString MKGBtnSound = " \
            QToolButton{ border:none; \
            background-image: url(:/functions/btn_sound_normal);} \
            QToolButton:hover{ background-image: url(:/functions/btn_sound_hover);}";

	const QString MMenuStyle03 = MMenuStyle01 + " \
            QMenu{ border:none; background:rgba(0, 0, 0, 210); border-radius:4px;} \
            QMenu::item{ color:#BBBBBB;} \
            QMenu::item:disabled{ color:#555555;} \
            QMenu::item:selected{ background:rgba(0, 0, 0, 200);} \
            QMenu::separator{ background:#BBBBBB;}";
	
}

#include <QMouseEvent>

MusicClickedSlider::MusicClickedSlider(QWidget *parent)
	: MusicClickedSlider(Qt::Horizontal, parent)
{

}

MusicClickedSlider::MusicClickedSlider(Qt::Orientation orientation, QWidget *parent)
	: QSlider(orientation, parent)
{
	//setCursor(QCursor(Qt::PointingHandCursor));
	m_mousePress = false;
	m_value = 0;
}

QString MusicClickedSlider::getClassName()
{
	return staticMetaObject.className();
}

bool MusicClickedSlider::event(QEvent *event)
{
	if (m_mousePress)
	{
		setValue(m_value);
	}
	return QSlider::event(event);
}

void MusicClickedSlider::mousePressEvent(QMouseEvent *event)
{
	QSlider::mousePressEvent(event);
	if (event->button() == Qt::LeftButton)
	{
		m_mousePress = true;

		double pos;
		if (orientation() == Qt::Horizontal)
		{
			pos = event->pos().x()*1.0 / width();
			m_value = pos * (maximum() - minimum()) + minimum();
		}
		else
		{
			pos = event->pos().y()*1.0 / height();
			m_value = maximum() - pos * (maximum() - minimum());
		}
	}
}

void MusicClickedSlider::mouseMoveEvent(QMouseEvent *event)
{
	QSlider::mouseMoveEvent(event);
	if (m_mousePress)
	{
		if (orientation() == Qt::Horizontal)
		{
			int x = event->pos().x();
			if ((x >= 0) && (x <= width()))
			{
				double pos = event->pos().x()*1.0 / width();
				m_value = pos * (maximum() - minimum()) + minimum();
				setValue(m_value);
			}
			else if (x < 0)
			{
				m_value = minimum();
			}
			else
			{
				m_value = maximum();
			}
		}
		else
		{
			int y = event->pos().y();
			if ((y >= 0) && (y <= height()))
			{
				double pos = event->pos().y()*1.0 / height();
				m_value = maximum() - pos * (maximum() - minimum());
				setValue(m_value);
			}
			else if (y < 0)
			{
				m_value = maximum();
			}
			else
			{
				m_value = minimum();
			}
		}
	}
}

void MusicClickedSlider::mouseReleaseEvent(QMouseEvent *event)
{
	QSlider::mouseReleaseEvent(event);
	m_mousePress = false;
}
//#include "musictoolmenuwidget.h"
//#include "musicuiobject.h"

#include <QWidgetAction>

MusicToolMenu::MusicToolMenu(QWidget *parent)
	: QMenu(parent)
	, m_slider(nullptr)
{

}

QString MusicToolMenu::getClassName()
{
	return staticMetaObject.className();
}

void MusicToolMenu::showEvent(QShowEvent *event)
{
	QMenu::showEvent(event);
	//emit windowStateChanged(true);
}

void MusicToolMenu::hideEvent(QHideEvent *event)
{
	QMenu::hideEvent(event);
	//emit windowStateChanged(false);
}

void MusicToolMenu::wheelEvent(QWheelEvent * event)
{
	if (rect().contains(event->pos()) && m_slider && m_slider->isVisible())
		qApp->sendEvent(m_slider, event);
}


MusicToolMenuWidget::MusicToolMenuWidget(QWidget *parent)
	: QToolButton(parent)
	
{
	//setCursor(Qt::PointingHandCursor);

	m_menu = new MusicToolMenu(this);
	QWidgetAction *actionWidget = new QWidgetAction(m_menu);
	m_containWidget = new QWidget(m_menu);

	actionWidget->setDefaultWidget(m_containWidget);
	m_menu->addAction(actionWidget);

	//connect(this, SIGNAL(clicked()), SLOT(popupMenu()));
}

MusicToolMenuWidget::~MusicToolMenuWidget()
{
	delete m_containWidget;
	delete m_menu;
}

QString MusicToolMenuWidget::getClassName()
{
	return staticMetaObject.className();
}

void MusicToolMenuWidget::setTranslucentBackground()
{
	m_menu->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);;
	m_menu->setAttribute(Qt::WA_TranslucentBackground);
	m_menu->setStyleSheet(MusicUIObject::MMenuStyle03);
}

void MusicToolMenuWidget::popupMenu()
{
	QPoint pos = mapToGlobal(QPoint(0, 0));
	pos.setY(pos.y() - m_containWidget->height() - 10);
	pos.setX(pos.x() - (m_containWidget->width() - width()) / 2);

	//m_menu->exec(pos);
	m_menu->move(pos);
	m_menu->show();
}




#include <QTimer>
#include <QHBoxLayout>

MusicVolumePopWidget::MusicVolumePopWidget(QWidget *parent)
	: MusicToolMenuWidget(parent)
{
	initWidget();

	m_menuShown = false;

	//disconnect(this, SIGNAL(clicked()), this, SLOT(popupMenu()));
}

MusicVolumePopWidget::~MusicVolumePopWidget()
{
	delete m_volumeSlider;
}

QString MusicVolumePopWidget::getClassName()
{
	return staticMetaObject.className();
}

void MusicVolumePopWidget::setValue(int value)
{
	m_volumeSlider->blockSignals(true);
	m_volumeSlider->setValue(value);
	m_volumeSlider->blockSignals(false);

	QString style = MusicUIObject::MKGBtnSound;
	if (66 < value && value <= 100)
	{
		style += "QToolButton{ margin-left:-60px; }";
	}
	else if (33 < value && value <= 66)
	{
		style += "QToolButton{ margin-left:-40px; }";
	}
	else if (0 < value && value <= 33)
	{
		style += "QToolButton{ margin-left:-20px; }";
	}
	else
	{
		style += "QToolButton{ margin-left:-80px; }";
	}
	setStyleSheet(style);
	setToolTip(QString::number(value));
}

int MusicVolumePopWidget::value() const
{
	return m_volumeSlider->value();
}

void MusicVolumePopWidget::leaveEvent(QEvent *event)
{
	MusicToolMenuWidget::leaveEvent(event);
	//m_menu->hide();
}

void MusicVolumePopWidget::mousePressEvent(QMouseEvent *event)
{
	MusicToolMenuWidget::enterEvent(event);
	if (m_menu->isVisible())
	{
		m_menu->hide();
	}
	else
	{
		popupMenu();
	}
}

void MusicVolumePopWidget::wheelEvent(QWheelEvent * event)
{
	if(m_volumeSlider->isVisible())
		QApplication::sendEvent(m_volumeSlider, event);
}

void MusicVolumePopWidget::moveEvent(QMoveEvent * event)
{
	if(m_volumeSlider->isVisible())
		popupMenu();
	MusicToolMenuWidget::moveEvent(event);
}

void MusicVolumePopWidget::resizeEvent(QResizeEvent * event)
{

}

void MusicVolumePopWidget::initWidget()
{
	setTranslucentBackground();
	m_containWidget->setFixedSize(20, 100);
	QHBoxLayout *layout = new QHBoxLayout(m_containWidget);
	layout->setContentsMargins(0, 9, 0, 9);
	layout->setSpacing(0);

	m_volumeSlider = new MusicClickedSlider(Qt::Vertical, this);
	m_volumeSlider->setCursor(QCursor(Qt::PointingHandCursor));
	m_volumeSlider->setRange(0, 100);
	m_volumeSlider->setStyleSheet(MusicUIObject::MSliderStyle02);

	//connect(m_volumeSlider, SIGNAL(valueChanged(int)), SIGNAL(musicVolumeChanged(int)));
	m_menu->setSlider(m_volumeSlider);
	layout->addWidget(m_volumeSlider);
	m_containWidget->setLayout(layout);
}

