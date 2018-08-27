#include "CheckBoxHeader.h"

CheckboxHeader::CheckboxHeader(Qt::Orientation orientation, QWidget* parent /*= 0*/)
	: QHeaderView(orientation, parent)
	, m_rect(1, 3, 20, 20)
{
	isChecked_ = true;
}

void CheckboxHeader::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
	painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex);
	painter->restore();
	if (logicalIndex == 0)
	{
		QStyleOptionButton option;
		
		option.rect = m_rect;

		option.state = QStyle::State_Enabled | QStyle::State_Active;

		if (isChecked_)
			option.state |= QStyle::State_On;
		else
			option.state |= QStyle::State_Off;
		option.state |= QStyle::State_Off;

		style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
	}
}

void CheckboxHeader::mousePressEvent(QMouseEvent* event)
{
	QPoint point = event->pos();
	if (m_rect.contains(point))
	{
		setIsChecked(!isChecked());

		emit checkBoxClicked(isChecked());
	}
}

void CheckboxHeader::redrawCheckBox()
{
	viewport()->update();
}

void CheckboxHeader::setIsChecked(bool val)
{
	if (isChecked_ != val)
	{
		isChecked_ = val;

		redrawCheckBox();
	}
}
