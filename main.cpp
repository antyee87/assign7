#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <QScreen>

#include "gameprocess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    GameProcess game(&w);
    w.setGameProcess(&game);

    return a.exec();
}
