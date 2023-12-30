#include "mainwindow.h"
#include "connection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(!createConnection()) return 0;
    w.show();
    return a.exec();
}
