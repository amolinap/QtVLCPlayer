#include <QApplication>
#include "VLCVideoWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VLCVideoWidget w("");
    w.show();

    return a.exec();
}
