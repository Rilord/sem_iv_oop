//
// Created by Kirill Diordiev on 21.05.2021.
//

#include "control_panel.h"

#include <iostream>

#include <QDebug>

ControlPanel::ControlPanel(QObject *parent)
        : QObject(parent), current_floor(1),
          current_target(-1), is_targets(FLOOR_NUM, false),
          state(FREE), current_direction(STAY) {}

void ControlPanel::new_move_to(int floor)  {
    state = BUSY;
    is_targets[floor - 1] = true;

    if (current_target == -1) {
        current_target = floor;
    }

    if (IS_REACHABLE(floor)) {
        current_target = floor;
    }

    next_target(floor);
    current_direction = GET_DIRECTION;
    emit move_to(floor);
}

void ControlPanel::reached_floor(int floor) { //
    if (state != BUSY)
        return;

    current_floor = floor;
    is_targets[floor - 1] = false;

    if (current_floor == current_target) {
        current_target = -1;
        find_new_target();
    }

    if (next_target(floor)) {
        current_direction = GET_DIRECTION;

        emit move_to(floor);
    } else {
        state = FREE;
    }
}

void ControlPanel::passed_floor(int floor) {
    current_floor = floor;
}

void ControlPanel::find_new_target() {
    int state = false;

    if (current_direction == UP) {
        for (int i = FLOOR_NUM; i >= 1 && !state; i--) {
            if (is_targets[i - 1]) {
                state = true;
                current_target = i;
            }
        }
        return;
    }

    for (int i = 1; i <= FLOOR_NUM && !state; i++) {
        if (is_targets[i - 1]) {
            state = true;
            current_target = i;
        }
    }
}

bool ControlPanel::next_target(int &floor) {
    bool state = false;
    if (current_target > current_floor) {
        bool flag = true;
        for (int i = current_floor; i <= FLOOR_NUM && flag; i += 1) {
            if (is_targets[i - 1]) {
                floor = i;
                state = true;
                flag = false;
            }
        }
    } else {
        bool flag = true;
        for (int i = current_floor; i >= 1 && flag; i -= 1) {
            if (is_targets[i - 1]) {
                floor = i;
                state = true;
                flag = false;
            }
        }
    }
    return state;
}

void ControlPanel::set_direction(direction dir) {
    current_direction = dir;
}
int ControlPanel::get_current_target() {
    return current_floor;
}

void ControlPanel::set_current_target(int floor) {
    current_floor = floor;
}