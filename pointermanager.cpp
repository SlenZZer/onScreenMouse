#include "pointermanager.h"

pointerManager::pointerManager(QObject *parent, Display *mdisplay) : QObject(parent),display(mdisplay)
{
    if(display == nullptr)
    {
        qDebug()<<" Not opening!!";
    }

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
                        DEBUG_MSG("Pointer moved up !!");

        break;
    case DOWN:
        new_x = event.xbutton.x_root ;
        new_y = event.xbutton.y_root + dist;
                DEBUG_MSG("Pointer moved down !!");
        break;
    case RIGHT: // right
        new_x = event.xbutton.x_root + dist ;
        new_y = event.xbutton.y_root ;
        //        DEBUG_MSG("Pointer moved right !!");
        break;
    case LEFT: // left
        new_x = event.xbutton.x_root - dist ;
        new_y = event.xbutton.y_root ;
        //        DEBUG_MSG("Pointer moved left !!");
        break;
    case LEFT_CLK: // left
        XTestFakeButtonEvent(display, 1, True, CurrentTime);  // Press left button
        XTestFakeButtonEvent(display, 1, False, CurrentTime); // Release left button
        DEBUG_MSG("Left click triggered !!");
        break;
    case RIGHT_CLK:
        XTestFakeButtonEvent(display, 3, True, CurrentTime);  // Press right button
        XTestFakeButtonEvent(display, 3, False, CurrentTime); // Release right button
        DEBUG_MSG("Right click triggered !!");
        break;

    case SCR_UP:
        XTestFakeButtonEvent(display, 4, True, CurrentTime);  // Scroll up
        XTestFakeButtonEvent(display, 4, False, CurrentTime); // Stop scroll
        DEBUG_MSG("Scroll up triggered !!");
        break;

    case SCR_DOWN:
        XTestFakeButtonEvent(display, 5, True, CurrentTime);  // Scroll down
        XTestFakeButtonEvent(display, 5, False, CurrentTime); // Stop scroll
        DEBUG_MSG("Scroll down triggered !!");
        break;
    default:
        //        DEBUG_MSG( "no input direcetion given !!");
        break;
    }

    // Move pointer to the new position only if a direction was given
    if (direction != LEFT_CLK && direction != RIGHT_CLK && direction != SCR_UP && direction != SCR_DOWN)
        XWarpPointer(display, None, root, 0, 0, 0, 0, new_x, new_y);
    XFlush(display);

    return true;
}
