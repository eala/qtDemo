#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QWidget>
#include <QTableWidgetSelectionRange>

class spreadsheet : public QWidget
{
    Q_OBJECT
public:
    explicit spreadsheet(QWidget *parent = 0);
    ~spreadsheet();

signals:
    //void currentCellChanged(int x1, int y1, int x2, int y2);
    //void modified();

public slots:
    bool showGrid();
    void setShowGrid(bool isShow);
    QString currentLocation();
    QString currentFormula();
    void clear();
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
    void setCurrentCell(int col, int row);
    QTableWidgetSelectionRange selectRange();


private:
    bool isShowGrid;
};

#endif // SPREADSHEET_H
