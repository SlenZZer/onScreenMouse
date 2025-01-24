#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QThread>
#include "pointermanager.h"
#define initDist 20
class appManager : public QThread{
    Q_OBJECT

public:
    appManager(QObject *parent = nullptr) : QThread(parent) {}

    ~appManager();

protected:
    bool _isEnabled = false;
    bool _exiting = false;
    void run() override;

signals:
    void killRequested();

};
#endif // APPMANAGER_H
