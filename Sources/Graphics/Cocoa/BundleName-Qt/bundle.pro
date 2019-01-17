QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bundle_name
TEMPLATE = app

SOURCES += main.cpp

macx {

    QMAKE_INFO_PLIST = Info.plist

    OTHER_FILES += \
        Info.plist \
        zh-Hans.lproj/InfoPlist.strings

    MAC_RESOURCES.files = zh-Hans.lproj
    MAC_RESOURCES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += MAC_RESOURCES
}
