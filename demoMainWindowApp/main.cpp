#include "mainwindow.h"
#include <QApplication>
#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#if MDI
    mainWindow *window = new mainWindow;
    window->show();
#else
    mainWindow window;
    window.show();
#endif
    return app.exec();
}
