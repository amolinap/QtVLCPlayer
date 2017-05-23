/**
 * @file
 *   @brief Definition of class VLCVideoWidget
 *
 *   @author Alejandro Molina Pulido <am.alex09@gmail.com>
 *
 */

#include "VLCVideoWidget.h"
#include "ui_VLCVideoWidget.h"

#define qtu( i ) ((i).toUtf8().constData())

VLCVideoWidget::VLCVideoWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::VLCVideoWidget)
{
    ui->setupUi(this);

    vlcDisplay = new VLCDisplay(this);

    createControlsVLC();
}

void VLCVideoWidget::createControlsVLC()
{
    vlDisplay = new QVBoxLayout(this);
    vlDisplay->setContentsMargins(2,2,2,2);    
    vlDisplay->addWidget(vlcDisplay);    

    QHBoxLayout *hlLabelMedia = new QHBoxLayout();
    lbTittle = new QLabel(this);
    lbTittle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    lbTittle->setText(tr(""));
    hlLabelMedia->addWidget(lbTittle);
    vlDisplay->addLayout(hlLabelMedia);

    ui->groupBox->setLayout(vlDisplay);

    acPlay = new QAction(QIcon(":/images/Play.png"), tr("Play"), this);
    connect(acPlay, SIGNAL(triggered()), this, SLOT(play()));

    acStop = new QAction(QIcon(":/images/Stop.png"), tr("Stop"), this);
    connect(acStop, SIGNAL(triggered()), this, SLOT(stop()));

    acNetwork = new QAction(QIcon(":/images/Server.png"), tr("Open Stream"), this);
    connect(acNetwork, SIGNAL(triggered()), this, SLOT(openRTSP()));

    acFile = new QAction(QIcon(":/images/Open.png"), tr("Open File"), this);
    connect(acFile, SIGNAL(triggered()), this, SLOT(openFile()));
}

void VLCVideoWidget::play()
{
    if(!lbTittle->text().isEmpty())
    {
        vlcDisplay->playVideo();
    }
}

void VLCVideoWidget::stop()
{
    vlcDisplay->stopVideo();
}

VLCVideoWidget::~VLCVideoWidget()
{
    delete vlcDisplay;

    delete ui;
}

void VLCVideoWidget::openRTSP()
{
    bool ok;

    QStringList url = (QStringList() << tr("rtp://239.255.1.12"));

    QString text = QInputDialog::getItem(this, tr("Open Network Stream"), tr("URL:"), url, 0, true, &ok);

    if (ok && !text.isEmpty())
    {        
        addURL(text, true);
    }
}

void VLCVideoWidget::openFile()
{
    QString fileName(QFileDialog::getOpenFileName(this, tr("Open"), "/", tr("Open File (*.avi | *.mp4 | *.mpg | *.mov)")));

    if (fileName.isEmpty())
        return;

    addURL(fileName, false);
}

void VLCVideoWidget::addURL(const QString url, bool isRTSP)
{
    vlcDisplay->addURL(url, isRTSP);    

    if(!isRTSP)
    {
        QDir dirInfo(url);

        QString name = dirInfo.dirName();

        if(name.count() > 20)
        {
            lbTittle->setText("../"+dirInfo.dirName().remove(19, name.count()));
        }
        else
        {
            lbTittle->setText("../"+dirInfo.dirName());
        }


        lbTittle->setToolTip(url);
    }
    else
    {
        lbTittle->setText(url);
    }
}

void VLCVideoWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(acPlay);
    menu.addAction(acStop);
    menu.addAction(acNetwork);
    menu.addAction(acFile);
    menu.exec(event->globalPos());
}

void VLCVideoWidget::setVideoURL(const QString &url)
{
    vlcDisplay->setVideoURL(url);
}

QString VLCVideoWidget::getVideoURL()
{
    return vlcDisplay->getVideoURL();
}
