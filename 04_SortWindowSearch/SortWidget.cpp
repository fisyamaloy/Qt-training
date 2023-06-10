#include "SortWidget.h"
#include <QDialog>

SortWidget::SortWidget(QWidget *parent)
    : QDialog(parent)
{
    init();
    fillGroupBoxes();
}

SortWidget::~SortWidget()
{

}

void SortWidget::onMoreButtonClicked(bool isToggled)
{
    for(int i = 1; i < GROUP_BOX_AMOUNT; ++i)
    {
        groupBoxes[i].setVisible(isToggled);
    }

    if (!isToggled)
    {
        adjustSize();
    }
}

void SortWidget::setColumnRange(QChar first, QChar last)
{
    comboBoxes[0][0].clear();
    for (int i = 1; i < GROUP_BOX_AMOUNT; ++i)
    {
        comboBoxes[i][0].clear();
        comboBoxes[i][0].addItem(tr("None"));
    }

    while(first != last)
    {
        for (int i = 0; i < GROUP_BOX_AMOUNT; ++i)
        {
            comboBoxes[i][0].addItem(QString(first));
        }
        first = first.unicode() + 1;
    }
}

void SortWidget::init()
{
    groupBoxes = new QGroupBox[GROUP_BOX_AMOUNT];
    groupBoxLayouts = new QVBoxLayout[GROUP_BOX_AMOUNT];

    labels = new QLabel*[GROUP_BOX_AMOUNT];
    for(int i = 0; i < GROUP_BOX_AMOUNT; ++i)
    {
        labels[i] = new QLabel[2];
    }

    comboBoxes = new QComboBox*[GROUP_BOX_AMOUNT];
    for(int i = 0; i < GROUP_BOX_AMOUNT; ++i)
    {
        comboBoxes[i] = new QComboBox[2];
    }

    for(int i = 0; i < GROUP_BOX_AMOUNT; ++i)
    {
        groupBoxSpacers.append(new QSpacerItem(40, 0));
    }

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    moreButton = new QPushButton("More");
    moreButton->setCheckable(true);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(moreButton, &QPushButton::toggled, this, &SortWidget::onMoreButtonClicked);
}

void SortWidget::fillGroupBoxes()
{
    setColumnRange('A', 'Z');

    groupBoxes[0].setTitle("Primary key");
    groupBoxes[1].setTitle("Secondary key");
    groupBoxes[2].setTitle("Theritory key");

    auto mainLayout = new QVBoxLayout;

    for (int i = 0; i < GROUP_BOX_AMOUNT; ++i)
    {
        labels[i][0].setText(tr("Column"));
        labels[i][1].setText(tr("Order"));

        comboBoxes[i][0].addItem(tr("None"));
        comboBoxes[i][1].addItem(tr("Ascending"));
        comboBoxes[i][1].addItem(tr("Descending"));

        auto labelsLayout = new QVBoxLayout;
        labelsLayout->addWidget(&labels[i][0]);
        labelsLayout->addWidget(&labels[i][1]);

        auto comboboxWithSpacerlayout = new QHBoxLayout;
        comboboxWithSpacerlayout->addWidget(&comboBoxes[i][0]);
        comboboxWithSpacerlayout->addItem(groupBoxSpacers[i]);

        auto comboBoxesLayout = new QVBoxLayout;
        comboBoxesLayout->addLayout(comboboxWithSpacerlayout);
        comboBoxesLayout->addWidget(&comboBoxes[i][1]);

        auto mainGroupBoxLayout = new QHBoxLayout;
        mainGroupBoxLayout->addLayout(labelsLayout);
        mainGroupBoxLayout->addLayout(comboBoxesLayout);

        groupBoxes[i].setLayout(mainGroupBoxLayout);

        if (i == 0)
        {
            auto buttonsLayout = new QVBoxLayout;
            buttonsLayout->addWidget(okButton);
            buttonsLayout->addWidget(cancelButton);
            buttonsLayout->addWidget(moreButton);

            auto groupBoxWithButtonsLayout = new QHBoxLayout;
            groupBoxWithButtonsLayout->addWidget(&groupBoxes[i]);
            groupBoxWithButtonsLayout->addLayout(buttonsLayout);
            mainLayout->addLayout(groupBoxWithButtonsLayout);
        }
        else
        {
            mainLayout->addWidget(&groupBoxes[i]);
        }
    }

    for(int i = 1; i < GROUP_BOX_AMOUNT; ++i)
    {
        groupBoxes[i].setVisible(false);
    }

    setLayout(mainLayout);
}
