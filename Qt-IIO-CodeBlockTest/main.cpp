#include "mainwindow.h"
#include <QApplication>

#include <Infrastructure/infrastructure.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qt_iio_cc::infrastructure::Infrastructure::getInstance().initialize();

    MainWindow w;
    w.show();

    return a.exec();
}
