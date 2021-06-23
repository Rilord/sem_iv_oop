//
// Created by Kirill Diordiev on 21.05.2021.
//

#pragma once

#include <QObject>

#include <constants.h>

class Door : public QObject {
    Q_OBJECT
public:
    explicit Door(QObject *parent = nullptr);
    enum door_state { OPENING, OPENED, CLOSING, CLOSED };

signals:
    void closed_doors();
    void newInfo(QString);
public slots:
    void start_opening();
    void start_closing();
private slots:
    void open();
    void close();
private:
    bool isOpen();
    door_state state;
    QTimer doorOpenTimer;
    QTimer doorCloseTimer;
    int time;
};
