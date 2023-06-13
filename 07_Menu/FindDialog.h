#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = nullptr);

signals:
    void findNext(const QString& str, const Qt::CaseSensitivity cs);
    void findPrev(const QString& str, const Qt::CaseSensitivity cs);

private slots:
    void findButtonClickHandler();
    void enableFindButton(const QString& str);

private:
    QLabel* findWhatLabel;
    QLineEdit* input;
    QCheckBox* matchCaseCheckBox;
    QCheckBox* backwardCheckBox;
    QPushButton* findButton;
    QPushButton* closeButton;
};
#endif // DIALOG_H
