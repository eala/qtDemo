#include <QWidget>
#include <QPushButton>
#include "gotocelldialog.h"

gotoCellDialog::gotoCellDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QRegExp regExp("[A-Za-z]");
    lineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

gotoCellDialog::~gotoCellDialog()
{
}

void gotoCellDialog::on_lineEdit_textChanged(){
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(lineEdit->hasAcceptableInput());
}
