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
#if MDI
    void closeAllWindows();
#endif

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
    QString curFile;

    findDialog *mFindDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;


    enum{ MaxRecentFiles = 5};
#if MDI
    static QStringList recentFiles; // all windows share the same recent files list
    static QAction *recentFileActions[MaxRecentFiles];
#else
    QStringList recentFiles;
    QAction *recentFileActions[MaxRecentFiles];
#endif

    // file menu
    QAction *newAction;
    QAction *openAction;
    QAction *separatorAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *closeAction;
#if MDI
    QAction *exitAction;
#endif

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
