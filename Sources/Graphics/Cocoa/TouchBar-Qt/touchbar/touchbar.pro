QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = touchbar
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    qmactouchbar.mm

HEADERS += \
    qmactouchbar.h

LIBS += -framework AppKit