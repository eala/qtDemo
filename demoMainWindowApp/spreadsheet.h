#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QWidget>

class spreadsheet : public QWidget
{
    Q_OBJECT
public:
    explicit spreadsheet(QWidget *parent = 0);
    ~spreadsheet();

signals:

public slots:
    bool showGrid();
    void setShowGrid(bool isShow);
    QString currentLocation();
    QString currentFormula();
    void clear();

private:
    bool isShowGrid;
};

#endif // SPREADSHEET_H
