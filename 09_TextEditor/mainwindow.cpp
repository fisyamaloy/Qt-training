#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "File.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    ui->statusbar->showMessage("OK");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    File* file = new File(this);
    connect(file, &File::filePath, this, &MainWindow::openFile);
    file->show();
}


void MainWindow::on_actionSave_triggered()
{
    File* file = new File(this);
    connect(file, &File::filePath, this, &MainWindow::saveFile);
    file->show();
}

void MainWindow::openFile(const QString& filePath)
{
    QFile qFile(filePath);
    qFile.open(QFile::ReadOnly | QFile::Text);
    if (!qFile.isOpen())
    {
        QMessageBox::information(this, "Error", "Error: openFile");
        ui->statusbar->showMessage("Error: openFile");
        return;
    }

    QTextStream stream(&qFile);
    const QString buffer = stream.readAll();
    ui->textEdit->setText(buffer);
    ui->statusbar->showMessage("Open file");
    qFile.flush();

    qFile.close();
}

void MainWindow::saveFile(const QString& filePath)
{
    QFile qFile(filePath);
    qFile.open(QFile::WriteOnly | QFile::Text);
    if (!qFile.isOpen())
    {
        QMessageBox::information(this, "Error", "Error: writeFile");
        ui->statusbar->showMessage("Error: writeFile");
        return;
    }

    QTextStream stream(&qFile);
    stream << ui->textEdit->toPlainText();
    ui->statusbar->showMessage("Write file");
    qFile.flush();

    qFile.close();
}
