#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "A" << "B" << "C" << "D");
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I" << "J");

    int s = 1;
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j)
        {
            auto item = new QTableWidgetItem(QString::number(s));
            ui->tableWidget->setItem(i, j, item);
            item->setBackground(Qt::gray);
            ++s;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << ui->tableWidget->currentItem()->text() << '\n';

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actionTimer);
    timer->start(1000);
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    ui->tableWidget->item(row, column)->setBackground(Qt::white);
    qDebug() << ui->tableWidget->item(row, column)->text();
}

void MainWindow::actionTimer()
{
    srand(time(NULL));
    int i = rand() % ui->tableWidget->rowCount();
    int j = rand() % ui->tableWidget->columnCount();
    auto item = new QTableWidgetItem("&!#*#@");
    item->setBackground(Qt::blue);
    item->setTextColor(Qt::white);
    ui->tableWidget->setItem(i, j, item);
}
