#include "mainwindow.h"
#include <QApplication>
#include <QRegExp>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Alert A = Alert(""," ",0);
    MainWindow w;
    w.show();

    return a.exec();
}
