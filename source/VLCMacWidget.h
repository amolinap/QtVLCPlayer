#ifndef VLCMACWIDGET_H
#define VLCMACWIDGET_H
#include <QtGui>
#import <qmaccocoaviewcontainer_mac.h>
#include "vlc/vlc.h"

/**
* Defines the instance for associate the display video player to widget
**/
class VLCMacWidget : public QMacCocoaViewContainer
{

public:
    /**
     * @brief This is the class constructor.
     *
     * @param mediaPlayer The media video player
     * @param parent The parent the video player
     **/
    VLCMacWidget(libvlc_media_player_t *mediaPlayer, QWidget *parent=0);
};

#endif // VLCMACWIDGET_H
