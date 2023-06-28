#include "GoToCellDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QRegExp>
#include <QRegExpValidator>

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    cellLocationLabel = new QLabel(tr("Go to cell:"));

    input = new QLineEdit;
    input->setMinimumWidth(250);
    QRegExp regExpr("[a-zA-Z][1-9][0-9]{0,2}");
    input->setValidator(new QRegExpValidator(regExpr, this));

    spacer = new QSpacerItem(100, 0);
    okButton = new QPushButton(tr("OK"));
    okButton->setMinimumHeight(35);
    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setMinimumHeight(35);

    okButton->setEnabled(false);
    okButton->setDefault(true);

    auto topLayout = new QHBoxLayout;
    topLayout->addWidget(cellLocationLabel);
    topLayout->addWidget(input);

    auto bottomLayout = new QHBoxLayout;
    bottomLayout->addItem(spacer);
    bottomLayout->addWidget(okButton);
    bottomLayout->addWidget(cancelButton);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(input, &QLineEdit::textChanged, this, &GoToCellDialog::onInputTextChanged);
}

void GoToCellDialog::onInputTextChanged()
{
    okButton->setEnabled(input->hasAcceptableInput());
}

QString GoToCellDialog::getInputCellLocation() const
{
    return input->text();
}
