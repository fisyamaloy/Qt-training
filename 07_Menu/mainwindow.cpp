#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QAction>
#include <QIcon>
#include "FindDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu* file = menuBar()->addMenu("File");

    QAction* newFile = new QAction(tr("New"), this);
    QAction* openFile = new QAction(tr("Open"), this);
    QAction* saveFile = new QAction(tr("Save"), this);

    newFile->setShortcut(QKeySequence::New);
    openFile->setShortcut(QKeySequence::Open);
    saveFile->setShortcut(tr("Ctrl+S"));

    file->addAction(newFile);
    file->addAction(openFile);
    file->addAction(saveFile);

    connect(newFile, &QAction::triggered, this, &MainWindow::onNewTriggered);
    connect(openFile, &QAction::triggered, this, &MainWindow::onOpenTriggered);
    connect(saveFile, &QAction::triggered, this, &MainWindow::onSaveTriggered);

    QMenu* editFile = menuBar()->addMenu("Edit");
    QAction* deleteAction = new QAction(tr("Delete"), this);
    editFile->addAction(deleteAction);

    QMenu* select = new QMenu("Select", editFile);
    QAction* rowAction = new QAction(tr("Row"), this);
    QAction* columnAction = new QAction(tr("Column"), this);
    select->addAction(rowAction);
    select->addAction(columnAction);

    newFile->setIcon(QIcon(":/Icons/newFile.jpeg"));
    openFile->setIcon(QIcon(":/Icons/openFile.png"));
    saveFile->setIcon(QIcon(":/Icons/saveFile.jpg"));

    editFile->addMenu(select);

    QMenu* test = menuBar()->addMenu("Test");
    auto findDialog = new QAction(tr("Find dialog"), this);
    test->addAction(findDialog);

    connect(findDialog, &QAction::triggered, this, &MainWindow::onFindDialogTriggered);

}

void MainWindow::onNewTriggered()
{
    QMessageBox box;
    box.setText("New file");
    box.exec();
}

void MainWindow::onOpenTriggered()
{
    QMessageBox box;
    box.setText("Open file");
    box.exec();
}

void MainWindow::onSaveTriggered()
{
    QMessageBox box;
    box.setText("Save file");
    box.exec();
}

void MainWindow::onFindDialogTriggered()
{
    FindDialog* findDialog = new FindDialog;
    findDialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
