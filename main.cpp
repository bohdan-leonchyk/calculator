#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LeonchykCalculator w;
    w.show();

    return a.exec();
}
