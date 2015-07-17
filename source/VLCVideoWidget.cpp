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

VLCVideoWidget::VLCVideoWidget(const QString path, QWidget *parent) :
        QWidget(parent),
        //isRecord(false),
        //isPlay(false),
        //isRTSP(false),
        //fileSubtitles(NULL),
        ui(new Ui::VLCVideoWidget)
{
    ui->setupUi(this);

    pathVideo = path;
    lat = 0;
    lon = 0;
    alt = 0;
    alertRecord = false;

    vlcDisplay = new VLCDisplay(pathVideo, this);
    connect(vlcDisplay, SIGNAL(emitRecordVideo(bool)), this, SLOT(setRecordStyle(bool)));
    connect(vlcDisplay, SIGNAL(emitSizeFile(QString)), this, SLOT(setSizeFileVideo(QString)));
    createControlsVLC();

    //countSubTitle =0;
    //option =0;
    //isSubTitles = false;
    //readingSizeFile = false;
    //startTime = -1,
    //activeUAS = NULL;
    saveAutomatic = true;
    //fileSubtitles = NULL;
    //sizeFileRecord =0;
    //connect(UASManager::instance(), SIGNAL(activeUASSet(UASInterface*)), this, SLOT(setActiveUAS(UASInterface*)));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateInterface()));
    timer->start(1000);

    QDir d;
//    if(!d.exists(QDir::homePath()+"/videos"))
//    {
//        d.mkdir(QDir::homePath()+"/videos/");
//    }
    if(!d.exists(QCoreApplication::applicationDirPath()+"/../../../videos"))
    {
        //ui->label->setText(QCoreApplication::applicationDirPath()+"/../../../videos");

        if(d.mkdir("../../../videos"))
        {
            qDebug()<<" - "<<QCoreApplication::applicationDirPath()+"/../../../videos";

            //ui->label->setText(QCoreApplication::applicationDirPath()+"/../../../videos");
        }
    }

    qDebug()<<"QDir::homePath()+/videos/ "<<QDir::homePath()+"/videos/";
    qDebug()<<"QDir::currentPath()+/videos/ "<<QDir::currentPath()+"/videos/";
    qDebug()<<"QCoreApplication::applicationDirPath()+/videos/ "<<QCoreApplication::applicationDirPath()+"/videos/";
    qDebug()<<"QCoreApplication::applicationFilePath()+/videos/ "<<QCoreApplication::applicationFilePath()+"/../../../videos/";
}

void VLCVideoWidget::createControlsVLC()
{
    slVolume = new QSlider(Qt::Horizontal);
    QObject::connect(slVolume, SIGNAL(sliderMoved(int)), this, SLOT(changeVolume(int)));
    slVolume->setValue(80);

    slMediaPosition = new QSlider(Qt::Horizontal);
    slMediaPosition->setMaximum(1000);
    QObject::connect(slMediaPosition, SIGNAL(sliderMoved(int)), this, SLOT(changePosition(int)));

    vlDisplay = new QVBoxLayout(this);
    vlDisplay->setContentsMargins(2,2,2,2);    
    vlDisplay->addWidget(vlcDisplay);    
    vlDisplay->addWidget(slVolume);
    vlDisplay->addWidget(slMediaPosition);
    slVolume->setVisible(false);
    slMediaPosition->setVisible(false);

    hlButtonOptions = new QHBoxLayout();
    btPlay = new QPushButton(QIcon(":/images/icons_ET/Play.png"), "", this);
    btPlay->setToolTip("Reproducir");
    connect(btPlay, SIGNAL(clicked()), this, SLOT(play()));

    btStop = new QPushButton(QIcon(":/images/icons_ET/Stop.png"), "", this);
    btStop->setToolTip("Detener");
    connect(btStop, SIGNAL(clicked()), this, SLOT(stop()));

    btOpenRTSP = new QPushButton(QIcon(":/images/icons_ET/Radio.png"), "", this);
    btOpenRTSP->setToolTip("Abrir RTSP");
    connect(btOpenRTSP, SIGNAL(clicked()), this, SLOT(openRTSP()));

    btOpenFile = new QPushButton(QIcon(":/images/icons_ET/Open.png"), "", this);
    btOpenFile->setToolTip("Abrir Video");
    connect(btOpenFile, SIGNAL(clicked()), this, SLOT(openFile()));

    btRecord = new QPushButton(QIcon(":/images/icons_ET/Record.png"), "", this);
    btRecord->setToolTip("Grabar");
    connect(btRecord, SIGNAL(clicked()), this, SLOT(record()));

    hlButtonOptions->addWidget(btPlay);
    hlButtonOptions->addWidget(btStop);
    hlButtonOptions->addWidget(btOpenRTSP);
    hlButtonOptions->addWidget(btOpenFile);
    hlButtonOptions->addWidget(btRecord);

    vlDisplay->addLayout(hlButtonOptions);

    QHBoxLayout *hlLabelMedia = new QHBoxLayout();
    lbTittle = new QLabel(this);
    lbTittle->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    lbTittle->setText("");
    lbSizeFile = new QLabel(this);
    lbSizeFile->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    lbSizeFile->setText("----");
    hlLabelMedia->addWidget(lbTittle);
    hlLabelMedia->addWidget(lbSizeFile);
    vlDisplay->addLayout(hlLabelMedia);

    styleButtonRed = QString("QAbstractButton { background-color: rgb(255, 5, 0); border-color: rgb(10, 10, 10)} QAbstractButton:checked { border: 2px solid #379AC3; }");
    styleButtonGreen = QString("QAbstractButton { background-color: rgb(11, 255, 0); border-color: rgb(10, 10, 10)} QAbstractButton:checked { border: 2px solid #379AC3; }");

    btRecord->setStyleSheet(styleButtonGreen);
    //processRecord.setProcessChannelMode(QProcess::MergedChannels);
    ui->groupBox->setLayout(vlDisplay);

    acVolume = new QAction("Ver control volumen", this);
    acMediaPosition = new QAction("Ver linea de avance", this);
    acVolume->setCheckable(true);
    acVolume->setChecked(false);
    acMediaPosition->setCheckable(true);
    acMediaPosition->setChecked(false);
}

