#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//class QAction;

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

private:
    Ui::MainWindow *ui;
    static constexpr int RECENT_FILES_AMOUNT = 5;
    QAction* recentFilesActions[RECENT_FILES_AMOUNT];
};
#endif // MAINWINDOW_H
