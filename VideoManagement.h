#ifndef VIDEOMANAGEMENT_H
#define VIDEOMANAGEMENT_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QObject>
#include <QSpacerItem>
#include <QHostAddress>
#include <QHostInfo>

#include "VLCVideoWidget.h"
#include "QtConfiguration.h"

namespace Ui {
class VideoManagement;
}

class VideoManagement : public QWidget
{
    Q_OBJECT

public:
    explicit VideoManagement(QWidget *parent = 0);
    ~VideoManagement();

private:
    Ui::VideoManagement *ui;

    VLCVideoWidget* video1;
    VLCVideoWidget* video2;
    VLCVideoWidget* video3;
    VLCVideoWidget* video4;
    VLCVideoWidget* video5;
    VLCVideoWidget* video6;
    VLCVideoWidget* video7;
    VLCVideoWidget* video8;

public slots:
    void getIPAddress();
};

#endif // VIDEOMANAGEMENT_H
