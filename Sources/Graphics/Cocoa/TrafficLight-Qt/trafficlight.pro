QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trafficlight
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.mm \
    kwindowbuttonview.mm

HEADERS += \
    kwindowbuttonview.h

LIBS += -framework AppKit