//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QObject>

#include <control_panel/control_panel.h>
#include <door/door.h>
#include <constants.h>

class Cabin : public QObject {
    Q_OBJECT
    enum cabin_state { MOVE, STANDBY_OPEN, STANDBY_CLOSE };

public:
    explicit Cabin(QObject *parent = nullptr);

signals:
    void close_doors();
    void cabin_cross_floor(int floor, direction dir);
    void cabin_reached_target(int floor);
    void cabin_stop(int floor);

public slots:
    void cabin_move();
    void cabin_slowdown();
    void moveStandByOpen();
    void moveStandByClose();
    void cabin_call(int floor, direction dir); // Вызов из панели

private:
    int current_floor;
    int target;
    bool new_target;
    cabin_state state;
    direction current_direction;
    Door door;
    QTimer cross_floor_timer;
};



