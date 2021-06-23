//
// Created by Kirill Diordiev on 21.05.2021.
//

#include <cabin/cabin.h>

#include <QString>

#include <QDebug>

Cabin::Cabin(QObject *parent)
        : QObject(parent), current_floor(1), target(-1), new_target(false),
          state(STANDBY_OPEN), current_direction(STAY) {
    cross_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(cabin_called_open()), &door, SLOT(moveStandByOpen()));
    QObject::connect(this, SIGNAL(cabin_called_shut()), &door, SLOT(moveStandByClose()));
    QObject::connect(this, SIGNAL(cabin_reached_target(int)), this,
                     SLOT(cabin_slowdown()));
    QObject::connect(this, SIGNAL(cabin_stop(int)), &door,
                     SLOT(start_opening()));
    QObject::connect(&door, SIGNAL(closed_doors()), this, SLOT(cabin_move()));

    QObject::connect(&cross_floor_timer, SIGNAL(timeout()), this,
                     SLOT(cabin_move()));
}


void Cabin::cabin_move() { // дверь закрыта - поехали
    if (status == STAND)
}

void Cabin::cabin_slowdown() { // кабина достигла цели - астанавитесь
    if (state != MOVE)
        return;

    state = STOP;
    qDebug() << "Stopped at floor " << QString::number(current_floor) << ".";
    emit cabin_stop(current_floor);
}

void Cabin::cabin_call(int floor, direction dir) {
    if (state != STOP)
        return;

    new_target = true;
    state = WAIT;
    target = floor;

    current_direction = dir;
    if (cabin_doors == SHUT) {
        cabin_doors = OPEN;
        emit cabin_called_shut();
    }
    else {
        emit cabin_called_open();
    }
}

void Cabin::moveStandByClose() {
    state = STANDBY_CLOSE;
    emit close_doors();
}

void Cabin::moveStandByOpen() {
    state = STANDBY_OPEN;
    current_direction = STAY;
    emit cabin_stop(current_floor);
}