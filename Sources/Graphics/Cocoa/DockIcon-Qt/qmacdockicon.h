#ifndef QT_MACDOCKICON_H
#define QT_MACDOCKICON_H

#include <QMainWindow>
#include <QObject>

QT_BEGIN_NAMESPACE
class QIcon;
class QMenu;
class QWidget;
QT_END_NAMESPACE

QPixmap dock_drawTextOnImage(QString title,QRect rect,float fontSize);


/** Macintosh-specific dock icon handler.
 */
class QMacDockIcon : public QObject
{
    Q_OBJECT

public:
    ~QMacDockIcon();

    void setIcon(const QIcon &icon);
    static QMacDockIcon *instance();

    void handleDockIconClickEvent();
    void handleDockIconQuitEvent();
    
    void showDockIcon();
    void hideDockIcon();

signals:
    void dockIconClicked();
    void dockIconTryToQuit();

private:
    QMacDockIcon();
};

#endif // QT_MACDOCKICON_H
