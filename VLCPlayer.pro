#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T10:27:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VLCPlayer
TEMPLATE = app
TARGETDIR = $$OUT_PWD
BASEDIR = $$IN_PWD

VLC_SOURCE = source

INCLUDEPATH += $$VLC_SOURCE

HEADERS += $$VLC_SOURCE/VLCVideoWidget.h \
        $$VLC_SOURCE/VLCDisplay.h

SOURCES += main.cpp \
        $$VLC_SOURCE/VLCVideoWidget.cpp \
        $$VLC_SOURCE/VLCDisplay.cpp

FORMS += $$VLC_SOURCE/VLCVideoWidget.ui \
        $$VLC_SOURCE/VLCDisplay.ui

INCLUDEPATH += /Applications/VLC.app/Contents/MacOS/include \

LIBS += /Applications/VLC.app/Contents/MacOS/lib/libvlc.5.dylib \
/Applications/VLC.app/Contents/MacOS/lib/libvlccore.dylib \

macx: {
        HEADERS += $$VLC_SOURCE/VLCMacWidget.h \
                $$VLC_SOURCE/VLCNSView.h

        OBJECTIVE_SOURCES += $$VLC_SOURCE/VLCMacWidget.mm \
                $$VLC_SOURCE/VLCNSView.mm

    LIBS += -framework AppKit \
            -framework Cocoa
}

QMAKE_POST_LINK += echo "Copying files"
exists(/Applications/VLC.app)
{
    QMAKE_POST_LINK += && cp -r /Applications/VLC.app/Contents/MacOS/include $$TARGETDIR/VLCPlayer.app/Contents/MacOS
    QMAKE_POST_LINK += && cp -r /Applications/VLC.app/Contents/MacOS/lib $$TARGETDIR/VLCPlayer.app/Contents/MacOS
    QMAKE_POST_LINK += && cp -r /Applications/VLC.app/Contents/MacOS/plugins $$TARGETDIR/VLCPlayer.app/Contents/MacOS

    QMAKE_POST_LINK += && cp -f $$BASEDIR/bash/recordVLC.sh $$TARGETDIR/VLCPlayer.app/Contents/MacOS/recordVLC.sh
    QMAKE_POST_LINK += && cp -f $$BASEDIR/bash/pidprocess.sh $$TARGETDIR/VLCPlayer.app/Contents/MacOS/pidprocess.sh
}
