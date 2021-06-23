//
// Created by Kirill Diordiev on 21.05.2021.
//

#include "elevator.h"

Elevator::Elevator(QObject *parent) : QObject(parent) {
    status = STAND_OPEN;
    current_floor = 1;
    target = 1;
    current_direction = STAY;

    doors.start_opening();

    liftWaitClose.setSingleShot(true);
    newTargetTImer.setSingleShot(true);

    time = CROSSING_FLOOR_TIME;
    timeMove.setSingleShot(true);

    connect(this, SIGNAL(targetIsReached()), this, SLOT(goStandOpen()));
    connect(&newTargetTImer, SIGNAL(timeout()), this, SLOT(goStandClose()));
    connect(this, SIGNAL(close_doors()), &doors, SLOT(start_closing()));
    connect(&timeMove, SIGNAL(timeout()), this, SLOT(moving()));
    connect(this, SIGNAL(move()), this, SLOT(moving()));
    connect(this, SIGNAL(stoped(int)), &doors, SLOT(start_opening()));

    connect(this, SIGNAL(stoped(int)), &control_panel, SLOT(reached_floor(int)));
    connect(&control_panel, SIGNAL(move_to(int)), this, SLOT(onTargetReceived(int)));

    connect(&liftWaitClose, SIGNAL(timeout()), this, SLOT(moving()));
}



void Elevator::onTargetReceived(int i) {
    if (status == MOVING || status == STAND_CLOSE) {
        return;
    }

    target = i;

    if (target > current_floor) {
        current_direction = UP;
        emit move();
    }
    else if (target < current_floor) {
        current_direction = DOWN;
        emit move();
    }
    else if (target == current_floor) {
        emit targetIsReached();
    }
}


void Elevator::moving() {
    if (status == STAND_OPEN) {
        newTargetTImer.start(DOORS_TIME);
        liftWaitClose.start(WAIT_TIME);
    } else {
        emit newInfo("Elevator on " + QString::number(current_floor) + " floor" + " moving");
        current_floor += current_direction;
        status = MOVING;

        if (target == current_floor) {
            emit targetIsReached();
        }
        else {
            timeMove.start(time);
        }
    }
}


void Elevator::goStandOpen() {
    status = STAND_OPEN;
    emit newInfo("Elevator stopped and opened " + QString::number(current_floor) + " floor");
    current_direction = STAY;
    control_panel.set_direction(current_direction);
    emit stoped(current_floor);
}


void Elevator::goStandClose() {
    status = STAND_CLOSE;
    emit close_doors();
}


Door* Elevator::getDoors() {
    return &doors;
}

ControlPanel* Elevator::getControlPanel() {
    return &control_panel;
}

int Elevator::getCurFloor() {
    return current_floor;
}