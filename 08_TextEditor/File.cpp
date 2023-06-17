#include "File.h"
#include "ui_File.h"
#include <QPushButton>

File::File(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &File::onOKClicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &QDialog::close);
}

void File::onOKClicked()
{
    emit filePath(ui->pathInput->text());
    close();
}

File::~File()
{
    delete ui;
}
