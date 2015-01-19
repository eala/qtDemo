#include <QWidget>
#include <QPushButton>
#include "gotocelldialog.h"

gotoCellDialog::gotoCellDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    // Important: QRegExp {a,b}: you cannot put any white space delimiter between a,b
    QRegExp regExp("[A-Za-z][1-9][0-9]{0,1}");
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
