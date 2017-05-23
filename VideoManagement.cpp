#include "VideoManagement.h"
#include "ui_VideoManagement.h"

VideoManagement::VideoManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoManagement)
{
    ui->setupUi(this);

    video1 = new VLCVideoWidget();
    video2 = new VLCVideoWidget();
    video3 = new VLCVideoWidget();
    video4 = new VLCVideoWidget();

    video5 = new VLCVideoWidget();
    video6 = new VLCVideoWidget();
    video7 = new VLCVideoWidget();
    video8 = new VLCVideoWidget();

    QHBoxLayout* row1 = new QHBoxLayout();
    row1->addWidget(video1);
    row1->addWidget(video2);
    row1->addWidget(video3);
    row1->addWidget(video4);

    QHBoxLayout* row2 = new QHBoxLayout();
    row2->addWidget(video5);
    row2->addWidget(video6);
    row2->addWidget(video7);
    row2->addWidget(video8);

    QPushButton* btClose = new QPushButton(tr("Cerrar"), this);
    connect(btClose, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* row3 = new QHBoxLayout();
    row3->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    row3->addWidget(btClose);

    QVBoxLayout* column = new QVBoxLayout(this);
    column->addLayout(row1);
    column->addLayout(row2);
    column->addLayout(row3);    

    setLayout(column);

    this->setWindowTitle(tr("%0 v%1").arg(APP_NAME).arg(APP_VERSION));

    getIPAddress();
}

VideoManagement::~VideoManagement()
{
    delete ui;
}

void VideoManagement::getIPAddress()
{
    QHostInfo networkInfo(QHostInfo::fromName(QHostInfo::localHostName()));

    foreach (const QHostAddress &address, networkInfo.addresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            setWindowTitle(windowTitle()+" ["+ address.toString()+"] ");
        }
    }
}
