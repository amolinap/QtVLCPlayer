VLC_SOURCE = vlc/VLC_source

INCLUDEPATH += $$VLC_SOURCE

HEADERS += $$VLC_SOURCE/VLCVideoWidget.h \
    vlc/VLC_source/VLCDisplay.h


SOURCES += $$VLC_SOURCE/VLCVideoWidget.cpp \
    vlc/VLC_source/VLCDisplay.cpp


FORMS += $$VLC_SOURCE/VLCVideoWidget.ui \
    vlc/VLC_source/VLCDisplay.ui


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
