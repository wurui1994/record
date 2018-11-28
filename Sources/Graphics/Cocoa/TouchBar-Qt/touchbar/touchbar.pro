QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = touchbar
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    touchbar_mac.mm \
    main.cpp

HEADERS += \
    touchbar_mac.h

LIBS += -framework AppKit