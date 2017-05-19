/**
 * @file
 *   @brief Definition of class VLCVideoWidget
 *
 *   @author Alejandro Molina Pulido <am.alex09@gmail.com>
 *
 */

#ifndef VLCVIDEOWIDGET_H
#define VLCVIDEOWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QSlider>
#include <QSpacerItem>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QInputDialog>
#include <QFileDialog>
#include <QMenu>
#include <unistd.h>
#include <signal.h>

#include "VLCMacWidget.h"
#include "vlc/vlc.h"
#include "VLCDisplay.h"

namespace Ui {
    class VLCVideoWidget;
}

/**
  * @brief It is the interface that contains the control that displays the video
  *
  * The VLCVideoWidget class represents the interface that displays the video.
  *
  * @see VLCDisplay
**/
class VLCVideoWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief This is the class constructor.
     *
     * @param path The path for instance to play
     * @param parent The parent the widget
     **/
    explicit VLCVideoWidget(const QString path, QWidget *parent = 0);
    ~VLCVideoWidget();

private:
    Ui::VLCVideoWidget *ui;
    VLCDisplay* vlcDisplay;

    QSlider* slVolume;
    QSlider* slMediaPosition;
    QGroupBox* gbVLCDisplay;
    QPushButton *btPlay;
    QPushButton *btStop;
    QPushButton *btOpenRTSP;
    QPushButton *btOpenFile;
    QVBoxLayout *vlDisplay;
    QHBoxLayout *hlMain;
    QHBoxLayout *hlButtonOptions;
    QLabel *lbTittle;
    QAction* acVolume, *acMediaPosition;

    QString styleButtonRed;
    QString styleButtonGreen;
    QString pathVideo;    
    bool saveAutomatic;
    bool alertRecord;

protected:
    /** @brief Holds the latitude actual UAV */
    double lat;
    /** @brief Holds the longitude actual UAV */
    double lon;
    /** @brief Holds the altitude actual UAV */
    double alt;
    /**
     * @brief This method manage the opening a context menu.
     *
     * @param event Describe a context menu
     **/
    void contextMenuEvent(QContextMenuEvent *);
    /**
     * @brief This method initializa the controls for VLC video player.
     **/
    void createControlsVLC();    

public slots:
    /**
     * @brief This method add new URL media for video player.
     *
     * @param url The URL where the video store
     **/
    void addURL(const QString url, bool isRTSP);
    /**
     * @brief This method allows assign new path to video open/store.
     *
     * @param path The path where the video open/store
     **/
    void changePATH(const QString& path);
    /**
     * @brief This method playback starts.
     */
    void play();
    /**
     * @brief This method playback stops.
     */
    void stop();
    /**
     * @brief This method playback starts.
     */
    void openRTSP();
    /**
     * @brief This method open file in a directory.
     */
    void openFile();
    /**
     * @brief This method video storage begins.
     */
    void record();
    /**
     * @brief This method updates the status of the video interface.
     */
    void updateInterface();
    /**
     * @brief This method active the UAS to read GPS position.
     */
    //void setActiveUAS(UASInterface* uas);
    /**
     * @brief This method current GPS position the UAS active.
     *
     * @param uas Represents an unmanned aerial vehicle
     * @param lat Latitude actual of GPS in UAV
     * @param lon Longitude actual of GPS in UAV
     * @param alt Altitude actual of GPS in UAV
     * @param usec UNIX timestamp in milliseconds
     */
    //void updateGlobalPosition(UASInterface* uas, double lat, double lon, double alt, quint64 usec);
    /** @brief Receive update the altitude UAS
      *
      * @param z New altitude in plane z
    */
    void updateAltitude(double z);
    /**
      * @brief Enables automatic information stored
      *
      * @param saved If enabled the auto saved
    */
    void setSavedAutomatic(bool automatic);
    /**
     * @brief Edit button style used to store video
     *
     * @param status Indicates if stored
     **/
    void setRecordStyle(bool status);
    /**
     * @brief Get the current size of the file that stores the video
     *
     * @param size Size the file
     **/
    void setSizeFileVideo(QString size);
    /**
     * @brief Assign the new URL of video storage
     *
     * @param url URL of video storage
     **/
    void setVideoURL(const QString& url);
    /** @brief Return the URL of video storage */
    QString getVideoURL();

signals:
};

#endif // VLCVIDEOWIDGET_H
