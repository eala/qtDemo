#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// multiple document interface
#define MDI 0

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
    bool saveAs();
    void openRecentFile();
    void closeAllWindows();

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
    void createConnections();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    void displayStatusBar(const QString &str);
    QString strippedName(const QString &fullFileName);


protected:
    void closeEvent(QCloseEvent *event);

private:
    spreadsheet *mSpreadsheet;
    findDialog *mFindDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    static QStringList recentFiles; // all windows share the same recent files list
    QString curFile;

    enum{ MaxRecentFiles = 5};
    QAction *newAction;
    QAction *openAction;
    static QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *closeAction;
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
    QAction *autoRecalcAction;
    QAction *sortAction;
    QAction *showGridAction;

    // about menu
    QAction *myAboutAction;
    QAction *myAboutQtAction;


    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *myHelpMenu;
    QMenu *selectSubMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
};

#endif // MAINWINDOW_H
