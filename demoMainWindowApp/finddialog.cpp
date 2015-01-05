#include "finddialog.h"
#include "ui_finddialog.h"

findDialog::findDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findDialog)
{
    ui->setupUi(this);

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableFindButton(const QString &)));
    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

findDialog::~findDialog()
{
    delete ui;
}

void findDialog::findClicked(){
    QString text = ui->lineEdit->text();
    Qt::CaseSensitivity cs = ui->caseCheckBox->isChecked()? Qt::CaseSensitive : Qt::CaseInsensitive;
    if(ui->backwardCheckBox->isChecked()){
        emit findPrevious(text, cs);
    }else{
        emit findNext(text, cs);
    }
}

void findDialog::enableFindButton(const QString &text){
    ui->findButton->setEnabled(!text.isEmpty());
}
