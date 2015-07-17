#include "mainwindow.h"
#include <QApplication>
#include "VLCVideoWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    VLCVideoWidget w("");
    w.show();

    return a.exec();
}
