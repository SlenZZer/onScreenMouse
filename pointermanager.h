#ifndef POINTERMANAGER_H
#define POINTERMANAGER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <X11/Xlib.h>
#include <X11/keysym.h>


class pointerManager : public QObject
{
    Q_OBJECT
public:

    enum mDir{
        UP = 0,
        DOWN = 1,
        RIGHT = 2,
        LEFT = 3,
    };

    explicit pointerManager(QObject *parent , Display *display);
    ~pointerManager();

    bool moveMousePointer( int dist, pointerManager::mDir direction);



    Display *display = nullptr;
    Window root ;
    XEvent event;
    int new_x;
    int new_y;

signals:

};


class KeyLogger : public QThread {
    Q_OBJECT

public:
    KeyLogger(QObject *parent = nullptr) : QThread(parent) {}
    ~KeyLogger() { requestInterruption(); wait(); }

protected:
    bool _isEnabled = false;
    void run() override {
        Display *display = XOpenDisplay(nullptr);
        if (!display) {
            qDebug() << "Unable to open X display.";
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
                        qDebug() << "Letter a or A is pressed !!";
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
};



#endif // POINTERMANAGER_H
