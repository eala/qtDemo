#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
#include "ui_gotocelldialog.h"

class QPushButton;

class gotoCellDialog : public QDialog, public Ui::gotoCellDialog
{
    Q_OBJECT

public:
    gotoCellDialog(QWidget *parent = 0);
    ~gotoCellDialog();

private slots:
    void on_lineEdit_textChanged();
};

#endif // GOTOCELLDIALOG_H
