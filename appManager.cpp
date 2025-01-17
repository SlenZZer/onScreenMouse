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
    while (!isInterruptionRequested() || !_exiting) {
        XQueryKeymap(display, keyMap);
        // Check for Ctrl + Alt + M
        bool ctrlPressed = keyMap[XKeysymToKeycode(display, XK_Control_L) / 8] & (1 << (XKeysymToKeycode(display, XK_Control_L) % 8));
        bool altPressed = keyMap[XKeysymToKeycode(display, XK_Alt_L) / 8] & (1 << (XKeysymToKeycode(display, XK_Alt_L) % 8));

        bool mPressed = keyMap[XKeysymToKeycode(display, XK_M) / 8] & (1 << (XKeysymToKeycode(display, XK_M) % 8));
        bool nPressed = keyMap[XKeysymToKeycode(display, XK_N) / 8] & (1 << (XKeysymToKeycode(display, XK_N) % 8));

        bool upRightPressed = ((keyMap[XKeysymToKeycode(display, XK_Up) / 8] & (1 << (XKeysymToKeycode(display, XK_Up) % 8)))
                && keyMap[XKeysymToKeycode(display, XK_Right) / 8] & (1 << (XKeysymToKeycode(display, XK_Right) % 8)))?true:false;

        bool upLeftPressed = ((keyMap[XKeysymToKeycode(display, XK_Up) / 8] & (1 << (XKeysymToKeycode(display, XK_Up) % 8)))
                && keyMap[XKeysymToKeycode(display, XK_Left) / 8] & (1 << (XKeysymToKeycode(display, XK_Left) % 8)))?true:false;

        bool LeftDownPressed = ((keyMap[XKeysymToKeycode(display, XK_Down) / 8] & (1 << (XKeysymToKeycode(display, XK_Down) % 8)))
                && (keyMap[XKeysymToKeycode(display, XK_Left) / 8] & (1 << (XKeysymToKeycode(display, XK_Left) % 8))))?true:false;

        bool rightDownPressed = ((keyMap[XKeysymToKeycode(display, XK_Down) / 8] & (1 << (XKeysymToKeycode(display, XK_Down) % 8)))
                && (keyMap[XKeysymToKeycode(display, XK_Right) / 8] & (1 << (XKeysymToKeycode(display, XK_Right) % 8))))?true:false;

        if (ctrlPressed && altPressed && nPressed) {
                    DEBUG_MSG("Ctrl + Alt + M pressed. requested exiting...");
                    _exiting = true;
                }

        if (ctrlPressed && altPressed && mPressed) {
                    DEBUG_MSG("Ctrl + Alt + M pressed. enabled on screen mouse !!");
                    _isEnabled = !_isEnabled;
                }

        for (int i = 0; i < 256; ++i) {
            int byte = i / 8;
            int bit = i % 8;

            if (keyMap[byte] & (1 << bit)) {
                ulong keySym = XKeycodeToKeysym(display, i, 0);

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

                    if (upRightPressed)
                    {
                        pM->moveMousePointer(10,pointerManager::mDir::RIGHT_CLK);
//                        qDebug() << "Left button clicked !!";
                    }

                    if (upLeftPressed)
                    {
                        pM->moveMousePointer(10,pointerManager::mDir::LEFT_CLK);
//                        qDebug() << "Left button clicked !!";
                    }

                    if (rightDownPressed)
                    {
                        pM->moveMousePointer(10,pointerManager::mDir::SCR_UP);
//                        qDebug() << "Left button clicked !!";
                    }

                    if (LeftDownPressed)
                    {
                        pM->moveMousePointer(10,pointerManager::mDir::SCR_DOWN);
//                        qDebug() << "Left button clicked !!";
                    }
                }
            }
        }
        QThread::msleep(100); // Sleep for 100ms to reduce CPU usage
    }
    XCloseDisplay(display);
}
