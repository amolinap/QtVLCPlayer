#include "VLCDisplay.h"
#include "ui_VLCDisplay.h"

#define qtu( i ) ((i).toUtf8().constData())

VLCDisplay::VLCDisplay(const QString path, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::VLCDisplay)
{
    ui->setupUi(this);

    isRecord = false;
    isPlay = false;
    isRTSP = false;
    isSubTitles = false;
    url = "";
    lat = 0;
    lon = 0;
    alt = 0;
    pathVideo = "videos/";

    videoURL = "rtsp://201.168.1.30:554/axis-media/media.amp";
    startTime=-1;

    createInstanceVLC(path);
    mediaPlayer = libvlc_media_player_new_from_media(media);
    vlcMacWidget = new VLCMacWidget(mediaPlayer, ui->groupBox);
    vlcMacWidget->setMinimumHeight(ui->groupBox->height());
    vlcMacWidget->setMinimumWidth(ui->groupBox->width());

    readingSizeFile = false;
    fileSubtitles = NULL;
    option =0;    
    processRecord.setProcessChannelMode(QProcess::MergedChannels);

}

VLCDisplay::~VLCDisplay()
{
    if(instance)
    {
        libvlc_release(instance);
    }

    stopRecorVideo();

    //delete mediaPlayer;
    //delete media;
    //delete vlcMacWidget;

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

void VLCDisplay::recordVideo()
{
    if(isRTSP)
    {
        //if(libvlc_media_player_is_playing(mediaPlayer)==1)
        if(mediaPlayer)
        {
            if(!isRecord)
            {
                runRecordVideo();                
            }
            else
            {
                stopRecorVideo();                
            }
        }
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

    if(instance)
    {
        libvlc_release(instance);
    }

    createInstanceVLC(qtu(url));
    libvlc_media_player_set_media(mediaPlayer, media);

    this->url = url;
    this->isRTSP = isRTSP;
    //playVideo();
}

void VLCDisplay::createInstanceVLC(const QString url)
{
    char const *argv[] =
    {
        //"-vvvvv",
        "--no-video-title-show",
        "--no-skip-frames",
        //"--no-audio",
        //"--plugin-path", VLC_TREE "/modules",
        "--ignore-config", //Don't use VLC's config files
        "--rtsp-caching=10",
        "--no-snapshot-preview"
        //"--{rtsp,http,sout-mux}-caching"
    };
    int argc = sizeof( argv ) / sizeof( *argv );

    instance = libvlc_new(argc, argv);
    media = libvlc_media_new_path(instance, qtu(url));
}

void VLCDisplay::createFileSubTitles(QString file)
{
    QString fileName(file);

    if (fileName.isEmpty())
        return;

    QString tempFile(QFileInfo(fileName).baseName());
    QString tempPath(QFileInfo(fileName).dir().path()+"/");

    if(fileSubtitles== NULL)
    {
        fileSubtitles = new QFile();
    }

    if(fileSubtitles->fileName() != tempPath + "/" + tempFile + ".srt")
    {
        if(!QFileInfo(tempPath+"/"+tempFile+".srt").exists())
        {
            fileSubtitles->setFileName(file+".srt");
            fileSubtitles->open(QIODevice::WriteOnly | QIODevice::Append);
        }
    }

    this->isSubTitles = true;
}

void VLCDisplay::viewPIDProcess()
{
    pid_t pid = (pid_t)idProcess;
    QStringList arguments;
    arguments << QString::number(pid) << QCoreApplication::applicationDirPath() + "/outPID.txt";

    QProcess process;
    process.start(QCoreApplication::applicationDirPath() + "/./pidprocess.sh", arguments);
    process.waitForFinished(2000);
    process.close();
    process.kill();
}

bool VLCDisplay::readPIDProcess()
{
    viewPIDProcess();

    qDebug()<<QCoreApplication::applicationDirPath() + "/outPID.txt";
    if(!QFileInfo(QCoreApplication::applicationDirPath() + "/outPID.txt").exists())
    {        
        return true;
    }    

    QFile file(QCoreApplication::applicationDirPath() + "/outPID.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);

    int i=0;
    while (!in.atEnd())
    {
        const QStringList &wpParams = in.readLine().split(" ");//\t");
        qDebug()<<wpParams;
        qDebug()<<wpParams.size();
        i++;
    }

    qDebug()<<"i: "<<i;
    if(i==1)
        return true;

    return false;
}

void VLCDisplay::changePATH(const QString &path)
{
    this->pathVideo = path;
}

void VLCDisplay::updateInterface()
{
    if(isPlay)
    {
        if(mediaPlayer) //It segfault if vlcPlayer don't exist
        {
            switch(libvlc_media_player_get_state(mediaPlayer))
            {
            case 6:
                libvlc_media_player_stop(mediaPlayer);
                //btPlay->setIcon(QIcon(":/images/icons_ET/Play.png"));
                break;

            case 7:
                libvlc_media_player_release(mediaPlayer);
                //btPlay->setIcon(QIcon(":/images/icons_ET/Play.png"));
                break;
            default:
                break;
            }
        }
    }

    if(isRecord)
    {
        if(isSubTitles)
        {
            QTextStream streamData(fileSubtitles);

            if(startTime== (quint64)-1)
            {
                startTime = getGroundTimeNow();
            }

            quint64 filterTime = (getGroundTimeNow()-startTime)/1000;
            int sec = static_cast<int>(filterTime - static_cast<int>(filterTime / 60) * 60);
            int min = static_cast<int>(filterTime / 60)-((static_cast<int>(filterTime / 60)/60)*60);
            int hours = static_cast<int>((filterTime / 60)/60);
            QString timeText1;
            timeText1 = timeText1.sprintf("%02d:%02d:%02d", hours, min, sec);

            streamData
                    << countSubTitle << "\r\n"
                    << timeText1 << "   <i> Lat: "<<this->lat<<" - Lon: "<<this->lon<<" - Alt: "<<this->alt<<"</i> \r\n"
                    << "\r\n\n";

            countSubTitle++;
        }

        QFileInfo fileInfo(nameFile+".mp4");

        if(fileInfo.exists())
        {
            if(sizeFileRecord != fileInfo.size())
            {
                sizeFileRecord = fileInfo.size();                
                emit emitSizeFile(QString::number(sizeFileRecord/1024)+" KB");
            }
            else
            {
                if(option == 4)
                {                    
                    emit emitRecordVideo(false);

                    bool closedVideo = false;
                    while (!closedVideo)
                    {
                        pid_t pid = (pid_t)idProcess;
                        qDebug()<<"KILL(pid, SIGINT): "<<kill(pid, SIGINT);
                        qDebug()<<"KILLPG(pid, SIGINT): "<<killpg(pid, SIGINT);

                        closedVideo = readPIDProcess();
                    }
                    qDebug()<<"Exit while...";

                    isRecord = false;
                    option=0;
                    //qDebug()<<"failed to save video: "<<idProcess;
                }

                option++;
                //qDebug()<<"closing " <<option;
            }
        }
        //qDebug()<<fileInfo.filePath()<< " "<<fileInfo.size()/1024<<" KB";
    }
}

quint64 VLCDisplay::getGroundTimeNow()
{
    QDateTime time = QDateTime::currentDateTime();
    time = time.toUTC();
    quint64 milliseconds = time.toTime_t() * static_cast<quint64>(1000);
    return static_cast<quint64>(milliseconds + time.time().msec());
}

void VLCDisplay::setPositionUAV(double lat, double lon, double alt)
{
    this->lat = lat;
    this->lon = lon;
    this->alt = alt;
}

//    char const *argv[] =
//    {
//        //"-vvvvv",
//        //"--no-video-title-show",
//        "--no-skip-frames",
//        //"--no-audio",
//        //"--plugin-path", VLC_TREE "/modules",
//        "--ignore-config", //Don't use VLC's config files
//        "--rtsp-caching=100"
//        //"--{rtsp,http,sout-mux}-caching"
//    };
//    int argc = sizeof( argv ) / sizeof( *argv );
//    instance = libvlc_new(argc, argv);//0, NULL);
//    libvlc_media_t * mediar =libvlc_media_new_path(instance, qtu(url));

void VLCDisplay::resizeEvent(QResizeEvent *size)
{
    vlcMacWidget->resize(size->size().width(), size->size().height());
}

void VLCDisplay::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    if(idProcess>0)
    {
        pid_t id = (pid_t)idProcess;//processRecord.pid()+1;
        processRecord.close();
        qDebug()<<"KILL(pid, SIGINT): "<<kill(id, SIGINT);
        qDebug()<<"KILLPG(pid, SIGINT): "<<killpg(id, SIGINT);
    }

    if(fileSubtitles)
    {
        if(fileSubtitles->isOpen())
        {
            fileSubtitles->close();
            fileSubtitles->flush();
        }
    }
}

//void VLCDisplay::setSaveAutomatic(bool automatic)
//{
//    this->savedAutomatic = automatic;

//    if(savedAutomatic)
//        runRecordVideo();
//    else
//        stopRecorVideo();
//}

void VLCDisplay::runRecordVideo()
{
    if(!isRecord && isRTSP)
    {
        QStringList arguments;
        QString fileName = QDate::currentDate().toString("yyyyMMdd")+QTime::currentTime().toString("HHmmss");
        arguments << videoURL << QCoreApplication::applicationDirPath()+"/../../../videos/" << fileName;

        processRecord.start(QCoreApplication::applicationDirPath() + "/./recordVLC.sh", arguments);

        nameFile = pathVideo + "/" + fileName;
        createFileSubTitles(nameFile);
        readingSizeFile = true;

        qDebug()<<"file: "<<QCoreApplication::applicationDirPath() << "/./recordVLC.sh" << " Argumentos:" <<arguments;
        idProcess = processRecord.pid()+1;

        emit emitRecordVideo(true);
        isRecord = true;
    }
}

void VLCDisplay::stopRecorVideo()
{
    if(isRecord && isRTSP)
    {
        emit emitRecordVideo(false);
        isRecord = false;

        if(fileSubtitles->isOpen())
        {
            isSubTitles = false;
            countSubTitle =0;
            startTime=-1;
            fileSubtitles->close();
            fileSubtitles->flush();
        }

        processRecord.close();
        processRecord.kill();

        bool closedVideo = false;
        while (!closedVideo)
        {
            pid_t pid = (pid_t)idProcess;
            qDebug()<<"KILL(pid, SIGINT): "<<kill(pid, SIGINT);
            qDebug()<<"KILLPG(pid, SIGINT): "<<killpg(pid, SIGINT);
            //qDebug()<<"While 2 Matando Proceso: "<<pid;

            closedVideo = readPIDProcess();
        }
        //qDebug()<<"Exit while...";
        idProcess =0;
    }
}

void VLCDisplay::setVideoURL(const QString &url)
{
    videoURL = url;
}

QString VLCDisplay::getVideoURL()
{
    return videoURL;
}
