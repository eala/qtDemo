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
