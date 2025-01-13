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
    void run() override;
};
#endif // APPMANAGER_H
