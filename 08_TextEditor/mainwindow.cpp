#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "File.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->clear();
    ui->listWidget->clear();
    for(int i = 0; i < 10; ++i)
    {
        ui->comboBox->addItem(QString::number(i));
        ui->listWidget->addItem(QString::number(i));
    }
    ui->listWidget->addItem(QString::number(100));
    ui->statusbar->showMessage("OK");

    ui->treeWidget->clear();
    QTreeWidgetItem* item = new QTreeWidgetItem;
    item->setText(0, "first");
    item->setText(1, "second");
    item->setText(2, "thith");
    item->setText(3, "fourth");
    item->setText(4, "fifth");
    ui->treeWidget->setColumnCount(5);
    ui->treeWidget->addTopLevelItem(item);

    QTreeWidgetItem* child1 = new QTreeWidgetItem;
    child1->setText(0, "child1");

    QTreeWidgetItem* child1_1 = new QTreeWidgetItem;
    child1_1->setText(0, "child1_1");
    child1->addChild(child1_1);

    item->addChild(child1);

    QTreeWidgetItem* child2 = new QTreeWidgetItem;
    child2->setText(0, "child2");
    item->addChild(child2);

    ui->treeWidget->setColumnWidth(0, 200);

    QTreeWidgetItem* itemLvl2 = new QTreeWidgetItem;
    itemLvl2->setText(0, "first_lvl_2");
    ui->treeWidget->addTopLevelItem(itemLvl2);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    File* file = new File(this);
    qDebug() << "on Open triggered " << QDate::currentDate() << ' ' << QTime::currentTime() << '\n';
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

void MainWindow::on_actionFileDirectory_triggered()
{
    File* file = new File(this);
    connect(file, &File::filePath, this, &MainWindow::printDirectrory);
    file->show();
}

void MainWindow::printDirectrory(const QString& filePath)
{
    ui->textEdit->setText(printDirectroryRecursive(filePath, 0));
}


QString MainWindow::printDirectroryRecursive(const QString& filePath, int lvl)
{
    QDir dir(filePath);
    QString buffer;
    QString spaces;
    for(int i = 0; i < lvl; ++i)
    {
        spaces += "       ";
    }

    for(int i = 2; i < dir.entryInfoList().size(); ++i)
    {
        const auto& fileInfo = dir.entryInfoList().at(i);
        buffer += spaces + fileInfo.absoluteFilePath() + "\n";
        if (fileInfo.isDir())
        {
            buffer += printDirectroryRecursive(fileInfo.absoluteFilePath(), lvl + 1);
        }
    }

    return buffer;
}

//void MainWindow::fileDirectory(const QString& filePath)
//{
//    QDir dir(filePath);
//    QString buffer;
//    for (const QFileInfo& fileInfo : dir.entryInfoList())
//    {
//        buffer += fileInfo.absoluteFilePath() + '\n';
//    }

//    ui->textEdit->setText(buffer);
//}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::warning(this, "ComboBox button clicked", ui->comboBox->currentText());
}


void MainWindow::on_pushButton_2_clicked()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    item->setBackground(Qt::red);
    QMessageBox::information(this, "ListWidget button clicked", item->text());
}

