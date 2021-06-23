//
// Created by Kirill Diordiev on 26.05.2021.
//

#include <QDebug>
#include <ui/mainwindow.h>
#include <ui/design.h>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    qDebug() << "Stopped at 1 floor, doors are closed.\n"
                "Waiting state...";

    connect(elevator.getDoors(), SIGNAL(newInfo(QString)), this, SLOT(setInfo(QString)));
    connect(&elevator, SIGNAL(newInfo(QString)), this, SLOT(setInfo(QString)));
    connect(this, SIGNAL(addTarget(int)), elevator.getControlPanel(), SLOT(new_move_to(int)));

    for (int i = 0; i < ui->cabin_buttons.size(); ++i) {
        connect(ui->cabin_buttons[i], &QPushButton::pressed, this,
                [=, this]() {on_button_cabin_clicked(i + 1); });
    }

    for (int i = 0; i < ui->cabin_buttons.size(); ++i) {
        connect(ui->floor_buttons[i], &QPushButton::pressed, this,
                [=, this]() {on_button_floor_clicked(i + 1); });
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_cabin_clicked(int num) {
    qDebug() << "Cabin pressed button " << num;
    emit addTarget(num);
}

void MainWindow::on_button_floor_clicked(int num) {
    qDebug() << "Floor " << num << " call.";
    emit addTarget(num);
}

void MainWindow::stop() {
    QString info = "Лифт стоит на " + QString::number(elevator.getCurFloor()) + " этаже";
    qDebug() << info;
}

void MainWindow::moving() {
    QString info = "Лифт на " + QString::number(elevator.getCurFloor()) + " этаже";
    qDebug() << info;
}

void MainWindow::close() {
    QString info = "Двери закрыты";
    qDebug() << info;
}

void MainWindow::open() {
    QString info = "Двери открыты";
    qDebug() << info;
}

void MainWindow::startClosing() {
    QString info = "Двери закрываются";
    qDebug() << info;
}

void MainWindow::startOpening() {
    QString info = "Двери открываются";
    qDebug() << info;
}

void MainWindow::setInfo(QString info) {
    qDebug() << info;
}