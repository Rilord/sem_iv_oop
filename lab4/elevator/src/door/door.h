//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QObject>

#include <constants.h>

class Door : public QObject {
    Q_OBJECT
    enum door_state { OPENING, OPENED, CLOSING, CLOSED };
public:
    explicit Door(QObject *parent = nullptr);
signals:
    void closed_doors();
    void opened_doors();
public slots:
    void start_opening();
    void start_closing();
public slots:
    void open();
    void close();
private:
    door_state state;
    QTimer doors_open_timer;
    QTimer doors_close_timer;
    QTimer doors_opened_timer;
};
