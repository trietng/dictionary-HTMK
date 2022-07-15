#include "dictionary.hpp"
#include "mainwindow.h"

#include <QApplication>
#include "debug.h"
int main(int argc, char *argv[])
{
    MainProgram p;
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.setProgram(&p);
    w.show();
    return a.exec();
}
