//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QObject>
#include <QVector>
#include <constants.h>

#define IS_REACHABLE(new_floor) \
    (current_direction == UP && new_floor > current_target) || \
(current_direction == DOWN && new_floor < current_target)      \

#define GET_DIRECTION \
    (current_floor > current_target) ? DOWN : UP


class ControlPanel : public QObject {
    Q_OBJECT
    enum panel_state { BUSY, FREE };
public:
    explicit ControlPanel(QObject *parent = nullptr);
    void set_direction(direction dir);
    void set_current_target(int);
    int get_current_target();


signals:
    void move_to(int floor); // Вызов лифта из Elevator

public slots:
    void reached_floor(int floor); // Кабина достигла cabin_stop и дала сигнал
    void passed_floor(int floor); // Кабина прошла cabin_passed и дала сигнал
    void new_move_to(int floor);

private:
    int current_floor;
    int current_target = -1;

    QVector<bool> is_targets;
    panel_state state;
    direction current_direction;
    bool next_target(int &floor);
    void find_new_target();

};
