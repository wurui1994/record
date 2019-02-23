#include <QtCore/QtCore>

class NotificationCenter : public QObject
{
public:
	static NotificationCenter &instance();
    void startServer(QString name);
    void sendMessage(QString name,QString object);
	//
	void onMessage(QString name,QString object);
	//
	void runLoop();
private:
};
//
#define NotificationCenterInstance NotificationCenter::instance()
