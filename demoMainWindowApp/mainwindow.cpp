#include <QWidget>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

#include "mainwindow.h"

#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"
#include "spreadsheet.h"

//mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
mainWindow::mainWindow()
{
    mSpreadsheet = new spreadsheet;
    setCentralWidget(mSpreadsheet);

    createActions();
    createMenus();

    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();
    mFindDialog = 0;
    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");

}

mainWindow::~mainWindow()
{

}

void mainWindow::createActions(){
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setToolTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile())); // it should be managed as createConnects()

    // un-implement
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Open"), this);
    saveAsAction = new QAction(tr("&Open"), this);

    cutAction = new QAction(tr("&Open"), this);
    copyAction = new QAction(tr("&Open"), this);
    pasteAction = new QAction(tr("&Open"), this);
    deleteAction = new QAction(tr("&Open"), this);

    selectRowAction = new QAction(tr("&Open"), this);
    selectColumnAction = new QAction(tr("&Open"), this);

    findAction = new QAction(tr("&Open"), this);
    gotoCellAction = new QAction(tr("&Open"), this);
    recalculateAction = new QAction(tr("&Open"), this);
    sortAction = new QAction(tr("&Open"), this);
    aboutAction = new QAction(tr("&Open"), this);

    for(int i=0; i<MaxRecentFiles; ++i){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setToolTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setToolTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(close()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(mSpreadsheet->showGrid());
    showGridAction->setShortcut(QKeySequence::SelectAll);
    showGridAction->setToolTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), mSpreadsheet, SLOT(setShowGrid(bool)));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void mainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    separatorAction = fileMenu->addSeparator();
    for(int i=0; i<MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(gotoCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void mainWindow::createContextMenu(){
    mSpreadsheet->addAction(cutAction);
    mSpreadsheet->addAction(copyAction);
    mSpreadsheet->addAction(pasteAction);
    mSpreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void mainWindow::createToolBars(){
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);

    editToolBar->addSeparator();

    editToolBar->addAction(findAction);
    editToolBar->addAction(gotoCellAction);
}

void mainWindow::createStatusBar(){
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(mSpreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
            this, SLOT(updateStatusBar()));
    connect(mSpreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));
    updateStatusBar();
}

void mainWindow::updateStatusBar(){
    locationLabel->setText(mSpreadsheet->currentLocation());
    formulaLabel->setText(mSpreadsheet->currentFormula());
}

void mainWindow::spreadsheetModified(){
    setWindowModified(true);
    updateStatusBar();
}

void mainWindow::newFile(){
    if(okToContinue()){
        mSpreadsheet->clear();
        setCurrentFile("");
    }
}

bool mainWindow::okToContinue(){
    if(isWindowModified()){
        int r = QMessageBox::warning(this, tr("Spreadsheet"),
                                     tr("The document has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(QMessageBox::Yes == r){
            return save();
        }else if(QMessageBox::Cancel == r){
            return false;
        }
    }
    return true;
}

// not implement yet
void mainWindow::closeEvent(QCloseEvent *event){

}

void mainWindow::readSettings(){

}

void mainWindow::openRecentFile(){

}

void mainWindow::setCurrentFile(const QString &fileName){

}

void mainWindow::find(){

}

void mainWindow::open(){

}

bool mainWindow::save(){
    return true;
}

void mainWindow::sort(){

}

void mainWindow::about(){

}

void mainWindow::saveAs(){

}

void mainWindow::goToCell(){

}
