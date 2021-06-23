//
// Created by Kirill Diordiev on 21.05.2021.
//

#include "door.h"

#include <QDebug>

Door::Door(QObject *parent) : QObject(parent), state(CLOSED) {
    state = OPENED;
    time = DOORS_TIME;

    doorOpenTimer.setSingleShot(true);
    doorCloseTimer.setSingleShot(true);

    connect(&doorOpenTimer, SIGNAL(timeout()), this, SLOT(open()));
    connect(&doorCloseTimer, SIGNAL(timeout()), this, SLOT(close()));}

bool Door::isOpen() {
    return state == OPENED;
}


void Door::start_opening() { // кабина остановилась - открываем дверь
    if (!isOpen()) {
        state = OPENING;
        emit newInfo("door opening");
        doorOpenTimer.start(DOORS_TIME);
    }
}

void Door::start_closing() { // Кабина вызвана - дверь закрывается
    if (isOpen()) {
        state = CLOSING;
        emit newInfo("door closing");
        doorCloseTimer.start(DOORS_TIME);
    }
}

void Door::open() { // таймер прошел - открываем
        state = OPENED;
        qDebug() << "The doors are opened!";
        emit newInfo("Door open");

}

void Door::close() { // таймер прошел - закрываем
    if (state == CLOSING) {
        state = CLOSED;
        qDebug() << "The doors are closed.";
        emit newInfo("Door closed");
    }
}