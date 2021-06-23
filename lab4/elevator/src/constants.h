//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QTextEdit>
#include <QTimer>

enum direction {
    DOWN = -1,
    STAY,
    UP
};

#define CROSSING_FLOOR_TIME 1500
#define DOORS_TIME 2000
#define WAIT_TIME 2000
#define FLOOR_NUM 10
