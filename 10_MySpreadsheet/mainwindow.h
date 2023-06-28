#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PasteQString.h"

class QTableWidgetItem;
class QLabel;
class FindDialog;
class SortDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenRecentFiles();

    void on_actionAbout_Qt_triggered();

    void on_actionExit_triggered();

    void on_actionShow_grid_toggled(bool arg1);

    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void closeEvent(QCloseEvent* event);

    void onFindNext(const QString& str, const Qt::CaseSensitivity cs);
    void onFindPrev(const QString& str, const Qt::CaseSensitivity cs);

    void on_actionFind_triggered();

    void on_actionGo_To_Cell_triggered();

    void on_actionSort_triggered();

    void on_actionDelete_triggered();

    void on_actioncut_triggered();

    void on_actionPaste_triggered();

    void on_actionCopy_triggered();

private:
    bool okToContinue();

    void updateStatusBar(const int row, const int column);

    void clearTableWidget();

    void setCurrentFile(const QString& filePath);

    bool save();
    bool saveAs();
    bool saveFile(const QString& fileName);

    bool writeFile(const QString& fileName);

    bool loadFile(const QString& fileName);

    QString strippedName(const QString& filePath);

    void updateRecentFilesActions();

    void writeSettings();
    void readSettings();

    void updateContextMenu();

private:
    Ui::MainWindow *ui;
    FindDialog* findDlg;

    static constexpr int MAX_RECENT_FILES_AMOUNT = 5;
    QAction* recentFilesActions[MAX_RECENT_FILES_AMOUNT];
    QStringList recentFiles;

    QLabel* locationLabel;
    QLabel* formulaLabel;

    QString currentFile;
    PasteQString pasteBuf;

};
#endif // MAINWINDOW_H
