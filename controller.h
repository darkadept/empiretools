#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "database/orm.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();
    
signals:
    
public slots:
    void start();
    
private:
    class ControllerPrivate &d;
    class ControllerUiPrivate &ui;

//    void initPlayers();
    void initMap();
    void initSkills();

};

#endif // CONTROLLER_H
