#include "SortWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortWidget w;
    w.show();
    return a.exec();
}
