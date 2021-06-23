//
// Created by Kirill Diordiev on 26.05.2021.
//

#pragma once

#include <QMainWindow>
#include <elevator/elevator.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void on_button_cabin_clicked(int num);

signals:
    void addTarget(int);

private slots:
//  void on_button_cabin_3_clicked();
//  void on_button_cabin_4_clicked();
//  void on_button_cabin_5_clicked();
//  void on_button_cabin_6_clicked();
//  void on_button_cabin_7_clicked();
//  void on_button_cabin_8_clicked();
//  void on_button_cabin_9_clicked();
//  void on_button_cabin_10_clicked();
//
//  void on_button_floor_1_clicked();
//  void on_button_floor_2_clicked();
//  void on_button_floor_3_clicked();
//  void on_button_floor_4_clicked();
//  void on_button_floor_5_clicked();
//  void on_button_floor_6_clicked();
//  void on_button_floor_7_clicked();
//  void on_button_floor_8_clicked();
//  void on_button_floor_9_clicked();
    void on_button_floor_clicked(int num);
    void setInfo(QString info);
    void close();
    void open();
    void startClosing();
    void startOpening();
    void stop();
    void moving();

private:
    Ui::MainWindow *ui;
    Elevator elevator;
};