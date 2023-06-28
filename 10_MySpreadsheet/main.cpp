#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <thread>
#include <chrono>

void loadModules()
{
    //std::this_thread::sleep_for(std::chrono::seconds(2));
}

void establishConnections()
{
    //std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/Icons/Splash.jpg"));
    splash->show();

    Qt::Alignment centerBottom = Qt::AlignCenter | Qt::AlignBottom;
    splash->showMessage(QObject::tr("Setting up the main window..."), centerBottom, Qt::white);
    MainWindow w;

    splash->showMessage(QObject::tr("Loading modules..."), centerBottom, Qt::white);
    loadModules();

    splash->showMessage(QObject::tr("Establishing connections..."), centerBottom, Qt::white);
    establishConnections();
    w.show();

    splash->finish(&w);
    delete splash;
    return a.exec();
}