void VLCVideoWidget::play()
{
    if(!lbTittle->text().isEmpty())
    {
        vlcDisplay->playVideo();

        if(saveAutomatic)
        {
            vlcDisplay->runRecordVideo();
        }
    }
}

void VLCVideoWidget::stop()
{
    vlcDisplay->stopVideo();

    if(saveAutomatic)
    {
        vlcDisplay->stopRecorVideo();
    }
}

VLCVideoWidget::~VLCVideoWidget()
{
    delete vlcDisplay;

    delete ui;
}

void VLCVideoWidget::openRTSP()
{
    bool ok;

    QStringList url = (QStringList() << tr("rtsp://201.168.1.30:554/axis-media/media.amp") << tr("http://192.168.1.90/mjpg/video.mjpg"));

    //QString text = QInputDialog::getText(this, tr("Ingrese la URL"), tr("URL RTSP Axis:"), QLineEdit::Normal, tr("rtsp://192.168.1.90:554/axis-media/media.amp"), &ok);
    QString text = QInputDialog::getItem(this, tr("Ingrese la URL"), tr("URL RTSP Axis:"), url, 0, true, &ok);

    if (ok && !text.isEmpty())
    {        
        addURL(text, true);
    }
}

void VLCVideoWidget::openFile()
{
    QString fileName(QFileDialog::getOpenFileName(this, tr("Abrir"), pathVideo, tr("Archivo de video (*.avi | *.mp4 | *.mpg | *.mov)")));//"settings/", tr("Movie Files (*.avi)")));

    if (fileName.isEmpty())
        return;

    addURL(fileName, false);
}

void VLCVideoWidget::addURL(const QString url, bool isRTSP)
{
    vlcDisplay->addURL(url, isRTSP);    
    lbTittle->setText(url);

    if(!isRTSP)
    {
        QDir dirInfo(url);
        lbTittle->setText("../"+dirInfo.dirName());
        lbTittle->setToolTip(url);
    }
}

void VLCVideoWidget::record()
{
    vlcDisplay->recordVideo();
}

void VLCVideoWidget::changePATH(const QString &path)
{
    this->pathVideo = path;
    vlcDisplay->changePATH(path);
}

void VLCVideoWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(acVolume);
    menu.addAction(acMediaPosition);
    menu.exec(event->globalPos());
}

void VLCVideoWidget::updateInterface()
{
    vlcDisplay->setPositionUAV(this->lat, this->lon, this->alt);
    vlcDisplay->updateInterface();

    if(!vlcDisplay->getIsRecord())
    {
        if(alertRecord)
        {
            ui->groupBox->setStyleSheet("QGroupBox {border-color: #FF3333;}");
        }
        else
        {
            ui->groupBox->setStyleSheet("QGroupBox {border-color: #66FF33;}");
        }

        alertRecord = !alertRecord;
    }
}

void VLCVideoWidget::updateAltitude(double z)
{
    this->alt = z;
}

void VLCVideoWidget::setSavedAutomatic(bool automatic)
{
    Q_UNUSED(automatic);

    saveAutomatic = automatic;

    if(saveAutomatic)
    {
        vlcDisplay->runRecordVideo();
    }
    else
    {
        vlcDisplay->stopRecorVideo();
    }
}

void VLCVideoWidget::setRecordStyle(bool status)
{
    if(status)
    {
        btRecord->setStyleSheet(styleButtonRed);
        ui->groupBox->setStyleSheet("QGroupBox {border-color: #6495ED;}");
    }
    else
    {
        btRecord->setStyleSheet(styleButtonGreen);
    }
}

void VLCVideoWidget::setSizeFileVideo(QString size)
{
    lbSizeFile->setText(size);
}

void VLCVideoWidget::setVideoURL(const QString &url)
{
    vlcDisplay->setVideoURL(url);
}

QString VLCVideoWidget::getVideoURL()
{
    return vlcDisplay->getVideoURL();
}
