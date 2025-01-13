#include "appManager.h"

appManager::~appManager()
{
    requestInterruption(); wait();
}

void appManager::run()
{
    Display *display = XOpenDisplay(nullptr);
    if (!display) {
        DEBUG_MSG( "Unable to open X display.");
        return;
    }

    pointerManager* pM = new pointerManager(nullptr, display);

    char keyMap[32];
    while (!isInterruptionRequested()) {
        XQueryKeymap(display, keyMap);

        for (int i = 0; i < 256; ++i) {
            int byte = i / 8;
            int bit = i % 8;

            if (keyMap[byte] & (1 << bit)) {
                KeySym keySym = XKeycodeToKeysym(display, i, 0);


                if (keySym == XK_a || keySym == XK_A ) {
                    DEBUG_MSG("Letter a or A is pressed !!");
                            _isEnabled = !_isEnabled;
                }

                if(_isEnabled)
                {
                    if (keySym == XK_Left) {
                        pM->moveMousePointer(10,pointerManager::mDir::LEFT);
                        //                         qDebug() << "RIGHT ARROW PRESSED";
                    } else if (keySym == XK_Right) {
                        pM->moveMousePointer(10,pointerManager::mDir::RIGHT);
                        //                        qDebug() << "RIGHT ARROW PRESSED";
                    } else if (keySym == XK_Up) {
                        pM->moveMousePointer(10,pointerManager::mDir::UP);
                        //                        qDebug() << "UP ARROW PRESSED";
                    } else if (keySym == XK_Down) {
                        pM->moveMousePointer(10,pointerManager::mDir::DOWN);
                        //                        qDebug() << "DOWN ARROW PRESSED";
                    }
                }
            }
        }
        QThread::msleep(100); // Sleep for 100ms to reduce CPU usage
    }
    XCloseDisplay(display);
}
