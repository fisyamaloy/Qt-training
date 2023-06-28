#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIcon>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>
#include "FindDialog.h"
#include "GoToCellDialog.h"
#include "SortDialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableWidget);

    ui->tableWidget->setRowCount(1000);
    constexpr int LETTERS_AMOUNT = 26;
    ui->tableWidget->setColumnCount(LETTERS_AMOUNT);

    QStringList alphabet;
    int start = 'A';
    for (int i = start; i < start + LETTERS_AMOUNT; ++i)
    {
        alphabet.push_back(QString(QChar(i)));
    }
    ui->tableWidget->setHorizontalHeaderLabels(alphabet);

    ui->tableWidget->addAction(ui->actioncut);
    ui->tableWidget->addAction(ui->actionCopy);
    ui->tableWidget->addAction(ui->actionPaste);

    auto menuBarActions = ui->menubar->actions();
    auto fileSubMenu = menuBarActions.at(0)->menu();
    auto fileActions = fileSubMenu->actions();
    for (int i = 0; i < MAX_RECENT_FILES_AMOUNT; ++i)
    {
        recentFilesActions[i] = new QAction(this);
        recentFilesActions[i]->setVisible(false);
        connect(recentFilesActions[i], &QAction::triggered, this, &MainWindow::onOpenRecentFiles);
        fileSubMenu->insertAction(fileActions.at(fileActions.size() - 1), recentFilesActions[i]);
    }
    fileSubMenu->insertSeparator(fileActions.at(fileActions.size() - 1));

    ui->actionShow_grid->setChecked(ui->tableWidget->showGrid());

    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);
    statusBar()->addWidget(locationLabel, 0);
    statusBar()->addWidget(formulaLabel, 1);

    findDlg = new FindDialog(this);
    connect(findDlg, &FindDialog::findNext, this, &MainWindow::onFindNext);
    connect(findDlg, &FindDialog::findPrev, this, &MainWindow::onFindPrev);

    setCurrentFile("");
    setWindowIcon(QIcon(":/Icons/Spreadsheet.jpg"));

    readSettings();
    updateContextMenu();
}

void MainWindow::onFindNext(const QString& str, const Qt::CaseSensitivity cs)
{
    int CURRENT_ROW = ui->tableWidget->currentRow();
    int CURRENT_COLUMN = ui->tableWidget->currentColumn() + 1;

    for (int i = CURRENT_ROW; i < ui->tableWidget->rowCount(); ++i)
    {
        for (int j = CURRENT_COLUMN; j < ui->tableWidget->columnCount(); ++j)
        {
            auto item = ui->tableWidget->item(i, j);
            if (item && item->text().contains(str, cs))
            {
                ui->tableWidget->clearSelection();
                ui->tableWidget->setCurrentCell(i, j);
                activateWindow();
                return;
            }
        }
    }

    QApplication::beep();
}

void MainWindow::onFindPrev(const QString& str, const Qt::CaseSensitivity cs)
{
    const int CURRENT_ROW = ui->tableWidget->currentRow();
    const int CURRENT_COLUMN = ui->tableWidget->currentColumn() - 1;

    for (int i = CURRENT_ROW; i >= 0; --i)
    {
        for (int j = CURRENT_COLUMN; j >= 0; --j)
        {
            auto item = ui->tableWidget->item(i, j);
            if (item && item->text().contains(str, cs))
            {
                ui->tableWidget->clearSelection();
                ui->tableWidget->setCurrentCell(i, j);
                activateWindow();
                return;
            }
        }
    }

    QApplication::beep();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenRecentFiles()
{
    if (okToContinue())
    {
        auto action = qobject_cast<QAction*>(sender());
        if (action)
        {
            const auto FILE_NAME = action->data().toString();
            if (loadFile(FILE_NAME))
            {
                setCurrentFile(FILE_NAME);
            }
        }
    }
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionShow_grid_toggled(bool arg1)
{
    ui->tableWidget->setShowGrid(arg1);
}

void MainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    updateStatusBar(currentRow, currentColumn);
    updateContextMenu();
}

void MainWindow::updateStatusBar(const int row, const int column)
{
    if (row == -1 || column == -1)
        return;

    auto horHeaderItem = ui->tableWidget->horizontalHeaderItem(column);
    const QString COLUMN_HEADER = (horHeaderItem != nullptr) ? horHeaderItem->text() : "";

    locationLabel->setText(COLUMN_HEADER + QString::number(row + 1));
}

void MainWindow::on_actionNew_triggered()
{
    if (okToContinue())
    {
        clearTableWidget();
        setCurrentFile("");
    }
}

bool MainWindow::okToContinue()
{
    if (isWindowModified())
    {
        int res = QMessageBox::warning(this, tr("Spreadsheet"), tr("The document has been modified. \n Do you want to save your changes?"),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (res == QMessageBox::Yes)
            return save();
        else if (res == QMessageBox::Cancel)
            return false;

    }
    return true;
}

bool MainWindow::save()
{
    if (currentFile.isEmpty())
        return saveAs();
    else
        return saveFile(currentFile);
}

bool MainWindow::saveAs()
{
    const QString FILE_NAME = QFileDialog::getSaveFileName(this, tr("Save Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));
    if (FILE_NAME.isEmpty())
        return false;

    return saveFile(FILE_NAME);
}

bool MainWindow::writeFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);

    const int ROW_AMOUNT = ui->tableWidget->rowCount();
    const int COLUMN_AMOUNT = ui->tableWidget->columnCount();
    for (int row = 0; row < ROW_AMOUNT; ++row) {
        for (int col = 0; col < COLUMN_AMOUNT; ++col) {
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            stream << (item ? item->text() : "") << "\t";
        }
        stream << "\n";
    }

    file.close();
    return true;
}

bool MainWindow::saveFile(const QString& fileName)
{
    if (!writeFile(fileName))
    {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString& filePath)
{
    currentFile = filePath;
    setWindowModified(false);

    QString showName = "Untitled";
    if (!currentFile.isEmpty())
    {
        showName = strippedName(currentFile);
        recentFiles.removeAll(currentFile);
        recentFiles.prepend(currentFile);
        updateRecentFilesActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(showName).arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString& filePath)
{
    QFileInfo file(filePath);
    return file.fileName();
}

void MainWindow::updateRecentFilesActions()
{
    QMutableStringListIterator it(recentFiles);
    while (it.hasNext())
    {
        if (!QFile::exists(it.next()))
        {
            it.remove();
        }
    }

    for (int i = 0; i < MAX_RECENT_FILES_AMOUNT; ++i)
    {
        if (i < recentFiles.count())
        {
            const QString TEXT = tr("&%1 %2").arg(i + 1).arg(strippedName(recentFiles[i]));
            recentFilesActions[i]->setText(TEXT);
            recentFilesActions[i]->setData(recentFiles[i]);
            recentFilesActions[i]->setVisible(true);
        }
        else
        {
            recentFilesActions[i]->setVisible(false);
        }
    }
}

void MainWindow::clearTableWidget()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j)
        {
            auto item = ui->tableWidget->takeItem(i, j);
            if (item)
            {
                delete item;
            }
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if (okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));
        if (!fileName.isEmpty())
        {
            if (loadFile(fileName))
            {
                setCurrentFile(fileName);
            }
        }
    }
}

bool MainWindow::loadFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream stream(&file);
    int row = 0;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList values = line.split("\t");

        int column = 0;
        for (const QString& value : values) {
            QTableWidgetItem* item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(row, column, item);
            ++column;
        }

        ++row;
    }

    file.close();
    return true;
}


