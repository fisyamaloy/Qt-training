#include "FindDialog.h"
#include <QtWidgets>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Find");

    findWhatLabel = new QLabel(tr("Find &what:"));
    input = new QLineEdit;
    matchCaseCheckBox = new QCheckBox(tr("&Match case"));
    backwardCheckBox = new QCheckBox(tr("&Search backward"));
    findButton = new QPushButton(tr("&Find"));
    closeButton = new QPushButton(tr("&Close"));

    findWhatLabel->setBuddy(input);

    findButton->setDefault(true);
    findButton->setEnabled(false);

    connect(input, SIGNAL(textChanged(QString)), this, SLOT(enableFindButton(QString)));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findButtonClickHandler()));

    auto inputLayout = new QHBoxLayout;
    inputLayout->addWidget(findWhatLabel);
    inputLayout->addWidget(input);

    auto checkBoxesLayout = new QVBoxLayout;
    checkBoxesLayout->addWidget(matchCaseCheckBox);
    checkBoxesLayout->addWidget(backwardCheckBox);

    auto concatInputAndCheckBoxesLayot = new QVBoxLayout;
    concatInputAndCheckBoxesLayot->addLayout(inputLayout);
    concatInputAndCheckBoxesLayot->addLayout(checkBoxesLayout);

    auto buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(findButton);
    buttonsLayout->addWidget(closeButton);

    auto finalLayout = new QHBoxLayout;
    finalLayout->addLayout(concatInputAndCheckBoxesLayot);
    finalLayout->addLayout(buttonsLayout);
    finalLayout->addStretch();

    setLayout(finalLayout);
}

void FindDialog::enableFindButton(const QString& str)
{
    findButton->setEnabled(str.size() > 0);
}

void FindDialog::findButtonClickHandler()
{
    auto text = input->text();

    Qt::CaseSensitivity cs = matchCaseCheckBox->isChecked() ? Qt::CaseSensitive: Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked())
    {
        emit findPrev(text, cs);
    }
    else
    {
        emit findNext(text, cs);
    }
}

