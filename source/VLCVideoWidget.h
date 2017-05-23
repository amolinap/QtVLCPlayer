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
#include <QContextMenuEvent>
#include <QMenu>
#include <unistd.h>
#include <signal.h>

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
    explicit VLCVideoWidget(QWidget *parent = 0);
    ~VLCVideoWidget();

private:
    Ui::VLCVideoWidget *ui;
    VLCDisplay* vlcDisplay;

    QGroupBox* gbVLCDisplay;
    QVBoxLayout *vlDisplay;
    QHBoxLayout *hlMain;
    QLabel *lbTittle;
    QAction *acPlay, *acStop, *acNetwork, *acFile;

protected:
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
     * @brief Assign the new URL of video storage
     *
     * @param url URL of video storage
     **/
    void setVideoURL(const QString& url);
    /** @brief Return the URL of video storage */
    QString getVideoURL();

};

#endif // VLCVIDEOWIDGET_H
