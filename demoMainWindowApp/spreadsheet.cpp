#include "spreadsheet.h"

spreadsheet::spreadsheet(QWidget *parent)
    : QWidget(parent), isShowGrid(false)
{

}

spreadsheet::~spreadsheet()
{

}

bool spreadsheet::showGrid(){
    return isShowGrid;
}

void spreadsheet::setShowGrid(bool isShow){
    isShowGrid = isShow;
}

QString spreadsheet::currentLocation(){
    return QString("Unknown");
}

QString spreadsheet::currentFormula(){
    return QString("Unknown");
}

void spreadsheet::clear(){

}

bool spreadsheet::readFile(const QString &fileName){
    return true;
}

void spreadsheet::findNext(const QString &str, Qt::CaseSensitivity cs){

}

void spreadsheet::findPrevious(const QString &str, Qt::CaseSensitivity cs){

}

void spreadsheet::setCurrentCell(int col, int row){

}

QTableWidgetSelectionRange spreadsheet::selectRange(){
    QTableWidgetSelectionRange range;
    return range;
}

bool spreadsheet::writeFile(const QString &fileName){

}

/*
void spreadsheet::currentCellChanged(int x1, int y1, int x2, int y2){

}

void spreadsheet::modified(){

}
*/
