#pragma once

#include <QObject>
#include <QTextEdit

#include <cabin/cabin.h>
#include <consts.h>
#include <control_panel/control_panel.h>

class Elevator : public QObject {
    Q_OBJECT

public:
    Elevator();
    void onClick(int floor);
private:
    // ControlPanel
    // Cabin
    //
};