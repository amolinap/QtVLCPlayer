#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T10:27:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VLCPlayer
TEMPLATE = app
TARGETDIR = $$OUT_PWD
BASEDIR = $$IN_PWD

BASEDIR = $$IN_PWD
TARGETDIR = $$OUT_PWD
OBJECTS_DIR = $$OUT_PWD/obj
MOC_DIR = $$OUT_PWD/moc
UI_HEADERS_DIR = $$OUT_PWD/generated
UI_DIR= $$OUT_PWD/ui

VLC_SOURCE = source

INCLUDEPATH += $$VLC_SOURCE

HEADERS += $$VLC_SOURCE/VLCVideoWidget.h \
        $$VLC_SOURCE/VLCDisplay.h \
        VideoManagement.h \
        QtConfiguration.h

SOURCES += main.cpp \
        $$VLC_SOURCE/VLCVideoWidget.cpp \
        $$VLC_SOURCE/VLCDisplay.cpp \
        VideoManagement.cpp

FORMS += $$VLC_SOURCE/VLCVideoWidget.ui \
        $$VLC_SOURCE/VLCDisplay.ui \
        VideoManagement.ui

RESOURCES += \
    Resources.qrc

LIBS += -lvlc -lvlccore
