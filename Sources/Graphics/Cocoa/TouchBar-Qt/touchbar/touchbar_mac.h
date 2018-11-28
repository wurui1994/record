#pragma once

#include <QtCore>
#include <QtWidgets>

class Command:public QObject
{
public:
    Command(QObject* parent = nullptr, QString id = "0",
            int order = 0, QString title="Button",
            QAction* action = nullptr);
    ~Command();
    QString id();
    QAction* action();
    QString touchBarTitle();
    int macTouchBarOrder();
private:
    QString m_id;
    QAction* m_action;
    QString m_touchBarTitle;
    int m_macTouchBarOrder;
};

class MacTouchBar
{
public:
    MacTouchBar();
    MacTouchBar(QWidget* parent);
    ~MacTouchBar();

    void addItem(Command *command);
    static void clear();
    //
};

