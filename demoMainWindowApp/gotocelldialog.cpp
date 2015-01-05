#include "gotocelldialog.h"
#include "ui_gotocelldialog.h"

gotoCellDialog::gotoCellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gotoCellDialog)
{
    ui->setupUi(this);
}

gotoCellDialog::~gotoCellDialog()
{
    delete ui;
}
