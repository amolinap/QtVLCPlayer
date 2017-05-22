/**
 * @file
 *   @brief Definition of class VLCDisplay
 *
 *   @author Alejandro Molina Pulido <am.alex09@gmail.com>
 *
 */
#ifndef VLCDISPLAY_H
#define VLCDISPLAY_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <unistd.h>
#include <signal.h>

#include "vlc/vlc.h"
#include "VLCMacWidget.h"

namespace Ui {
    class VLCDisplay;
}

/**
  * @brief Is the control that displays the video
  *
  * The VLCDisplay class represents the control that displays the video without stabilization.
  *
  * @see VLCVideoWidget
**/
class VLCDisplay : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief This is the class constructor.
     *
     * @param path The path for instance to play
     * @param parent The parent the widget
     **/
    explicit VLCDisplay(const QString path, QWidget *parent = 0);
    virtual ~VLCDisplay();
    bool getIsPlay(){ return isPlay; }

private:
    Ui::VLCDisplay *ui;
    /** @brief Holds instance configuration for video player */
    libvlc_instance_t * instance;
    /** @brief Holds instance media video player */
    libvlc_media_player_t * mediaPlayer;
    /** @brief Holds instance playable media */
    libvlc_media_t * media;
    QString videoURL;

    #if defined Q_OS_MAC
        /** @brief Holds instance video player for visualization */
        VLCMacWidget* vlcMacWidget;
    #endif

public slots:    
    /**
     * @brief This method playback stops.
     */
    void stopVideo();
    /**
     * @brief This method playback starts.
     */
    void playVideo();
    /**
     * @brief This method add new URL media for video player.
     *
     * @param url The URL where the video store
     **/
    void addURL(const QString url, bool isRTSP);
    /**
     * @brief This method create the main instantiates VLC.
     *
     * @param path The path for instance to play
     **/
    void createInstanceVLC(const QString url);
    /**
     * @brief Assign the new URL of video storage
     *
     * @param url URL of video storage
     **/
    void setVideoURL(const QString& url);
    /** @brief Return the URL of video storage */
    QString getVideoURL();

protected:
    /** @brief Saved if video player is URL RTSP */
    bool isRTSP;
    /** @brief Saved if video player is play */
    bool isPlay;
    QString url, nameFile;
    /**
     * @brief This method manage the close window event.
     *
     * @param event Describe a close event
     **/
    void closeEvent(QCloseEvent *event);    

};

#endif // VLCDISPLAY_H
