#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QSpacerItem;

class GoToCellDialog : public QDialog
{
    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = nullptr);

    QString getInputCellLocation() const;

private slots:
    void onInputTextChanged();

private:
    QLabel* cellLocationLabel;
    QLineEdit* input;

    QSpacerItem* spacer;
    QPushButton* okButton;
    QPushButton* cancelButton;

};
#endif // GOTOCELLDIALOG_H
