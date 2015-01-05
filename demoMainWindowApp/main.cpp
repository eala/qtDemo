#include "mainwindow.h"
#include <QApplication>
#include "finddialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    findDialog w;
    w.show();

    return a.exec();
}
