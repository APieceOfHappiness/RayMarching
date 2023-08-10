
#include "mainwindow.h"

#include <QApplication>
#include <QLabel>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel *label = new QLabel("Hello");
    MainWindow w;
    w.show();
    delete label;
    return a.exec();
}
