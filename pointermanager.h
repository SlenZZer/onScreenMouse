#ifndef POINTERMANAGER_H
#define POINTERMANAGER_H

#include <QObject>
#include <QDebug>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#ifdef QT_DEBUG
    #define DEBUG_MSG(msg) qDebug() << msg
#else
    #define DEBUG_MSG(msg) // Do nothing in release mode
#endif

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




#endif // POINTERMANAGER_H
