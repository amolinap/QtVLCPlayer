#include "VLCDisplay.h"
#include "ui_VLCDisplay.h"

#define qtu( i ) ((i).toUtf8().constData())

VLCDisplay::VLCDisplay(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::VLCDisplay)
{
    ui->setupUi(this);

    isPlay = false;
    isRTSP = false;
    url = "";

    videoURL = "rtp://239.255.1.12";

    createInstanceVLC(videoURL);
    mediaPlayer = libvlc_media_player_new_from_media(media);

    #if defined Q_OS_LINUX
        libvlc_media_player_set_xwindow(mediaPlayer, ui->gbPlayer->winId());
    #endif

    #if defined Q_OS_MAC
        vlcMacWidget = new VLCMacWidget(mediaPlayer, ui->gbPlayer);
    #endif

    //addURL(videoURL, true);
}

VLCDisplay::~VLCDisplay()
{
    if(instance)
    {
        libvlc_release(instance);
    }

    delete ui;
}

void VLCDisplay::playVideo()
{
    if(libvlc_media_player_is_playing(mediaPlayer)==1)
    {
        libvlc_media_player_pause(mediaPlayer);        
        isPlay = false;
    }
    else
    {
        libvlc_media_player_play(mediaPlayer);        
        isPlay = true;
    }    
}

void VLCDisplay::stopVideo()
{
    if(libvlc_media_player_is_playing(mediaPlayer)==1)
    {        
        libvlc_media_player_stop(mediaPlayer);
        isPlay = false;
    }
}

void VLCDisplay::addURL(const QString url, bool isRTSP)
{
    stopVideo();

    this->url = url;
    this->isRTSP = isRTSP;

    if(instance)
    {
        libvlc_release(instance);
    }

    createInstanceVLC(qtu(url));

    libvlc_media_player_set_media(mediaPlayer, media);
}

void VLCDisplay::createInstanceVLC(const QString url)
{
    qDebug()<<"URL: "<<url;

    char const *argv[] =
    {
        "--no-video-title-show",
        "--no-skip-frames",
        //"--no-audio",
        "--plugin-path",
        "--ignore-config", //Don't use VLC's config files
        "--rtsp-caching=0",
    };
    int argc = sizeof( argv ) / sizeof( *argv );

    instance = libvlc_new(argc, argv);

    if(isRTSP)
    {
        media = libvlc_media_new_location(instance, qtu(url));
    }
    else
    {
        media = libvlc_media_new_path(instance, qtu(url));
    }
}

void VLCDisplay::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}

void VLCDisplay::setVideoURL(const QString &url)
{
    videoURL = url;
}

QString VLCDisplay::getVideoURL()
{
    return videoURL;
}
