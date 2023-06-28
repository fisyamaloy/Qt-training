#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QVector>
#include <QPushButton>
#include <QDialog>

class SortDialog : public QDialog
{
    Q_OBJECT

public:
    SortDialog(QWidget *parent = nullptr);
    ~SortDialog();

    void init();

private:
    void fillGroupBoxes();
    void setColumnRange(QChar first, QChar last);

private slots:
    void onMoreButtonClicked(bool isToggled);

private:
    static constexpr int GROUP_BOX_AMOUNT = 3;
    QGroupBox* groupBoxes;
    QVBoxLayout* groupBoxLayouts;
    QLabel** labels;
    QComboBox** comboBoxes;
    QVector<QSpacerItem*> groupBoxSpacers;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QPushButton* moreButton;
};
#endif // WIDGET_H
