//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QObject>
#include <QTextEdit>

#include <door/door.h>
#include <constants.h>
#include <control_panel/control_panel.h>

class Elevator : public QObject {
Q_OBJECT
    enum elevator_status { MOVING, STAND_OPEN, STAND_CLOSE};


signals:
    void targetIsReached();
    void newInfo(QString);

    void move();
    void stoped(int);

    void close_doors();

public slots:
    void moving();

    void goStandClose();
    void goStandOpen();
    void onTargetReceived(int);

public:
    Elevator(QObject *parent = nullptr);
    Door* getDoors();
    ControlPanel* getControlPanel();
    int getCurFloor();

private:
    elevator_status status;
    ControlPanel control_panel;
    Door doors;
    QTimer liftWaitClose;
    QTimer newTargetTImer;
    QTimer timeMove;
    int time;

    int current_floor;
    direction current_direction;
    int target;

};