void MainWindow::on_actionSave_triggered()
{
    save();
}


void MainWindow::on_actionSave_As_triggered()
{
    saveAs();
}


void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    setWindowModified(true);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (okToContinue())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
        writeSettings();
    }
}

void MainWindow::writeSettings()
{
    QSettings settings("SOFTEBY", "Spreadsheet");

    settings.setValue("geometry", geometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", ui->actionShow_grid->isChecked());
    settings.setValue("autoRecalc", ui->actionAutoRecalculate->isChecked());
}

void MainWindow::readSettings()
{
    QSettings settings("SOFTEBY", "Spreadsheet");

    const QRect geom = settings.value("geometry", QRect(100, 100, 800, 600)).toRect();
    setGeometry(geom);
    recentFiles = settings.value("recentFiles").toStringList();
    ui->actionShow_grid->setChecked(settings.value("showGrid", true).toBool());
    ui->actionAutoRecalculate->setChecked(settings.value("autoRecalc", false).toBool());
}

void MainWindow::on_actionFind_triggered()
{
    findDlg->show();
    findDlg->raise();
    findDlg->activateWindow();
}


void MainWindow::on_actionGo_To_Cell_triggered()
{
    GoToCellDialog goToCellDlg(this);
    int res = goToCellDlg.exec();
    if (res == SortDialog::Accepted)
    {
        const auto cellText = goToCellDlg.getInputCellLocation().toUpper();
        ui->tableWidget->setCurrentCell(cellText.midRef(1).toInt() - 1, cellText[0].unicode() - 'A');
    }
}


// TODO: finish sort
void MainWindow::on_actionSort_triggered()
{
//    SortDialog sortDlg(this);

//    QTableWidgetSelectionRange range = ui->tableWidget->selectedRanges().at(0);
//    int res = sortDlg.exec();
//    if (res == SortDialog::Accepted)
//    {
//    }
}


void MainWindow::on_actionDelete_triggered()
{
    auto item = ui->tableWidget->currentItem();
    if (item)
    {
        item->setText("");
    }
}


void MainWindow::on_actioncut_triggered()
{
    auto item = ui->tableWidget->currentItem();
    if (item)
    {
        pasteBuf.setBuffer(item->text(), PasteQString::Operation::CUT);
        item->setText("");

        updateContextMenu();
    }
}


void MainWindow::on_actionPaste_triggered()
{
    auto item = ui->tableWidget->currentItem();
    const QString buffer = pasteBuf.getBuffer();
    if (!buffer.isEmpty())
    {
        if (item)
        {
            item->setText(buffer);
        }
        else
        {
            item = new QTableWidgetItem(pasteBuf.getBuffer());
            ui->tableWidget->setItem(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn(), item);
        }

        updateContextMenu();
    }
}


void MainWindow::on_actionCopy_triggered()
{
    auto item = ui->tableWidget->currentItem();
    pasteBuf.setBuffer(item ? item->text() : "", PasteQString::Operation::COPY);
    updateContextMenu();
}


void MainWindow::updateContextMenu()
{
    auto item = ui->tableWidget->currentItem();
    const bool isCurItemTextisEmpty = (item ? item->text().isEmpty() : true);

    ui->actionCopy->setDisabled(isCurItemTextisEmpty);
    ui->actioncut->setDisabled(isCurItemTextisEmpty);

    const bool isPasteBufEmpty = pasteBuf.lookAtBuffer().isEmpty();
    ui->actionPaste->setDisabled(isPasteBufEmpty);
}
