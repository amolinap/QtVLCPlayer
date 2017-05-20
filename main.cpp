#include <QApplication>

#include "VideoManagement.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VideoManagement w;
    w.show();

    return a.exec();
}
