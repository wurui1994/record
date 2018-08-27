#include <QMenu>
#include <QSlider>
#include <QToolButton>

class MusicToolMenu : public QMenu
{
public:
	explicit MusicToolMenu(QWidget *parent = 0);
	static QString getClassName();
	void setSlider(QSlider* slider)
	{
		m_slider = slider;
	}
protected:
	virtual void showEvent(QShowEvent *event) override;
	virtual void hideEvent(QHideEvent *event) override;

	void wheelEvent(QWheelEvent *event);
private:
	QSlider * m_slider;
};


class MusicToolMenuWidget : public QToolButton
{

public:

	explicit MusicToolMenuWidget(QWidget *parent = 0);
	~MusicToolMenuWidget();

	static QString getClassName();

	void setTranslucentBackground();
	void popupMenu();

protected:
	MusicToolMenu * m_menu;
	QWidget *m_containWidget;

};

#include <QSlider>

class MusicClickedSlider : public QSlider
{

public:
	explicit MusicClickedSlider(QWidget *parent = 0);
	explicit MusicClickedSlider(Qt::Orientation orientation, QWidget *parent = 0);

	static QString getClassName();

protected:
	virtual bool event(QEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;

protected:
	int m_value;
	bool m_mousePress;

};

class MusicVolumePopWidget : public MusicToolMenuWidget
{

public:

	explicit MusicVolumePopWidget(QWidget *parent = 0);
	virtual ~MusicVolumePopWidget();

	static QString getClassName();

	void setValue(int value);

	int value() const;

	void musicVolumeChanged(int volume);
protected:
	virtual void leaveEvent(QEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void wheelEvent(QWheelEvent *event);

	virtual void moveEvent(QMoveEvent *event);

	virtual void resizeEvent(QResizeEvent* event);

	void initWidget();

	bool m_menuShown;
	MusicClickedSlider *m_volumeSlider;

};





