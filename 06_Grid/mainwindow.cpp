#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto grid = new QGridLayout;
    grid->addWidget(ui->pushButton, 0, 0);
    grid->addWidget(ui->toolButton, 1, 1);
    grid->addWidget(ui->radioButton, 2, 2);

    auto widget = new QWidget;
    widget->setLayout(grid);

    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
