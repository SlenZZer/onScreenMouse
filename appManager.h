#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QThread>
#include "pointermanager.h"

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
