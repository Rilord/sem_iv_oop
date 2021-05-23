//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QObject>

#include <constants.h>
#include <control_panel/control_panel.h>
#include <door/door.h>

class Cabin : public QObject {
    Q_OBJECT
    enum cabin_state { MOVE, WAIT, STOP };

public:
    explicit Cabin(QObject *parent = nullptr);

signals:
void cabin_called();
void cabin_cross_floor(int floor, direction dir);
void cabin_reached_target(int floor);
void cabin_stop(int floor);

public slots:
    void cabin_move();
    void cabin_slowdown();
    void cabin_call(int floor, direction dir);

private:
    int current_floor;
    int target;
    bool new_target;
    cabin_state state;
    direction current_direction;
    Door door;
    QTimer cross_floor_timer;
};



