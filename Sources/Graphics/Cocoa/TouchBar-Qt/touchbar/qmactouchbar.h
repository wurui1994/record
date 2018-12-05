#pragma once

#include <QtCore>
#include <QtWidgets>

class Command:public QObject
{
public:
    enum ControlType
    {
        Button = 0,
        Label,
        // ColorPicker
        ColorPickerColor,
        ColorPickerText,
        ColorPickerStroke,
        //
        SharingService,
    };
public:
    Command(QObject* parent = nullptr, QString id = "0",
            int order = 0, QString title="Button",
            QAction* action = nullptr,ControlType controlType = Button);
    ~Command();
    QString id();
    QAction* action();
    QString touchBarTitle();
    int macTouchBarOrder();
    ControlType controlType();
private:
    QString m_id;
    QAction* m_action;
    QString m_touchBarTitle;
    int m_macTouchBarOrder;
    //
    ControlType m_controlType;
};

class QMacTouchBar
{
public:
    QMacTouchBar();
    QMacTouchBar(QWidget* parent);
    ~QMacTouchBar();

    void addItem(Command *command);
    static void clear();
    //
};

