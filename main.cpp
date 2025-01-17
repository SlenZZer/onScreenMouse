#include <QCoreApplication>
#include "appManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    appManager appMger;
    appMger.start(); // Start the key appManager in a separate thread

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
        appMger.requestInterruption(); // Gracefully stop the appManager
        appMger.wait();
    });

    QObject::connect(&appMger, &appManager::killRequested, [&](){
       DEBUG_MSG("got kill msg !!");
//       appMger.requestInterruption(); // Gracefully stop the appManager
//       appMger.wait();

       return a.exec();
    });

    return a.exec();
}
