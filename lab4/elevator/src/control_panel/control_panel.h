//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QObject>
#include <QVector>

#include <constants.h>

class ControlPanel : public QObject {
    Q_OBJECT
    enum panel_state { BUSY, FREE };
public:
    explicit ControlPanel(QObject *parent = nullptr);
    void new_move_to(int floor);

signals:
    void move_to(int floor, direction dir);

public slots:
    void reached_floor(int floor);
    void passed_floor(int floor);

private:
    int current_floor;
    int current_target = -1;

    QVector<bool> is_targets;
    panel_state state;
    direction current_direction;
    bool next_target(int &floor);
    void find_new_target();

};
