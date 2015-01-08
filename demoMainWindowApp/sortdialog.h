#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "ui_sortdialog.h"
#include "spreadsheet.h"

class sortDialog : public QDialog, public Ui::sortDialog
{
    Q_OBJECT

public:
    sortDialog(QWidget *parent = 0);
    void setColumnRange(QChar first, QChar last);
    void setSpreadsheet(spreadsheet *sheet){mSpreadsheet = sheet;}

private:
    spreadsheet *mSpreadsheet;
};

#endif // SORTDIALOG_H
