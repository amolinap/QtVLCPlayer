#ifndef VLCDISPLAY_H
#define VLCDISPLAY_H

#include <QWidget>

#include "VLCMacWidget.h"
#include "vlc/vlc.h"
#include <unistd.h>
#include <signal.h>

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
    /** @brief Updates the interface to manage data that are displayed and stored */
    void updateInterface();
    bool getIsRecord(){ return isRecord; }
    bool getIsPlay(){ return isPlay; }

private:
    Ui::VLCDisplay *ui;
    /** @brief Holds instance video player for visualization */
    VLCMacWidget* vlcMacWidget;
    /** @brief Holds instance configuration for video player */
    libvlc_instance_t * instance;
    /** @brief Holds instance media video player */
    libvlc_media_player_t * mediaPlayer;
    /** @brief Holds instance playable media */
    libvlc_media_t * media;
    QString videoURL;

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
     * @brief This method video storage begins.
     */
    void recordVideo();
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
     * @brief This method reads the process to know the status of video storage.
     *
     * @return If the process has been canceled
     */
    bool readPIDProcess();
    /**
     * @brief This method consultation process state video storage.
     */
    void viewPIDProcess();
    /**
     * @brief This method allows assign new path to video open/store.
     *
     * @param path The path where the video open/store
     **/
    void changePATH(const QString& path);
    /**
     * @brief This method return the time actual in milliseconds.
     *
     * @return Time in milliseconds
     **/
    quint64 getGroundTimeNow();    
    /** @brief Starts the process of storing video */
    void runRecordVideo();
    /** @brief Stops the video storage */
    void stopRecorVideo();
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
    /** @brief Saved if video player is recording */
    bool isRecord;
    /** @brief Saved if video player is play */
    bool isPlay;
    QString url, pathVideo, nameFile;
    QProcess processRecord;
    /** @brief Ready size file where store video */
    bool readingSizeFile;
    int idProcess, option;
    qint64 sizeFileRecord;
    void resizeEvent(QResizeEvent *size);
    /**
     * @brief This method manage the close window event.
     *
     * @param event Describe a close event
     **/
    void closeEvent(QCloseEvent *event);    

signals:
    void emitRecordVideo(bool);
    void emitSizeFile(QString);
};

#endif // VLCDISPLAY_H
