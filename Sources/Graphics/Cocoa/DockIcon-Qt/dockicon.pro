QT += core gui widgets

OBJECTIVE_SOURCES += main.mm
QMAKE_OBJECTIVE_CFLAGS += -fobjc-arc
LIBS += -framework AppKit

HEADERS += \
    qmacdockicon.h

SOURCES += \
    qmacdockicon.mm
