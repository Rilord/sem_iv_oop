//
// Created by Kirill Diordiev on 21.05.2021.
//

#include <cabin/cabin.h>

#include <QString>

#include <QDebug>

Cabin::Cabin(QObject *parent) : QObject(parent), current_floor(-1), new_target(false),
    state(STOP), current_direction(STAY) {
    cross_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL())

}