#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableWidget);

    ui->tableWidget->setRowCount(1000);
    constexpr int LETTERS_AMOUNT = 26;
    ui->tableWidget->setColumnCount(LETTERS_AMOUNT);

    QStringList alphabet;
    int start = 'A';
    for (int i = start; i < start + LETTERS_AMOUNT; ++i)
    {
        alphabet.push_back(QString(QChar(i)));
    }
    ui->tableWidget->setHorizontalHeaderLabels(alphabet);
    ui->tableWidget->addAction(ui->actioncut);
    ui->tableWidget->addAction(ui->actionCopy);
    ui->tableWidget->addAction(ui->actionPaste);

    auto menuBarActions = ui->menubar->actions();
    auto fileSubMenu = menuBarActions.at(0)->menu();
    auto fileActions = fileSubMenu->actions();
    for (int i = 0; i < RECENT_FILES_AMOUNT; ++i)
    {
        recentFilesActions[i] = new QAction(this);
        recentFilesActions[i]->setVisible(false);
        connect(recentFilesActions[i], &QAction::triggered, this, &MainWindow::onOpenRecentFiles);
        fileSubMenu->insertAction(fileActions.at(fileActions.size() - 1), recentFilesActions[i]);
    }
    fileSubMenu->insertSeparator(fileActions.at(fileActions.size() - 1));

    ui->actionShow_grid->setChecked(ui->tableWidget->showGrid());

    setWindowIcon(QIcon(":/Icons/Spreadsheet.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenRecentFiles()
{

}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionShow_grid_toggled(bool arg1)
{
    ui->tableWidget->setShowGrid(arg1);
}
