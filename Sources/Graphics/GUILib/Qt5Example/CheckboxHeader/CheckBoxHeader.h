#pragma once

#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>

class CheckboxHeader : public QHeaderView
{
	Q_OBJECT

public:
	CheckboxHeader(Qt::Orientation orientation, QWidget* parent = 0);

	bool isChecked() const { return isChecked_; }
	void setIsChecked(bool val);

signals:
	void checkBoxClicked(bool state);

protected:
	void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;

	void mousePressEvent(QMouseEvent* event);

private:
	bool isChecked_;
	QRect m_rect;

	void redrawCheckBox();
};
