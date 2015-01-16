#include <QWidget>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QTableWidgetSelectionRange>
#include <QSettings>
#include <QCloseEvent>

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

    setAttribute(Qt::WA_DeleteOnClose);
}

mainWindow::~mainWindow()
{

}

void mainWindow::createActions(){
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile())); // it should be managed as createConnects()

    // un-implement
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    saveAsAction = new QAction(tr("&Save as"), this);

    cutAction = new QAction(tr("&Cut"), this);
    copyAction = new QAction(tr("&Copy"), this);
    pasteAction = new QAction(tr("&Paste"), this);
    deleteAction = new QAction(tr("&Delete"), this);

    selectRowAction = new QAction(tr("&Select Row"), this);
    selectColumnAction = new QAction(tr("&Select Column"), this);

    findAction = new QAction(tr("&Find"), this);
    gotoCellAction = new QAction(tr("&GotoCell"), this);
    autoRecalcAction = new QAction(tr("&AutoRecalc"), this);
    sortAction = new QAction(tr("&Sort"), this);
    myAboutAction = new QAction(tr("cannot about"), this);


    for(int i=0; i<MaxRecentFiles; ++i){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }


    closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setToolTip(tr("Close this window"));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setToolTip(tr("Exit the application"));
    //connect(exitAction, SIGNAL(triggered()), this, SLOT(closeAllWindows())); // there is no API closeAllWindows
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

    myAboutQtAction = new QAction(tr("About &Qt"), this);
    myAboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(myAboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void mainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    separatorAction = fileMenu->addSeparator();
    /*
    for(int i=0; i<MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    */
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
    toolsMenu->addAction(autoRecalcAction);
    toolsMenu->addAction(sortAction);

    menuBar()->addSeparator();

    myHelpMenu = menuBar()->addMenu(tr("&Help"));
    myHelpMenu->addAction(myAboutAction);
    myHelpMenu->addAction(myAboutQtAction);
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

    //connect(mSpreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
    //        this, SLOT(updateStatusBar()));
    //connect(mSpreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));
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
#if 1
    mainWindow *mainWin = new mainWindow;
    mainWin->show();
#else
    if(okToContinue()){
        mSpreadsheet->clear();
        setCurrentFile("");
    }
#endif
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

void mainWindow::open(){
    if(okToContinue()){
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Spreadsheet"), ".",
                                                        tr("Spreadsheet files (*.sp)"));
        if(!fileName.isEmpty()){
            loadFile(fileName);
        }
    }
}

void mainWindow::displayStatusBar(const QString &str){
    const int DISPLAY_TIME = 2000;
    statusBar()->showMessage(str, DISPLAY_TIME);
}

bool mainWindow::loadFile(const QString &fileName){
    if(!mSpreadsheet->readFile(fileName)){
        displayStatusBar(tr("Loading canceled"));
        return false;
    }

    setCurrentFile(fileName);
    displayStatusBar(tr("File loaded"));
    return true;
}

bool mainWindow::save(){
    if(curFile.isEmpty()){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}

bool mainWindow::saveFile(const QString &fileName){
    if(!mSpreadsheet->writeFile(fileName)){
        displayStatusBar(tr("Saving canceled"));
        return false;
    }

    setCurrentFile(fileName);
    displayStatusBar(tr("File saved"));
    return true;
}

bool mainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Spreadsheet"), ".",
                                                    tr("Spreadsheet files (*.sp)"));
    if(fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void mainWindow::closeEvent(QCloseEvent *event){
    if(okToContinue()){
        writeSettings();
        event->accept();
    }else{
        event->ignore();
    }
}

void mainWindow::setCurrentFile(const QString &fileName){
    curFile = fileName;
    setWindowModified(false);
    QString showName = tr("Untitled");
    if(curFile.isEmpty()){
        showName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(showName)
                                    .arg(tr("Spreadsheet")));
}

QString mainWindow::strippedName(const QString &fullFileName){
    return QFileInfo(fullFileName).fileName();
}

void mainWindow::updateRecentFileActions(){
#if 0
    QMutableStringListIterator it(recentFiles);
    while(it.hasNext()){
        if(!QFile::exists(it.next()))
            it.remove();
    }

    for(int j=0; j< MaxRecentFiles; ++j){
        if(j < recentFiles.count()){
            QString text = tr("&%1 %2")
                            .arg(j+1)
                            .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }else{
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
#endif
}

void mainWindow::openRecentFile(){
    if(okToContinue()){
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void mainWindow::find(){
    if(!mFindDialog){
        mFindDialog = new findDialog(this);
        connect(mFindDialog, SIGNAL(findNext(const QString &, Qt::CaseSensitivity)),
                mSpreadsheet, SLOT(findNext(const QString &, Qt::CaseSensitivity)));
        connect(mFindDialog, SIGNAL(findPrevious(const QString &, Qt::CaseSensitivity)),
                mSpreadsheet, SLOT(findPrevious(const QString &, Qt::CaseSensitivity)));
    }
    mFindDialog->show();
    mFindDialog->raise();
    mFindDialog->activateWindow();
}

void mainWindow::writeSettings(){
    QSettings settings("Huang TaiChi Inc. ", "Spreadsheet");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalcAction->isChecked()); // fixme later?
}

void mainWindow::readSettings(){
    QSettings settings("Huang TaiChi Inc. ", "Spreadsheet");
    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();
    showGridAction->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecal", true).toBool();
    autoRecalcAction->setChecked(autoRecalc);
}

void mainWindow::sort(){
#if 0
    sortDialog dialog(this);
    QTableWidgetSelectionRange range = mSpreadsheet->selectRange();
    dialog.setColumnRange('A' + range.leftColumn(),
                          'A' + range.rightColumn());
    if(dialog.exec()){
        SpreadsheetCompare compare;
        compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] = dialog.secondaryColumnCombo->currentIndex()-1;
        compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex()-1;
        compare.ascending[0] = (0 == dialog.primaryColumnCombo->currentIndex());
        compare.ascending[1] = (0 == dialog.secondaryColumnCombo->currentIndex());
        compare.ascending[2] = (0 == dialog.tertiaryColumnCombo->currentIndex());
        mSpreadsheet->sort(compare);
    }
#endif
    sortDialog dialog(this);
    dialog.setSpreadsheet(mSpreadsheet);
    dialog.exec();
}

void mainWindow::about(){
    QMessageBox::about(this, tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.1</h2>"
                            "<p>Coprirght &copy; 2015 Hwang TaiChi Inc."
                            "<p>Spreadsheet is a small application that "
                            "demonstrate QAction, QMainWindow, QMenubar, "
                            "QStatusBar, QTableWidget, QToolBar, and many other"
                            "Qt classes"));
}

void mainWindow::goToCell(){
    gotoCellDialog dialog(this);
    if(dialog.exec()){
        QString str = dialog.lineEdit->text().toUpper();
        mSpreadsheet->setCurrentCell(str.mid(1).toInt() - 1,
                                     str[0].unicode() - 'A');
    }
}
