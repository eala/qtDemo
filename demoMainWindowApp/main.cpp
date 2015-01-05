#include "mainwindow.h"
#include <QApplication>
#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //findDialog findDlg;
    //findDlg.show();
    //gotoCellDialog *gotoCellDlg = new gotoCellDialog;
    //gotoCellDlg->show();
    sortDialog *sortDlg = new sortDialog;
    sortDlg->setColumnRange('C', 'F');
    sortDlg->show();

    return a.exec();
}
