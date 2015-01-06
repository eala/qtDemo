#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QLabel;
class findDialog;
class spreadsheet;

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    mainWindow();
    ~mainWindow();

signals:

private slots:
    void newFile();
    void open();
    bool save();
    void saveAs();
    void openRecentFile();

    void find();
    void goToCell();
    void sort();
    void about();

    void updateStatusBar();
    void spreadsheetModified();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

protected:
    void closeEvent(QCloseEvent *event);

private:
    spreadsheet *mSpreadsheet;
    findDialog *mFindDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    QStringList recentFiles;
    QString curFile;

    enum{ MaxRecentFiles = 5};
    QAction *newAction;
    QAction *openAction;
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    // edit menu
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;

    // sub select menu
    QAction *selectRowAction;
    QAction *selectColumnAction;
    QAction *selectAllAction;

    QAction *findAction;
    QAction *gotoCellAction;

    // tool menu
    QAction *recalculateAction;
    QAction *sortAction;
    QAction *showGridAction;

    // about menu
    QAction *aboutAction;
    QAction *aboutQtAction;


    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;
    QMenu *selectSubMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
};

#endif // MAINWINDOW_H
