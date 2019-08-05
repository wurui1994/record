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
        //
        Scrubber
    };
public:
    Command(QObject* parent = nullptr, QString id = "0",
            int order = 0, QString title="Button",ControlType controlType = Button);
    ~Command();
    QString id();
    QAction* action();
    QString touchBarTitle();
    int macTouchBarOrder();
    ControlType controlType();
    //
    void setScrubberSize(QSize const& size);
    void setScrubberTextList(QList<QString> const& stringList);
    void setScrubberImageList(QList<QImage> const& imageList);
    //
    void setScrubberResultIndex(int index);
    //
    QList<QString> scrubberTextList();
    QList<QImage> scrubberImageList();
    //
    QSize scrubberSize();
    int scrubberResultIndex();
private:
    QString m_id;
    QAction* m_action;
    QString m_touchBarTitle;
    int m_macTouchBarOrder;

    // Scrubber
    bool m_scrubberHasText;
    bool m_scrubberHasImage;
    QList<QString> m_scrubberText;
    QList<QImage> m_scrubberImage;
    QSize m_scrubberSize;
    int m_scrubberResultIndex;
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

