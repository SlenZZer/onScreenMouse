#include "pointermanager.h"

pointerManager::pointerManager(QObject *parent, Display *mdisplay) : QObject(parent),display(mdisplay)
{
//    display = XOpenDisplay(nullptr);
//    if(display == nullptr)
//    {
//        qDebug()<<" Not opening!!";
//    }

    root = DefaultRootWindow(display);

    //Get current pointer position
    XQueryPointer(display, root, &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
}

pointerManager::~pointerManager()
{
    XCloseDisplay(display);

}

bool pointerManager::moveMousePointer(int dist, pointerManager::mDir direction)
{

    //Get current pointer position
    XQueryPointer(display, root, &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    switch (direction) {
    case UP:
        new_x = event.xbutton.x_root ;
        new_y = event.xbutton.y_root- dist;
//        qDebug()<< "Pointer moved up !!";

        break;
    case DOWN:
        new_x = event.xbutton.x_root ;
        new_y = event.xbutton.y_root + dist;
//        qDebug()<< "Pointer moved down !!";
        break;
    case RIGHT: // right
        new_x = event.xbutton.x_root + dist ;
        new_y = event.xbutton.y_root ;
//        qDebug()<< "Pointer moved right !!";
        break;
    case LEFT: // left
        new_x = event.xbutton.x_root - dist ;
        new_y = event.xbutton.y_root ;
//        qDebug()<< "Pointer moved left !!";
        break;
    default:
//        qDebug()<<"no input direcetion given !!";
        break;
    }

    // Set new pointer position
    XWarpPointer(display, None, root, 0, 0, 0, 0, new_x, new_y);
    XFlush(display);

    return true;
}
