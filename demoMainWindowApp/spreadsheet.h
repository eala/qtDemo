#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetSelectionRange>

class Cell;
class SpreadsheetCompare;

class spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    explicit spreadsheet(QWidget *parent = 0);
    ~spreadsheet();

    bool autoRecalculate() const { return autoRecalc;}
    QString currentLocation() const;
    QString currentFormula() const;
    QTableWidgetSelectionRange selectedRange() const;
    void clear();
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    void sort(const SpreadsheetCompare &compare);

signals:
    //void currentCellChanged(int x1, int y1, int x2, int y2);
    void modified();
private slots:
    void somethingChanged();

public slots:
    void cut();
    void copy();
    void paste();
    void del();
    void selectCurrentRow();
    void selectCurrentColumn();
    void recalculate();
    void setAutoRecalculate(bool recalc);
    bool isAutoRecalculate(){ return autoRecalc;}
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private:
    enum {MagicNumber = 0x7F51C883, RowCount = 999, ColumnCount = 26};
    Cell *cell(int row, int column) const;
    QString text(int row, int column) const;
    QString formula(int row, int column) const;
    void setFormula(int row, int column, const QString &formula);

    bool autoRecalc;
};

class SpreadsheetCompare{
public:
    bool operator()(const QStringList &row1,
                    const QStringList &row2) const;
    enum { KeyCount = 3};
    int keys[KeyCount];
    bool ascending[KeyCount];
};

#endif // SPREADSHEET_H
