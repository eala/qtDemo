#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

namespace Ui {
class gotoCellDialog;
}

class gotoCellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gotoCellDialog(QWidget *parent = 0);
    ~gotoCellDialog();

private:
    Ui::gotoCellDialog *ui;
};

#endif // GOTOCELLDIALOG_H
