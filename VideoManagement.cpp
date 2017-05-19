#include "VideoManagement.h"
#include "ui_VideoManagement.h"

VideoManagement::VideoManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoManagement)
{
    ui->setupUi(this);

    video1 = new VLCVideoWidget("");
    video2 = new VLCVideoWidget("");
    video3 = new VLCVideoWidget("");
    video4 = new VLCVideoWidget("");

    video5 = new VLCVideoWidget("");
    video6 = new VLCVideoWidget("");
    video7 = new VLCVideoWidget("");
    video8 = new VLCVideoWidget("");

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

    QVBoxLayout* column = new QVBoxLayout(this);
    column->addLayout(row1);
    column->addLayout(row2);
    //column->addSpacerItem(new QSpacerItem(0,1000, QSizePolicy::Expanding, QSizePolicy::Expanding));

    setLayout(column);
}

VideoManagement::~VideoManagement()
{
    delete ui;
}
