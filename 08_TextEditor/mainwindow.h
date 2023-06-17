#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString printDirectroryRecursive(const QString& filePath, int lvl);

private slots:
    void openFile(const QString& filePath);

    void saveFile(const QString& filePath);

    //void fileDirectory(const QString& filePath);
    void printDirectrory(const QString& filePath);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionFileDirectory_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
