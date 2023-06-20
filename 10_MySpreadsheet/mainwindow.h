#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


//class QAction;
class QLabel;

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

    Ui::MainWindow *ui;

    static constexpr int RECENT_FILES_AMOUNT = 5;
    QAction* recentFilesActions[RECENT_FILES_AMOUNT];
    QStringList recentFiles;

    QLabel* locationLabel;
    QLabel* formulaLabel;

    QString currentFile;
};
#endif // MAINWINDOW_H
